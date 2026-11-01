#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/printk.h>

struct gpio_desc *gpio;

static int rotary_cybit_probe(struct platform_device *pdev) {
  struct device *dev = &pdev->dev;
  printk("probe cybit rotary\n");
  return 0;
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
