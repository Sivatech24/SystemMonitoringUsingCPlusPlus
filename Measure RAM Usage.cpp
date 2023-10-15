#include <iostream>
#include <fstream>
#include <string>

// Function to retrieve RAM usage in kilobytes
long getRAMUsageKB() {
    std::ifstream meminfoFile("/proc/meminfo");
    if (!meminfoFile) {
        std::cerr << "Failed to open meminfo file." << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(meminfoFile, line)) {
        if (line.find("MemTotal:") == 0) {
            long totalMemoryKB;
            std::istringstream ss(line.substr(10));
            ss >> totalMemoryKB;
            return totalMemoryKB;
        }
    }

    return -1; // RAM usage not found
}

int main() {
    long totalRAMKB = getRAMUsageKB();
    if (totalRAMKB != -1) {
        std::cout << "Total RAM: " << totalRAMKB << " KB" << std::endl;
    } else {
        std::cerr << "Failed to retrieve RAM usage." << std::endl;
    }

    return 0;
}
