#include <linux/module.h>
#include <linux/printk.h>

int init_module() {

  pr_info("hwllo world\n");

  return 0;
}

void cleanup_module() { pr_info("goodbye world"); }

MODULE_LICENSE("GPL");
