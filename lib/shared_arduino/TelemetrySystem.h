//
// Created by Tom Danvers on 05/01/2023.
//

#ifndef MRAS_TELEMETRYSYSTEM_H
#define MRAS_TELEMETRYSYSTEM_H


#include "Subsystem.h"
#include "RadioLib.h"
#include "MRAS_Config.h"
#include "TelemetryMessage.h"
#include "system_messages/QueueTelemetryMessageMsg.h"
#include "system_messages/ReceivedTelemetryMessageMsg.h"

class TelemetrySystem : public Subsystem {
protected:
    // create subsystem boilerplate
    SUBSYSTEM_NAME("TelemetrySystem")
    SUBSYSTEM_NO_MESSAGE_HANDLER

    // create setup and loop functions
    int8_t setup() override;

    SX1262 radio = new Module(RADIO_CHIP_SELECT_PIN,
                              RADIO_DIO1_PIN,
                              RADIO_RESET_PIN,
                              RADIO_BUSY_PIN,
                              RADIO_SPI_BUS);

    enum TelemetrySystemState {
        IDLE,
        TX,
        RX
    } telemetry_system_state = IDLE;

    int16_t radio_state = 0;

protected:

    QueueTelemetryMessageMsg* get_next_message();

    void transmit_next_message();
    void start_receiving_next_message(uint32_t timeout = 0xFFFFFF);

    /**
     * After the radio is done receiving a new message, read this message from the radio buffer and output the result
     * into the provided ReceivedTelemetryMessageMsg.
     * @param output A reference to a ReceivedTelemetryMessageMsg where the output message is stored
     * @param receive_again Whether to immediately start receiving data with the radio after reading from
     * the radio buffer.
     * @return True if the operation was a success, otherwise false (such as in the case of a CRC error)
     */
    bool read_new_message_from_buffer(ReceivedTelemetryMessageMsg* &output, bool receive_again = true);

public:
    explicit TelemetrySystem(uint8_t id) : Subsystem(id) {}
    int16_t get_radio_state() const;
};


#endif //MRAS_TELEMETRYSYSTEM_H
