#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/timer.h>
#include <linux/seq_file.h>

#define DRIVER_AUTHOR "Christophe Barès"
#define DRIVER_DESC "Hello world Module"
#define DRIVER_LICENSE "GPL"

static struct proc_dir_entry *proc_file;
static int value=0;
module_param(value, int, 0644);
MODULE_PARM_DESC(value, "valeur...");

static int hello_proc_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Value = %d\n", value);
    return 0;
}

static int hello_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, hello_proc_show, NULL);
}

static const struct file_operations hello_fops = {
    .owner = THIS_MODULE,
    .open = hello_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int __init hello_init(void)
{
    printk("Hello User %d \r\n", value); 
    proc_file = proc_create("hello", 0444, NULL, &hello_fops);
    if (proc_file == NULL) {
        printk(KERN_ERR "Error: Could not create proc file\n");
        return -ENOMEM;
    }
    printk(KERN_INFO "Hello: module loaded, proc file created\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Bye bye...\n");
    proc_remove(proc_file);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
