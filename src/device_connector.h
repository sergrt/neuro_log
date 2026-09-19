#pragma once

#include "types.h"

#include <condition_variable>
#include <mutex>
#include <vector>

namespace neuro_trace {

class DeviceConnector final {
public:
    DeviceConnector();
    ~DeviceConnector();
    // TODO: add "delete" versions of ctors and operator=

    SensorPtr FindSensor();
    SensorPtr GetFirstSensor();

private:
    void CreateScanner();
    void StartScanner();
    void StopScanner();
    SensorPtr CreateSensor(const SensorInfo& sensorInfo) const;

    static void SensorsCallbackBridge(SensorScanner* scanner, SensorInfo* devices, int32_t deviceCount, void* userData);
    void SensorsCallback(SensorScanner* scanner, SensorInfo* devices, int32_t deviceCount);

    bool AddSensorsCallbackScanner();
    bool RemoveSensorsCallbackScanner();

    SensorScannerPtr scanner_{nullptr, freeScanner};
    SensorsListenerHandle sensorCallbackHandle_{};
    
    std::mutex discoveredDevicesLock_;
    std::condition_variable discoveredDevicesCv_;
    std::vector<SensorInfo> discoveredDevices_;
};

}  // namespace neuro_trace
