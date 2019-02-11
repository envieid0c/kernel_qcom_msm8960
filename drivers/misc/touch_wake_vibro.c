/*
 * Author: Sudokamikaze <pulshencode@outlook.com>
 * Original code author: Chad Froebel <chadfroebel@gmail.com>
 * 
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/*
 * Possible values are :
 *
 *   0 - disabled (default)
 *   1 - Enable DT2W vibration
*/

#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/dt2w_vibro.h>

int d2_vibro;

/* sysfs interface for "vibration toggle" */
static ssize_t dt_wake_vibro_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
return sprintf(buf, "%d\n", d2_vibro);
}

static ssize_t dt_wake_vibro_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

int new_vibro;

sscanf(buf, "%du", &new_vibro);

if (new_vibro >= DT_VIBRO_DISABLED && new_vibro <= DT_VIBRO_ENABLED) {
    /* update only if valid value provided */
    d2_vibro = new_vibro;
}

return count;
}


static struct kobj_attribute d2_vibro_attribute =
__ATTR(d2_vibration, 0666, dt_wake_vibro_show, dt_wake_vibro_store);

static struct attribute *d2_vibro_attrs[] = {
&d2_vibro_attribute.attr,
NULL,
};

static struct attribute_group d2_vibro_attr_group = {
.attrs = d2_vibro_attrs,
};

/* Initialize D2TW sysfs folder */
static struct kobject *d2_vibro_kobj;

int d2_vibro_init(void)
{
    int d2_vibro_retval;

    d2_vibro = DT_VIBRO_DISABLED; /* DT2W vibration disabled by default */

    d2_vibro_kobj = kobject_create_and_add("d2_vibro", kernel_kobj);
    if (!d2_vibro_kobj) {
	    return -ENOMEM;
    }

    d2_vibro_retval = sysfs_create_group(d2_vibro_kobj, &d2_vibro_attr_group);

    if (d2_vibro_retval)
	kobject_put(d2_vibro_kobj);

    if (d2_vibro_retval)
	kobject_put(d2_vibro_kobj);

    return (d2_vibro_retval);
}

void d2_vibro_exit(void)
{
    kobject_put(d2_vibro_kobj);
}

module_init(d2_vibro_init);
module_exit(d2_vibro_exit);