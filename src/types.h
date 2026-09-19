#include <sdk_api.h>

#include <memory>

namespace neuro_trace {

using SensorPtr = std::unique_ptr<Sensor, decltype(&freeSensor)>;
using SensorScannerPtr = std::unique_ptr<SensorScanner, decltype(&freeScanner)>;

}  // namespace neuro_trace
