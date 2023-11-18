sudo insmod /lib/modules/$(uname -r)/kernel/drivers/usb/serial/usbserial.ko
sudo insmod /lib/modules/$(uname -r)/kernel/drivers/usb/serial/P2_driver.ko

echo "Modules loaded successfully"
