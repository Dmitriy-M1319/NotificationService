#include "Note.h"

using namespace notifications;

Notification::Notification(): m_id{0}, m_text{""}, m_not_date{} {}

Notification::Notification(const std::string &text, const ptime &date, unsigned int id):
    m_text{text}, m_not_date{date}, m_id{id} {}

unsigned int Notification::id() const noexcept {
    return m_id;
}

const std::string& Notification::text() const noexcept {
    return m_text;
}

const ptime& Notification::notificationDate() const noexcept {
    return m_not_date;
}

void Notification::setId(unsigned int id) {
    m_id = id;
}

void Notification::setText(const std::string &text) {
    m_text = text;
}

void Notification::setNotificationDate(const ptime &date) {
    m_not_date = date;
}

void Notification::setText(std::string &&text) {
    m_text = std::move(text);
}

void Notification::setNotificationDate(ptime &&date) {
    m_not_date = std::move(date);
}
