/*
 * lunix-chrdev.c
 *
 * Implementation of character devices
 * for Lunix:TNG
 *
 * < Your name here >
 *
 */

#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/cdev.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mmzone.h>
#include <linux/vmalloc.h>
#include <linux/spinlock.h>

#include "lunix.h"
#include "lunix-chrdev.h"
#include "lunix-lookup.h"

/*
 * Global data
 */
struct cdev lunix_chrdev_cdev;

/*
 * Just a quick [unlocked] check to see if the cached
 * chrdev state needs to be updated from sensor measurements.
 */
/*
 * Declare a prototype so we can define the "unused" attribute and keep
 * the compiler happy. This function is not yet used, because this helpcode
 * is a stub.
 */
static int __attribute__((unused)) lunix_chrdev_state_needs_refresh(struct lunix_chrdev_state_struct *);
static int lunix_chrdev_state_needs_refresh(struct lunix_chrdev_state_struct *state)
{
    struct lunix_sensor_struct *sensor;

    // Assign the sensor of the state that is passed as an argument to the sensored declared above
    // Call WARN if unsuccesfull;
    WARN_ON(!(sensor = state->sensor));

    /* ? */ // TODO

    /* The following return is bogus, just for the stub to compile */
    return 0; /* ? */ // TODO
}

/*
 * Updates the cached state of a character device
 * based on sensor data. Must be called with the
 * character device state lock held.
 */
static int lunix_chrdev_state_update(struct lunix_chrdev_state_struct *state)
{
    struct lunix_sensor_struct __attribute__((unused)) * sensor;
    sensor = state->sensor;
    debug("leaving\n");

    /*
     * Grab the raw data quickly, hold the
     * spinlock for as little as possible.
     */
    /* ? */ // TODO
    /* Why use spinlocks? See LDD3, p. 119 */

    /*
     * Any new data available?
     */
    /* ? */ // TODO

    /*
     * Now we can take our time to format them,
     * holding only the private state semaphore
     */

    /* ? */ // TODO

    debug("leaving\n");
    return 0;
}

/*************************************
 * Implementation of file operations
 * for the Lunix character device
 *************************************/

static int lunix_chrdev_open(struct inode *inode, struct file *filp)
{
    /* Declarations */
    struct lunix_chrdev_state_struct *state;
    unsigned int minor_number;
    unsigned int sensor_number;
    /* ? */

    int ret;

    debug("entering\n");
    ret = -ENODEV;
    if ((ret = nonseekable_open(inode, filp)) < 0)
        goto out;

    /*
     * Associate this open file with the relevant sensor based on
     * the minor number of the device node [/dev/sensor<NO>-<TYPE>]
     */
    filp->private_data = state;

    /* Allocate a new Lunix character device private state structure */

    // Get the minor number of the file openned
    minor_number = iminor(inode);
    sensor_number = minor_number >> 3;

    // Allocate a new state struct initialized to 0
    state = kzalloc(sizeof(*state), GFP_KERNEL);

    // Set the fields of the struct to point at the corect sensor struct and correct type
    // Based on the minor number
    state->sensor = &lunix_sensors[sensor_number];
    state->type = minor_number - (sensor_number);

    // initialize semaphore
    init_MUTEX(state->lock);

    /* ? */

out:
    debug("leaving, with ret = %d\n", ret);
    return ret;
}

static int lunix_chrdev_release(struct inode *inode, struct file *filp)
{
    /* ? */
    kfree(filp->private_data);
    return 0;
}

static long lunix_chrdev_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    /* Why? */
    // There is no reason to send any "commands" to the device (?)
    return -EINVAL;
}

static ssize_t lunix_chrdev_read(struct file *filp, char __user *usrbuf, size_t cnt, loff_t *f_pos)
{
    ssize_t ret;

    struct lunix_sensor_struct *sensor;
    struct lunix_chrdev_state_struct *state;

    state = filp->private_data;
    WARN_ON(!state);

    sensor = state->sensor;
    WARN_ON(!sensor);

    /* Lock? */
    // LDD3, page 112
    if (down_interruptible(&state->sem))
        return -ERESTARTSYS;

    /*
     * If the cached character device state needs to be
     * updated by actual sensor data (i.e. we need to report
     * on a "fresh" measurement, do so
     */
    if (*f_pos == 0)
    {
        while (lunix_chrdev_state_update(state) == -EAGAIN)
        {
            /* ? */ // TODO
            /* The process needs to sleep */
            /* See LDD3, page 153 for a hint */
        }
    }

    /* End of file */
    /* ? */ // TODO

    /* Determine the number of cached bytes to copy to userspace */
    /* ? */ // TODO

    /* Auto-rewind on EOF mode? */
    /* ? */ // TODO

    /*
     * The next two lines  are just meant to suppress a compiler warning
     * for the "unused" out: label, and for the uninitialized "ret" value.
     * It's true, this helpcode is a stub, and doesn't use them properly.
     * Remove them when you've started working on this code.
     */
    ret = -ENODEV;
    goto out;
out:
    /* Unlock? */
    // LDD3, page 113
    up(&state->sem);

    return ret;
}

static int lunix_chrdev_mmap(struct file *filp, struct vm_area_struct *vma)
{
    return -EINVAL;
}

static struct file_operations lunix_chrdev_fops =
    {
        .owner = THIS_MODULE,
        .open = lunix_chrdev_open,
        .release = lunix_chrdev_release,
        .read = lunix_chrdev_read,
        .unlocked_ioctl = lunix_chrdev_ioctl,
        .mmap = lunix_chrdev_mmap

};

int lunix_chrdev_init(void)
{
    /*
     * Register the character device with the kernel, asking for
     * a range of minor numbers (number of sensors * 8 measurements / sensor)
     * beginning with LINUX_CHRDEV_MAJOR:0
     */
    int ret;
    dev_t dev_no;
    unsigned int lunix_minor_cnt = lunix_sensor_cnt << 3;

    debug("initializing character device\n");
    cdev_init(&lunix_chrdev_cdev, &lunix_chrdev_fops);
    lunix_chrdev_cdev.owner = THIS_MODULE;

    dev_no = MKDEV(LUNIX_CHRDEV_MAJOR, 0);

    /* ? */
    // Done: Same as LDD3 page 48
    ret = register_chrdev_region(dev_no, lunix_minor_cnt, "lunix-tng");
    /* register_chrdev_region? */

    // /* Since this code is a stub, exit early */
    // return 0;

    if (ret < 0)
    {
        debug("failed to register region, ret = %d\n", ret);
        goto out;
    }

    /* ? */
    // LDD3 page 56
    // Not completely sure about 3rd parameter
    ret = cdev_add(&lunix_chrdev_cdev, dev_no, lunix_minor_cnt);
    /* cdev_add? */

    if (ret < 0)
    {
        debug("failed to add character device\n");
        goto out_with_chrdev_region;
    }
    debug("completed successfully\n");
    return 0;

out_with_chrdev_region:
    unregister_chrdev_region(dev_no, lunix_minor_cnt);
out:
    return ret;
}

void lunix_chrdev_destroy(void)
{
    dev_t dev_no;
    unsigned int lunix_minor_cnt = lunix_sensor_cnt << 3;

    debug("entering\n");
    dev_no = MKDEV(LUNIX_CHRDEV_MAJOR, 0);
    cdev_del(&lunix_chrdev_cdev);
    unregister_chrdev_region(dev_no, lunix_minor_cnt);
    debug("leaving\n");
}
