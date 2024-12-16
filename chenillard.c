#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/timer.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/jiffies.h>
#include <linux/io.h>

#define DRIVER_AUTHOR "Votre Nom"
#define DRIVER_DESC "Module Chenillard"
#define DRIVER_LICENSE "GPL"
#define GPIO_BASE 0xFF203000
#define NUM_LEDS 4

static struct proc_dir_entry *proc_dir;
static struct proc_dir_entry *proc_file;
static struct timer_list chenillard_timer;
static int vitesse = 1000;
static int pattern = 0x01;
static void __iomem *gpio_addr;

module_param(vitesse, int, 0644);
MODULE_PARM_DESC(vitesse, "Vitesse du chenillard en ms");

static void update_leds(void)
{
    iowrite32(pattern, gpio_addr);
    printk(KERN_INFO "LED pattern: 0x%02x\n", pattern);
}

static void timer_function(unsigned long data)
{
    update_leds();
    pattern = ((pattern << 1) | (pattern >> (NUM_LEDS-1))) & ((1 << NUM_LEDS) - 1);
    mod_timer(&chenillard_timer, jiffies + msecs_to_jiffies(vitesse));
}

static int chenille_proc_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Pattern actuel: 0x%02x\n", pattern);
    return 0;
}

static ssize_t chenille_proc_write(struct file *file, const char __user *buffer,
                                 size_t count, loff_t *ppos)
{
    char tmp[16];
    unsigned int new_pattern;
    
    if (count > sizeof(tmp))
        return -EINVAL;
        
    if (copy_from_user(tmp, buffer, count))
        return -EFAULT;
        
    tmp[count - 1] = '\0';
    
    if (kstrtouint(tmp, 0, &new_pattern) == 0) {
        pattern = new_pattern & ((1 << NUM_LEDS) - 1);
        update_leds();
        return count;
    }
    
    return -EINVAL;
}

static int chenille_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, chenille_proc_show, NULL);
}

static const struct file_operations chenille_fops = {
    .owner = THIS_MODULE,
    .open = chenille_proc_open,
    .read = seq_read,
    .write = chenille_proc_write,
    .llseek = seq_lseek,
    .release = single_release,
};

static int __init chenillard_init(void)
{
    gpio_addr = ioremap(GPIO_BASE, 4);
    if (!gpio_addr) {
        printk(KERN_ERR "Failed to map GPIO memory\n");
        return -ENOMEM;
    }

    proc_dir = proc_mkdir("ensea", NULL);
    if (!proc_dir) {
        iounmap(gpio_addr);
        return -ENOMEM;
    }
    
    proc_file = proc_create("chenille", 0666, proc_dir, &chenille_fops);
    if (!proc_file) {
        proc_remove(proc_dir);
        iounmap(gpio_addr);
        return -ENOMEM;
    }
    
    init_timer(&chenillard_timer);
    chenillard_timer.function = timer_function;
    chenillard_timer.data = 0;
    mod_timer(&chenillard_timer, jiffies + msecs_to_jiffies(vitesse));
    
    printk(KERN_INFO "Chenillard initialisé avec vitesse=%d ms\n", vitesse);
    return 0;
}

static void __exit chenillard_exit(void)
{
    del_timer(&chenillard_timer);
    
    iowrite32(0, gpio_addr);  // Éteint toutes les LEDs
    iounmap(gpio_addr);
    
    proc_remove(proc_file);
    proc_remove(proc_dir);
    printk(KERN_INFO "Chenillard arrêté\n");
}

module_init(chenillard_init);
module_exit(chenillard_exit);

MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
