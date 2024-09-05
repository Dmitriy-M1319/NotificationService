#include "Serializer.h"

#include <nlohmann/json.hpp>

using namespace notifications;

std::string JsonSerializer::serialize(const NoteSerialization &note) const {
    return nlohmann::json{
        {"id", note.id},
        {"operation", note.operation},
        {"text", note.text},
        {"dateIsoString", note.dateIsoString}
    }.dump();
}

NoteSerialization JsonSerializer::deserialize(const std::string &jsonStr) const {
    nlohmann::json doc = nlohmann::json::parse(jsonStr);
    return NoteSerialization{
        doc["id"].get<unsigned int>(),
        doc["operation"].get<NoteSerialization::OperationType>(),
        doc["text"].get<std::string>(),
        doc["dateIsoString"].get<std::string>()
    };
}
