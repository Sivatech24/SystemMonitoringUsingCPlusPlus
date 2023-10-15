#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
void monitorResources() {
    std::stringstream ss;
    while (true) {
        std::ifstream statFile("/proc/stat");
        std::ifstream meminfoFile("/proc/meminfo");

        if (!statFile || !meminfoFile) {
            std::cerr << "Failed to open resource files." << std::endl;
            return;
        }

        std::string line;
        double cpuUsage = 0.0;
        long totalMemory = 0, freeMemory = 0;

        // Parse CPU usage
        while (std::getline(statFile, line) && line.compare(0, 3, "cpu") == 0) {
            std::istringstream ss(line);
            std::string cpu;
            long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
            ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

            if (cpu == "cpu") {
                // Calculate CPU usage percentage
                long prevIdle = idle + iowait;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::getline(statFile, line);
                ss.clear();
                ss.str(line);
                ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

                long idleTime = idle + iowait - prevIdle;
                long totalTime = user + nice + system + idle + iowait + irq + softirq + steal;
                cpuUsage = 100.0 * (totalTime - idleTime) / totalTime;
                break;
            }
        }

        // Parse memory usage
        while (std::getline(meminfoFile, line)) {
            if (line.find("MemTotal:") == 0) {
                std::istringstream ss(line);
                std::string label;
                ss >> label >> totalMemory;
            }
            else if (line.find("MemFree:") == 0) {
                std::istringstream ss(line);
                std::string label;
                ss >> label >> freeMemory;
            }
        }

        // Calculate used memory
        long usedMemory = totalMemory - freeMemory;

        std::cout << "CPU Usage: " << cpuUsage << "%" << std::endl;
        std::cout << "Used Memory: " << usedMemory / 1024 << " KB" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    }
}

int main() {
    monitorResources();
    return 0;
}
