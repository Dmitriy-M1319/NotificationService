#pragma once

#include <boost/date_time/posix_time/ptime.hpp>
#include <string>

using namespace boost::posix_time;

namespace notifications
{

class Notification
{
public:
    Notification();
    Notification(const std::string &text, const ptime &date, unsigned int id = 0);
    const std::string& text() const noexcept;
    const ptime& notificationDate() const noexcept;
    unsigned int id() const noexcept;
    
    void setId(unsigned int id);
    void setText(std::string &&text);
    void setText(const std::string &text);
    void setNotificationDate(const ptime &date);
    void setNotificationDate(ptime &&date);
private:
    unsigned int m_id;
    std::string m_text;
    ptime m_not_date;
};

}; // notification
