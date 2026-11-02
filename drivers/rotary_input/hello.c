#include <linux/delay.h>
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/interrupt.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/printk.h>
#include <linux/slab.h>

struct rotary_gpios_desc {
  struct gpio_desc *a;
  struct gpio_desc *b;
  struct gpio_desc *button;

  int irq_a;
  int irq_b;
  int irq_button;

  int last_a;
  struct device *dev;
};

static irqreturn_t rotary_irq_handler(int irq, void *dev_id);
static irqreturn_t rotary_irq_thread(int irq, void *dev_id);

static int rotary_cybit_probe(struct platform_device *pdev) {
  struct device *dev = &pdev->dev;
  struct rotary_gpios_desc *gpios;
  int ret;

  dev_info(dev, "Rotary driver probe started\n");

  /* Allocate GPIO descriptor storage */
  gpios = devm_kzalloc(dev, sizeof(*gpios), GFP_KERNEL);
  if (!gpios)
    return -ENOMEM;

  /* Acquire GPIO A */
  gpios->a = devm_gpiod_get(dev, "a", GPIOD_IN);
  if (IS_ERR(gpios->a))
    return dev_err_probe(dev, PTR_ERR(gpios->a), "Failed to acquire GPIO A\n");

  dev_info(dev, "GPIO A acquired\n");

  /* Acquire GPIO B */
  gpios->b = devm_gpiod_get(dev, "b", GPIOD_IN);
  if (IS_ERR(gpios->b))
    return dev_err_probe(dev, PTR_ERR(gpios->b), "Failed to acquire GPIO B\n");

  dev_info(dev, "GPIO B acquired\n");

  /* Acquire button GPIO */
  gpios->button = devm_gpiod_get(dev, "button", GPIOD_IN);
  if (IS_ERR(gpios->button))
    return dev_err_probe(dev, PTR_ERR(gpios->button),
                         "Failed to acquire button GPIO\n");

  dev_info(dev, "Button GPIO acquired\n");
  gpios->dev = dev;

  // last encoder state seeding
  gpios->last_a = gpiod_get_value_cansleep(gpios->a);

  if (gpios->last_a < 0)
    return dev_err_probe(dev, -EIO, "Failed to read initial encoder state\n");

  gpios->irq_a = gpiod_to_irq(gpios->a);
  if (gpios->irq_a < 0)
    return dev_err_probe(dev, gpios->irq_a, "Failed to get IRQ A\n");

  gpios->irq_b = gpiod_to_irq(gpios->b);
  if (gpios->irq_b < 0)
    return dev_err_probe(dev, gpios->irq_b, "Failed to get IRQ B\n");

  ret = devm_request_threaded_irq(
      dev, gpios->irq_a, rotary_irq_handler, rotary_irq_thread,
      IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
      "cybit_rotary_a", gpios);

  if (ret)
    return dev_err_probe(dev, ret, "Failed to request IRQ A\n");

  ret = devm_request_threaded_irq(
      dev, gpios->irq_b, rotary_irq_handler, rotary_irq_thread,
      IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
      "cybit_rotary_b", gpios);

  if (ret)
    return dev_err_probe(dev, ret, "Failed to request IRQ B\n");
  /* Associate GPIO data with platform device */
  platform_set_drvdata(pdev, gpios);

  dev_info(dev, "All GPIOs acquired successfully\n");

  return 0;
}

static irqreturn_t rotary_irq_handler(int irq, void *dev_id) {
  return IRQ_WAKE_THREAD;
}

static irqreturn_t rotary_irq_thread(int irq, void *dev_id) {
  struct rotary_gpios_desc *gpios = dev_id;

  int a = gpiod_get_value_cansleep(gpios->a);
  int b = gpiod_get_value_cansleep(gpios->b);
  if (a != gpios->last_a) {
    if (a == b) {
      printk("clockwise\n");
    } else {
      printk("anti-clockwise\n");
    }
  }

  gpios->last_a = a;

  return IRQ_HANDLED;
}

static void rotary_cybit_remove(struct platform_device *pdev) {
  printk("rotary cybit removed\n");
}

static const struct of_device_id cybit_of_match[] = {
    {.compatible = "custom,cybit-rotary"}, {/*sentinel*/}};
MODULE_DEVICE_TABLE(of, cybit_of_match);

static struct platform_driver rotary_cybit_driver = {
    .probe = rotary_cybit_probe,
    .remove = rotary_cybit_remove,
    .driver =
        {
            .name = "rotary_cybit",
            .of_match_table = cybit_of_match,

        },
};

module_platform_driver(rotary_cybit_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GPIO consumer driver for rotary encoder");
