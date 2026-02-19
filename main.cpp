#include<iostream>
#include<sys/statvfs.h>  

int main(int argc, char const *argv[]) {
    struct statvfs buffer;
    if (statvfs("/", &buffer) == 0) {
        unsigned long long available_bytes = buffer.f_bavail * buffer.f_frsize;
        long long total_bytes = (long long)buffer.f_blocks * buffer.f_frsize;
        if (argc == 3) {
            std::string arg1 = argv[1];
            std::string arg2 = argv[2];
            if (arg1 == "disk") {
                if (arg2 == "space") {
                    std::cout << "sda1 | Total: " << total_bytes / 1073741824 << "GB | Used: " << total_bytes / 1073741824 - available_bytes / 1073741824 << "GB | Available: " << available_bytes / 1073741824 << "GB" << "\n";
                }

            }
        }
        
    }
    return 0;
}