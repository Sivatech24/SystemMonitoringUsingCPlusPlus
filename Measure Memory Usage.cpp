#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
// Function to retrieve memory usage in kilobytes
long getMemoryUsageKB() {
    std::stringstream ss;
    std::ifstream statusFile("/proc/self/status");
    if (!statusFile) {
        std::cerr << "Failed to open status file." << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(statusFile, line)) {
        if (line.compare(0, 7, "VmSize:") == 0) {
            long memorySizeKB;
            std::istringstream ss(line.substr(7));
            ss >> memorySizeKB;
            return memorySizeKB;
        }
    }

    return -1; // Memory usage not found
}

int main() {
    long memoryUsageKB = getMemoryUsageKB();
    if (memoryUsageKB != -1) {
        std::cout << "Memory Usage: " << memoryUsageKB << " KB" << std::endl;
    } else {
        std::cerr << "Failed to retrieve memory usage." << std::endl;
    }

    return 0;
}
