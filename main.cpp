#include <iostream>
#include <iomanip>
#include <libusb.h>

void print_device_info(libusb_device *dev) {
    libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
        std::cerr << "[-] Failed to get device descriptor" << std::endl;
        return;
    }

    std::cout << "[+] Found USB Device: VID 0x" 
              << std::hex << std::setw(4) << std::setfill('0') << desc.idVendor
              << ", PID 0x" 
              << std::hex << std::setw(4) << std::setfill('0') << desc.idProduct
              << " (Interfaces: " << std::dec << (int)desc.bNumConfigurations << ")"
              << std::endl;
}

int main() {
    libusb_context *ctx = nullptr;
    libusb_device **list = nullptr;

    int result = libusb_init(&ctx);
    if (result < 0) {
        std::cerr << "[-] Initialization Error: " << result << std::endl;
        return 1;
    }

    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_INFO);

    ssize_t count = libusb_get_device_list(ctx, &list);
    if (count < 0) {
        std::cerr << "[-] Get Device Error" << std::endl;
        libusb_exit(ctx);
        return 1;
    }

    std::cout << "==========================================" << std::endl;
    std::cout << "  Scanning for connected USB devices...   " << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "[*] Total USB devices found: " << count << "\n" << std::endl;

    for (ssize_t i = 0; i < count; ++i) { 
        print_device_info(list[i]);
    }

    libusb_free_device_list(list, 1);
    libusb_exit(ctx);

    return 0;
}