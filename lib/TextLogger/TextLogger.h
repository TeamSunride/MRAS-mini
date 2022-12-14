//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_TEXTLOGGER_H
#define MRAS_TEXTLOGGER_H


#include "Subsystem.h"

class TextLogger : public Subsystem {
public:
    using Subsystem::Subsystem;
    virtual void _log(const char *fmt, ...) = 0;
};

#endif //MRAS_TEXTLOGGER_H
