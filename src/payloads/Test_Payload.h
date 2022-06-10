//
// Created by Tom Danvers on 07/05/2022.
// 2022 TeamSunride.
//

#ifndef TEST_PAYLOAD_H
#define TEST_PAYLOAD_H

#include "downlink.h"

struct Test_Payload {
    downlink::PayloadType type = downlink::PayloadType::Test_Payload_Type;
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t z = 0;

    uint64_t timestamp = 0;

    String toLineProtocol() const;

    Test_Payload(int16_t _x, int16_t _y, int16_t _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};


#endif //TEST_PAYLOAD_H