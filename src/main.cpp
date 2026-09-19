#include "device_connector.h"
#include "le_brainbit.h"
#include "log.h"

#include <iostream>
#include <thread>

int main() {
    using namespace neuro_trace;

    Log::Instance().Info("Application start", 4);

    Log::Instance().Info("Searching device...");
    DeviceConnector device_connector;
    SensorPtr sensor = device_connector.GetFirstSensor();
    LeBrainBit brain_bit(std::move(sensor));
    SensorSamplingFrequency samplingFrequency = brain_bit.ReadSamplingFrequency();

    Log::Instance().Info("Sampling frequency: ", samplingFrequency);
    return 0;
}
