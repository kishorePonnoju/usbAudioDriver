/***************************************************************************//**
*  \file       usb_driver.c
*
*  \details    Simple USB driver explanation
*
*  \author     EmbeTronicX
*
*  \Tested with kernel 5.3.0-42-generic
*
*******************************************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/usb.h>

/*
** This macro is used to tell the driver to use old method or new method.
** 
**  If it is 0, then driver will use old method. ie: __init and __exit
**  If it is non zero, then driver will use new method. ie: module_usb_driver
*/
#define IS_NEW_METHOD_USED  ( 1 )


/* #define USB_VENDOR_ID       ( 0x22d9 )      //USB device's vendor ID */
/* #define USB_PRODUCT_ID      ( 0x2764 )      //USB device's product ID */

#define USB_VENDOR_ID       ( 0x0d8c )      //USB device's vendor ID
#define USB_PRODUCT_ID      ( 0x013c )      //USB device's product ID

#define PRINT_USB_INTERFACE_DESCRIPTOR( i )                         \
{                                                                   \
    pr_info("USB_INTERFACE_DESCRIPTOR:\n");                         \
    pr_info("-----------------------------\n");                     \
    pr_info("bLength: 0x%x\n", i.bLength);                          \
    pr_info("bDescriptorType: 0x%x\n", i.bDescriptorType);          \
    pr_info("bInterfaceNumber: 0x%x\n", i.bInterfaceNumber);        \
    pr_info("bAlternateSetting: 0x%x\n", i.bAlternateSetting);      \
    pr_info("bNumEndpoints: 0x%x\n", i.bNumEndpoints);              \
    pr_info("bInterfaceClass: 0x%x\n", i.bInterfaceClass);          \
    pr_info("bInterfaceSubClass: 0x%x\n", i.bInterfaceSubClass);    \
    pr_info("bInterfaceProtocol: 0x%x\n", i.bInterfaceProtocol);    \
    pr_info("iInterface: 0x%x\n", i.iInterface);                    \
    pr_info("\n");                                                  \
}

#define PRINT_USB_ENDPOINT_DESCRIPTOR( e )                          \
{                                                                   \
    pr_info("USB_ENDPOINT_DESCRIPTOR:\n");                          \
    pr_info("------------------------\n");                          \
    pr_info("bLength: 0x%x\n", e.bLength);                          \
    pr_info("bDescriptorType: 0x%x\n", e.bDescriptorType);          \
    pr_info("bEndPointAddress: 0x%x\n", e.bEndpointAddress);        \
    pr_info("bmAttributes: 0x%x\n", e.bmAttributes);                \
    pr_info("wMaxPacketSize: 0x%x\n", e.wMaxPacketSize);            \
    pr_info("bInterval: 0x%x\n", e.bInterval);                      \
    pr_info("\n");                                                  \
}

/*
** This function will be called when USB device is inserted.
*/

/* The probe() method is invoked by khubd after device */
/* enumeration. The first argument, interface, contains information */
/* gleaned during the enumeration process. id is the entry in the */
/* driver's usb_device_id table that matches the values read from */
/* the Usb stick. tele_probe() is based on skel_probe() */
/* defined in drivers/usb/usb-skeleton.c*/

static int usb_probe(struct usb_interface *interface,
                        const struct usb_device_id *id)
{
    unsigned int i;
    unsigned int endpoints_count;
    struct usb_host_interface *iface_desc = interface->cur_altsetting;

    dev_info(&interface->dev, "USB Driver Probed: Vendor ID : 0x%02x,\t"
             "Product ID : 0x%02x\n", id->idVendor, id->idProduct);
    printk("probe called succesfully \n");
             
    endpoints_count = iface_desc->desc.bNumEndpoints;
    
    PRINT_USB_INTERFACE_DESCRIPTOR(iface_desc->desc);
    
     for ( i = 0; i < endpoints_count; i++ ) {
          PRINT_USB_ENDPOINT_DESCRIPTOR(iface_desc->endpoint[i].desc);
     }
    return 0;  //return 0 indicates we are managing this device
}

/*
** This function will be called when USB device is removed.
*/
static void usb_disconnect(struct usb_interface *interface)
{
    dev_info(&interface->dev, "USB Driver Disconnected\n");
}

//usb_device_id provides a list of different types of USB devices that the driver supports
const struct usb_device_id usb_table[] = {
    { USB_DEVICE( USB_VENDOR_ID, USB_PRODUCT_ID ) },    //Put your USB device's Vendor and Product ID
    { } /* Terminating entry */
};

//This enable the linux hotplug system to load the driver automatically when the device is plugged in
MODULE_DEVICE_TABLE(usb, usb_table);

//The structure needs to do is register with the linux subsystem
static struct usb_driver usb_driver = {
    .name       = "kishore USB Driver",
    .probe      = usb_probe,
    .disconnect = usb_disconnect,
    .id_table   = usb_table,
};

/* #if ( IS_NEW_METHOD_USED == 0 ) */
#if 1
//This will replaces module_init and module_exit.
module_usb_driver(usb_driver);

#else
static int __init usb_init(void)
{
    //register the USB device
    printk("kp usb init is called \n");
    return usb_register(&usb_driver);
}

static void __exit usb_exit(void)
{
    //deregister the USB device
    printk("exit usb \n");
    usb_deregister(&usb_driver);
}

module_init(usb_init);
module_exit(usb_exit);
#endif

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kishorePonnoju<kishore.kumar667@gmail.com>");
MODULE_DESCRIPTION("A simple device driver - USB Driver");
MODULE_VERSION("1.30");
