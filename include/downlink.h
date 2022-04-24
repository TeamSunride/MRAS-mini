//
// Created by Tom Danvers on 23/04/2022.
// 2022 TeamSunride.
//

#ifndef DOWNLINK_H
#define DOWNLINK_H

#include "RadioLib.h"

namespace downlink {

    // ===[ RADIO SETTINGS ]===

    const float frequency = 868.0;  // Carrier frequency in MHz
    const float bandwidth = 500.0;  // LoRa bandwidth in kHz
    const uint8_t spreadingFactor = 5;  // LoRa spreading factor
    const uint8_t codeRate = 5; // LoRa coding rate denominator.
    const uint8_t syncWord = 0x22;  // 2-byte LoRa sync word
    const int8_t power = 12; // output power in dBm

    // ===[ RADIO PIN DEFINITIONS ]===

    #if BUILD_ENV_NAME == dart

    #define CHIP_SELECT_PIN     10
    #define DIO1_PIN            5
    #define RESET_PIN           6
    #define BUSY_PIN            4
    #define RX_ENABLE_PIN       2
    #define TX_ENABLE_PIN       3

    # else

    // Default pin values for radio (with ARDUINO):
    #define CHIP_SELECT_PIN     10
    #define DIO1_PIN            2
    #define RESET_PIN           9
    #define BUSY_PIN            5
    #define RX_ENABLE_PIN       7
    #define TX_ENABLE_PIN       6

    #endif

    /**
     * Initialise the radio with the parameters corresponding to the selected build environment
     * Refer to `downlink.h` to set these parameters
     * @return RadioLib status code
     */
    int setupRadio();

    // this function is called when a complete packet
    // is transmitted by the module
    void setFlag();

    int transmit(uint8_t* data, size_t len);

    // https://community.platformio.org/t/platformio-doesnt-compile-when-header-contains-global-variables/6687
    // Store radio state globally
    extern int radioState;

    // flag to indicate that a packet was sent
    extern volatile bool radioAvailable;

    // disable interrupt when it's not needed
    extern volatile bool enableInterrupt;
}


#endif //DOWNLINK_H