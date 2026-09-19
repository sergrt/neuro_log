#include "device_connector.h"
#include "le_brainbit.h"
#include "log.h"

#include <iostream>
#include <thread>

int main() {
    using namespace neuro_trace;

    LOG_INFO("Application start");
    LOG_INFO("Searching device...");

    DeviceConnector device_connector;
    SensorPtr sensor = device_connector.GetFirstSensor();
    LeBrainBit brain_bit(std::move(sensor));
    SensorSamplingFrequency samplingFrequency = brain_bit.ReadSamplingFrequency();

    LOG_INFO("Sampling frequency: ", samplingFrequency);
    return 0;
}
