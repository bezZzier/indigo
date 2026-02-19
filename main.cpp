#include <iostream>
#include <sys/statvfs.h>
#include <mntent.h>
#include <string>

int main(int argc, char const *argv[]) {
    // 1. Check if the user typed 'indigo disk space'
    if (argc == 3) {
        std::string arg1 = argv[1];
        std::string arg2 = argv[2];

        if (arg1 == "disk" && arg2 == "space") {
            struct mntent *ent;
            FILE *file = setmntent("/etc/mtab", "r");

            if (file == NULL) {
                std::cerr << "Could not read partitions\n";
                return 1;
            }

            // 2. Loop through every partition in the system
            while ((ent = getmntent(file)) != NULL) {
                std::string device = ent->mnt_fsname;
                
                // Only look at real hardware devices
                if (device.find("/dev/") == 0) {
                    struct statvfs buffer;

                    if (statvfs(ent->mnt_dir, &buffer) == 0) {
                        unsigned long long available_bytes = (unsigned long long)buffer.f_bavail * buffer.f_frsize;
                        unsigned long long total_bytes = (unsigned long long)buffer.f_blocks * buffer.f_frsize;

                        long long total_gb = total_bytes / 1073741824;
                        long long available_gb = available_bytes / 1073741824;
                        long long used_gb = total_gb - available_gb;

                        // 3. Logic Filter: Skip the clutter (loop devices/system partitions < 1GB)
                        if (total_gb < 1) {
                            continue;
                        }

                        // 4. Print in your specific format
                        std::cout << ent->mnt_fsname << " | Total: " << total_gb 
                                  << "GB | Used: " << used_gb 
                                  << "GB | Available: " << available_gb << "GB" << "\n";
                    }
                }
            }
            endmntent(file);
        }
    }
    return 0;
}