#pragma once

#include "types.h"


//#include <iostream>

//#include "mathLib.h"
//#include "filtersLib.h"
//#include "spectrumLib.h"

namespace neuro_trace {

class LeBrainBit {
public:
    LeBrainBit(SensorPtr sensor);
    ~LeBrainBit();

    SensorSamplingFrequency ReadSamplingFrequency();

private:
    bool Connect();
    bool Disconnect();
    bool ExecCommand(SensorCommand command);

    
    /*
    //Read & write gain of device
    SensorGain readGain();

    //Read & write data offset of device
    SensorDataOffset readDataOffset();

    //Read & write firmware mode of device
    SensorFirmwareMode readFirmwareMode();

    //Get list of supported features by device
    std::vector<SensorFeature> getSupportedFeatures();

    //Get list of supported commands by device
    std::vector<SensorCommand> getSupportedCommands();

    //Get list of supported parameters by device
    std::vector<ParameterInfo> getSupportedParameters();

    //Get true result, if device supports current feature
    bool isSupportedFeature(SensorFeature feature);

    //Get true result, if device supports current command
    bool isSupportedCommand(SensorCommand command);

    //Get true result, if device supports current parameter
    bool isSupportedParameter(SensorParameter parameter);

    //Read & write name of device
    std::string readName();
    bool writeName(std::string name);

    //Read state of device
    SensorState readState();

    //Read address of device
    std::string readAddress();

    //Read & write serial number of device
    std::string readSerialNumber();
    bool writeSerialNumber(std::string serialNumber);

    //Read version of device
    SensorVersion readVersion();

    //Read battery power of device
    int32_t readBatteryPower();

    //Get count of channels
    int32_t getChannelsCount();

    //Get Family of device
    SensorFamily getFamily();


    // Callbacks
    //Add & remove Battery Power callback
    bool AddBatteryCallback();
    bool RemoveBatteryCallback();

    //Add & remove connection state callback
    bool AddConnectionStateCallback();
    bool RemoveConnectionStateCallback();

    //Add & remove signal data callback
    bool AddSignalCallbackBrainBit();
    bool RemoveSignalCallbackBrainBit();

    //Add & remove respiration data callback
    bool AddResistDataCallbackBrainBit();
    bool RemoveResistDataCallbackBrainBit();

    // =======================
    // || BRAINBIT CALLBACK ||
    // =======================

    bool AddSignalCallbackBrainBit_EmStArtifacts(MathLibSample* mathlib);
    bool RemoveSignalCallbackBrainBit_EmStArtifacts();

    bool AddSignalCallbackBrainBit_Filters(FiltersLibSample* mathlib);
    bool RemoveSignalCallbackBrainBit_Filters();

    bool AddSignalCallbackBrainBit_Spectrum(SpectrumLibSample* mathlib);
    bool RemoveSignalCallbackBrainBit_Spectrum();
    */

private:
    SensorPtr sensor_;

    /*
    //Handle of Battery Power Callback
    BattPowerListenerHandle battPowerHandle_{};

    //Handle of Connection State Device Callback
    SensorStateListenerHandle stateHandle_{};

    //Handle of Signal Data Device Callback
    BrainBitSignalDataListenerHandle signalDataHandle_{};

    //Handle of Resist Data Device Callback
    BrainBitResistDataListenerHandle resistDataHandle_{};

    //Handle of Signal Data Device Callback (Em_St_Artifacts)
    BrainBitSignalDataListenerHandle signalDataEmStArtifactsHandle_{};

    //Handle of Signal Data Device Callback (Filters)
    BrainBitSignalDataListenerHandle signalDataFiltersHandle_{};

    //Handle of Signal Data Device Callback (Spectrum)
    BrainBitSignalDataListenerHandle signalDataSpectrumHandle_{};
    */
};

}  // namespace neuro_trace
