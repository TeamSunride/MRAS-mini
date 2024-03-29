//
// Created by Tom Danvers on 11/03/2023.
//
#include "timestamp.h"

uint64_t getTimestampMillis() {
    uint64_t periods;
    uint32_t hi1 = SNVS_HPRTCMR, lo1 = SNVS_HPRTCLR;
    while (true) {
        uint32_t hi2 = SNVS_HPRTCMR, lo2 = SNVS_HPRTCLR;
        if (lo1 == lo2 && hi1 == hi2) {
            periods = (uint64_t) hi2 << 32 | lo2;
            break;
        }
        hi1 = hi2;
        lo1 = lo2;
    }
    uint32_t ms = (1000 * (periods % 32768)) / 32768;
    time_t sec = periods / 32768;
    tm t = *gmtime(&sec);

    setTime(t.tm_hour, t.tm_min, t.tm_sec, t.tm_mday, t.tm_mon + 1, t.tm_year + 1900);

    uint64_t unixTime = (uint64_t(now()) * 1000) + ms;
    return unixTime;
}


time_t getTeensy3Time() {
    return Teensy3Clock.get();
}
