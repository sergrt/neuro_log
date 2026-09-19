#include "device_connector.h"
#include "log.h"

#include <array>
#include <chrono>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>

namespace {

SensorFamily kDeviceFilter[] = { SensorFamily::SensorLEBrainBitBlack };

}  // namespace

namespace neuro_trace {

DeviceConnector::DeviceConnector() {
    CreateScanner();
    AddSensorsCallbackScanner();
    StartScanner();
}

DeviceConnector::~DeviceConnector() {
    StopScanner();
}

void DeviceConnector::CreateScanner() {
    OpStatus create_scanner_result{};
    scanner_ = SensorScannerPtr(createScanner(kDeviceFilter, sizeof(kDeviceFilter), &create_scanner_result), freeScanner);

    if (!create_scanner_result.Success || !scanner_) {
        throw std::runtime_error(create_scanner_result.ErrorMsg);
    }
}

void DeviceConnector::StartScanner() {
    OpStatus start_scanner_result{};
    bool result = startScanner(scanner_.get(), &start_scanner_result);

    if (!result) {
        throw std::runtime_error(start_scanner_result.ErrorMsg);
    }
}

void DeviceConnector::StopScanner() {
    OpStatus result{};

    if (stopScanner(scanner_.get(), &result) == 0) {
        throw std::runtime_error(result.ErrorMsg);
    }
}

SensorPtr DeviceConnector::FindSensor() {

    SensorInfo sensorInfo{};
    while (true) {
        int32_t countDevices = 64;
        std::array<SensorInfo, 64> devices{};
        OpStatus enum_devices_result{};
        bool result = sensorsScanner(scanner_.get(), devices.data(), &countDevices, &enum_devices_result);

        if (!result) {
            throw std::runtime_error(enum_devices_result.ErrorMsg);
        }

        if (countDevices != 0) {
            sensorInfo = devices[0];
            //break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    //if (countDevices == 0) {
    //    throw std::runtime_error("Device count = 0");
    //}

    //SensorInfo sensorInfo = devices[0];


    OpStatus create_sensor_result{};
    SensorPtr sensor = SensorPtr(createSensor(scanner_.get(), sensorInfo, &create_sensor_result), freeSensor);

    if (!create_sensor_result.Success || !sensor) {
        throw std::runtime_error(create_sensor_result.ErrorMsg);
    }

    return sensor;
}

SensorPtr DeviceConnector::CreateSensor(const SensorInfo& sensorInfo) const {
    OpStatus status{};
    SensorPtr sensor = SensorPtr(createSensor(scanner_.get(), sensorInfo, &status), freeSensor);

    if (!status.Success || !sensor) {
        throw std::runtime_error(status.ErrorMsg);
    }

    return sensor;
}

SensorPtr DeviceConnector::GetFirstSensor() {
    SensorInfo sensorInfo{};
    {
        std::unique_lock lock(discoveredDevicesLock_);
        discoveredDevicesCv_.wait(lock, [this]() { return !discoveredDevices_.empty(); });
        sensorInfo = discoveredDevices_[0];
    }
    return CreateSensor(sensorInfo);
}

void DeviceConnector::SensorsCallbackBridge(SensorScanner* scanner, SensorInfo* devices, int32_t deviceCount, void* userData) {
    DeviceConnector* instance = static_cast<DeviceConnector*>(userData);
    return instance->SensorsCallback(scanner, devices, deviceCount);
}

void DeviceConnector::SensorsCallback(SensorScanner* scanner, SensorInfo* devices, int32_t deviceCount) {
    std::string log_string = "Sensor callback called";
    Log::Instance().Info(log_string);

    for (int32_t i = 0; i < deviceCount; ++i) {
        std::cout << "    Address: " << devices[i].Address << "\n";
        std::cout << "    Name: " << devices[i].Name << "\n";
        std::cout << "    Pairing required: " << devices[i].PairingRequired << "\n";
        std::cout << "    RSSI: " << devices[i].RSSI << "\n";
        std::cout << "    SensFamily: " << (devices[i].SensFamily == SensorFamily::SensorLEBrainBitBlack ? "BrainBit black" : "<Unknown>") << "\n";
        std::cout << "    SensModel: " << devices[i].SensModel << "\n";
        std::cout << "    SerialNumber: " << devices[i].SerialNumber << "\n";
    }

    std::vector<SensorInfo> tmpDevices;
    tmpDevices.reserve(deviceCount);
    for (int32_t i = 0; i < deviceCount; ++i) {
        tmpDevices.push_back(devices[i]);
    }

    {
        std::lock_guard lock(discoveredDevicesLock_);
        discoveredDevices_.swap(tmpDevices);
    }
    discoveredDevicesCv_.notify_one();
}

bool DeviceConnector::AddSensorsCallbackScanner()
{
    OpStatus status{};
    bool result = addSensorsCallbackScanner(scanner_.get()
        , &DeviceConnector::SensorsCallbackBridge
        , &sensorCallbackHandle_
        , static_cast<void*>(this)
        , &status);
    if (!result) {
        throw std::runtime_error(status.ErrorMsg);
    }
    return true;
}

bool DeviceConnector::RemoveSensorsCallbackScanner()
{
    if (!sensorCallbackHandle_) {
        throw std::runtime_error("Null Sensors callback!");
    }
    removeSensorsCallbackScanner(sensorCallbackHandle_);
    return true;
}

}  // namespace neuro_trace
