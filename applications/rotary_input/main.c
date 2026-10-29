#include <fcntl.h>
#include <linux/gpio.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

static int emit_key(int fd, int key) {
  struct input_event ev = {0};

  ev.type = EV_KEY;
  ev.code = key;
  ev.value = 1;

  if (write(fd, &ev, sizeof(ev)) != sizeof(ev))
    return -1;

  memset(&ev, 0, sizeof(ev));
  ev.type = EV_SYN;
  ev.code = SYN_REPORT;

  if (write(fd, &ev, sizeof(ev)) != sizeof(ev))
    return -1;

  memset(&ev, 0, sizeof(ev));
  ev.type = EV_KEY;
  ev.code = key;
  ev.value = 0;

  if (write(fd, &ev, sizeof(ev)) != sizeof(ev))
    return -1;

  memset(&ev, 0, sizeof(ev));
  ev.type = EV_SYN;
  ev.code = SYN_REPORT;

  return write(fd, &ev, sizeof(ev)) == sizeof(ev) ? 0 : -1;
}

int main(void) {
  int chip_fd = -1;
  int ui = -1;
  int ret;
  int exit_status = 1;
  int gpio_requested = 0;
  int ui_created = 0;

  struct gpio_v2_line_request rotary_encoder_gpio = {0};

  rotary_encoder_gpio.offsets[0] = 22;
  rotary_encoder_gpio.offsets[1] = 27;
  strcpy(rotary_encoder_gpio.consumer, "rotary_input");
  rotary_encoder_gpio.num_lines = 2;
  rotary_encoder_gpio.config.flags = GPIO_V2_LINE_FLAG_INPUT;

  chip_fd = open("/dev/gpiochip0", O_RDONLY);
  if (chip_fd < 0) {
    perror("open gpiochip");
    goto cleanup;
  }

  ret = ioctl(chip_fd, GPIO_V2_GET_LINE_IOCTL, &rotary_encoder_gpio);
  if (ret < 0) {
    perror("request GPIO lines");
    goto cleanup;
  }
  gpio_requested = 1;

  ui = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
  if (ui < 0) {
    perror("open uinput");
    goto cleanup;
  }

  if (ioctl(ui, UI_SET_EVBIT, EV_KEY) < 0 ||
      ioctl(ui, UI_SET_KEYBIT, KEY_UP) < 0 ||
      ioctl(ui, UI_SET_KEYBIT, KEY_DOWN) < 0) {
    perror("configure uinput capabilities");
    goto cleanup;
  }

  struct uinput_setup setup = {0};

  snprintf(setup.name, UINPUT_MAX_NAME_SIZE, "cybit-rotary-keyboard");
  setup.id.bustype = BUS_VIRTUAL;
  setup.id.vendor = 0x1234;
  setup.id.product = 0x5678;
  setup.id.version = 1;

  if (ioctl(ui, UI_DEV_SETUP, &setup) < 0) {
    perror("UI_DEV_SETUP");
    goto cleanup;
  }

  if (ioctl(ui, UI_DEV_CREATE) < 0) {
    perror("UI_DEV_CREATE");
    goto cleanup;
  }
  ui_created = 1;

  /* Allow the input subsystem to register the virtual device. */
  usleep(100000);

  struct gpio_v2_line_values encoder_state = {0};
  encoder_state.mask = (1ULL << 0) | (1ULL << 1);

  ret = ioctl(rotary_encoder_gpio.fd, GPIO_V2_LINE_GET_VALUES_IOCTL,
              &encoder_state);
  if (ret < 0) {
    perror("initial GPIO read");
    goto cleanup;
  }

  int last_clk = (encoder_state.bits >> 0) & 1;

  while (1) {
    ret = ioctl(rotary_encoder_gpio.fd, GPIO_V2_LINE_GET_VALUES_IOCTL,
                &encoder_state);
    if (ret < 0) {
      perror("GPIO read");
      goto cleanup;
    }

    int clk = (encoder_state.bits >> 0) & 1;
    int dt = (encoder_state.bits >> 1) & 1;

    // printf("clk=%d dt=%d last_clk=%d\n", clk, dt, last_clk);
    // fflush(stdout);
    //
    if (clk != last_clk) {
      if (clk == 1) {
        int key = (clk == dt) ? KEY_UP : KEY_DOWN;

        printf("emitting %s\n", key == KEY_UP ? "KEY_UP" : "KEY_DOWN");
        fflush(stdout);

        if (emit_key(ui, key) < 0) {
          perror("emit key");
          goto cleanup;
        }
      }

      last_clk = clk;
    }
    usleep(1000);
  }

  exit_status = 0;

cleanup:
  if (ui_created)
    ioctl(ui, UI_DEV_DESTROY);

  if (ui >= 0)
    close(ui);

  if (gpio_requested)
    close(rotary_encoder_gpio.fd);

  if (chip_fd >= 0)
    close(chip_fd);

  return exit_status;
}
