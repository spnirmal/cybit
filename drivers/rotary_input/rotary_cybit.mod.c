#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x2260124d, "platform_driver_unregister" },
	{ 0x92997ed8, "_printk" },
	{ 0x668df3d6, "__platform_driver_register" },
	{ 0x474e54d2, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Ccustom,cybit-rotary");
MODULE_ALIAS("of:N*T*Ccustom,cybit-rotaryC*");

MODULE_INFO(srcversion, "B692A5D630807D02E06E422");
