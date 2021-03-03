# usbAudioDriver
Usb audio Driver for Quantum USB Sound Card QHM 623  device 


Disable the by default existing Usb driver present in Host machine.


$lsusb
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
Bus 002 Device 013: ID 0d8c:013c C-Media Electronics, Inc. CM108 Audio Controller
Bus 002 Device 003: ID 0e0f:0002 VMware, Inc. Virtual USB Hub
Bus 002 Device 002: ID 0e0f:0003 VMware, Inc. Virtual Mouse
Bus 002 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub


$ lsusb -t
/:  Bus 02.Port 1: Dev 1, Class=root_hub, Driver=uhci_hcd/2p, 12M
    |__ Port 1: Dev 2, If 0, Class=Human Interface Device, Driver=usbhid, 12M
    |__ Port 2: Dev 3, If 0, Class=Hub, Driver=hub/7p, 12M
        |__ Port 1: Dev 5, If 2, Class=Audio, Driver=snd-usb-audio, 12M
        |__ Port 1: Dev 5, If 0, Class=Audio, Driver=snd-usb-audio, 12M
        |__ Port 1: Dev 5, If 3, Class=Human Interface Device, Driver=usbhid, 12M
        |__ Port 1: Dev 5, If 1, Class=Audio, Driver=snd-usb-audio, 12M
/:  Bus 01.Port 1: Dev 1, Class=root_hub, Driver=ehci-pci/6p, 480M


$modinfo snd-usb-audio  | grep v0D8C

blocklist  the driver in yourhost pc at /etc/modprobe.d/blacklist.conf
like "blacklist snd-usb-audio"

Then after your driver will start working.
