#include <fcntl.h>
#include <linux/gpio.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {

  struct gpio_v2_line_request rotary_encoder_gpio = {0};
  rotary_encoder_gpio.offsets[0] = 22;
  rotary_encoder_gpio.offsets[1] = 27;
  strcpy(rotary_encoder_gpio.consumer, "rotary_input");
  rotary_encoder_gpio.num_lines = 2;
  rotary_encoder_gpio.config.flags = GPIO_V2_LINE_FLAG_INPUT;

  int chip_fd = open("/dev/gpiochip0", O_RDONLY);
  if (chip_fd < 0) {
    perror("unable to open chip");
    return 0;
  }
  int ret = ioctl(chip_fd, GPIO_V2_GET_LINE_IOCTL, &rotary_encoder_gpio);
  if (ret < 0) {
    perror("unable to open line request");
    return 0;
  }

  struct gpio_v2_line_values encoder_state = {0};
  encoder_state.mask = (1ULL << 0) | (1ULL << 1);

  while (1) {
    ret = ioctl(rotary_encoder_gpio.fd, GPIO_V2_LINE_GET_VALUES_IOCTL,
                &encoder_state);
    if (ret < 0) {
      perror("gpio read fail");
      return 0;
    }

    int clk = (encoder_state.bits >> 0) & 1;
    int dt = (encoder_state.bits >> 1) & 1;

    printf("encoder state %d , %d\n ", clk, dt);
    fflush(stdout);
    usleep(1000000);
  }
  return 0;
}
