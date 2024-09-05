#pragma once

#include "Note.h"

#include <boost/date_time/posix_time/time_parsers.hpp>
#include <string>

namespace notifications {


struct NoteSerialization {
    enum class OperationType : int {
        INSERT = 0,
        UPDATE = 1,
        DELETE = 2
    };

    unsigned int id;
    OperationType operation;
    std::string text;
    std::string dateIsoString;

    Notification toNote() const {
        return Notification(text, from_iso_string(dateIsoString), id);
    }
};

class ISerializer {
public:
    virtual std::string serialize(const NoteSerialization &) const = 0;
    virtual NoteSerialization deserialize(const std::string &) const = 0;
    virtual ~ISerializer() {};
};

};
