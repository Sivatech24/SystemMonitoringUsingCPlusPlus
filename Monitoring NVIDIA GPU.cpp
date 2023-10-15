#include <iostream>
#include <nvml.h>

int main() {
    nvmlReturn_t result;
    result = nvmlInit();

    if (result != NVML_SUCCESS) {
        std::cerr << "Failed to initialize NVML: " << nvmlErrorString(result) << std::endl;
        return 1;
    }

    int deviceCount;
    result = nvmlDeviceGetCount(&deviceCount);

    if (result != NVML_SUCCESS) {
        std::cerr << "Failed to query device count: " << nvmlErrorString(result) << std::endl;
        nvmlShutdown();
        return 1;
    }

    for (int i = 0; i < deviceCount; i++) {
        nvmlDevice_t device;
        result = nvmlDeviceGetHandleByIndex(i, &device);

        if (result != NVML_SUCCESS) {
            std::cerr << "Failed to get device handle: " << nvmlErrorString(result) << std::endl;
            continue;
        }

        char name[NVML_DEVICE_NAME_BUFFER_SIZE];
        result = nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_BUFFER_SIZE);

        if (result == NVML_SUCCESS) {
            std::cout << "GPU " << i << " Name: " << name << std::endl;
        }

        nvmlUtilization_t utilization;
        result = nvmlDeviceGetUtilizationRates(device, &utilization);

        if (result == NVML_SUCCESS) {
            std::cout << "GPU " << i << " Utilization (GPU/VRAM): " << utilization.gpu << "% / " << utilization.memory << "%" << std::endl;
        }
    }

    nvmlShutdown();
    return 0;
}
