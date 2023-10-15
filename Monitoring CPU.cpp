#include <iostream>
#include <windows.h>

int main() {
    ULONGLONG prevIdleTime = 0, prevKernelTime = 0, prevUserTime = 0;

    while (true) {
        FILETIME idleTime, kernelTime, userTime;
        if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
            ULONGLONG idle = ((reinterpret_cast<ULARGE_INTEGER*>(&idleTime))->QuadPart - prevIdleTime);
            ULONGLONG kernel = ((reinterpret_cast<ULARGE_INTEGER*>(&kernelTime))->QuadPart - prevKernelTime);
            ULONGLONG user = ((reinterpret_cast<ULARGE_INTEGER*>(&userTime))->QuadPart - prevUserTime);

            double total = static_cast<double>(kernel + user);
            double cpuUsage = 100.0 - (static_cast<double>(idle) / total * 100.0);

            std::cout << "CPU Usage: " << cpuUsage << "%" << std::endl;

            prevIdleTime = (reinterpret_cast<ULARGE_INTEGER*>(&idleTime))->QuadPart;
            prevKernelTime = (reinterpret_cast<ULARGE_INTEGER*>(&kernelTime))->QuadPart;
            prevUserTime = (reinterpret_cast<ULARGE_INTEGER*>(&userTime))->QuadPart;
        }

        // You can add memory and GPU monitoring here
        // Memory monitoring may involve platform-specific code or libraries.
        // GPU monitoring typically requires vendor-specific libraries or APIs.

        Sleep(1000); // Sleep for 1 second
    }

    return 0;
}
