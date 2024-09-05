#pragma once

#include "ISerializer.h"

namespace notifications {

class JsonSerializer : public ISerializer {
public:
    std::string serialize(const NoteSerialization &note) const override;
    NoteSerialization deserialize(const std::string &jsonStr) const override;
};

}
