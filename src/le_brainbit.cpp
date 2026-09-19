#include "le_brainbit.h"

#include <sdk_api.h>

#include <stdexcept>

namespace neuro_trace {

LeBrainBit::LeBrainBit(SensorPtr sensor)
    : sensor_(std::move(sensor)) {
    Connect();
}

LeBrainBit::~LeBrainBit() {
    Disconnect();
}

bool LeBrainBit::Connect() {
    OpStatus status{};
    const bool result = connectSensor(sensor_.get(), &status);

    if (!result) {
        throw std::runtime_error(status.ErrorMsg);
    }

    return true;
}

bool LeBrainBit::Disconnect() {
    OpStatus status{};
    const bool result = disconnectSensor(sensor_.get(), &status);

    if (!result) {
        throw std::invalid_argument(status.ErrorMsg);
    }

    return true;
}

bool LeBrainBit::ExecCommand(SensorCommand command) {
    return true;
}

SensorSamplingFrequency LeBrainBit::ReadSamplingFrequency() {
    OpStatus status{};
    SensorSamplingFrequency samplingFrequency{};
    const bool result = readSamplingFrequencySensor(sensor_.get(), &samplingFrequency, &status);
    
    if (!result) {
        throw std::invalid_argument(status.ErrorMsg);
    }

    return samplingFrequency;
}

}  // namespace neuro_trace
