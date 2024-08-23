#include "GNotifier.h"

#include <regex>
#include <format>
#include <boost/process.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>

using namespace notifications;

void GNotifier::notify(const Notification& notification)
{
    std::string timeStr{std::move(boost::posix_time::to_simple_string(notification.notificationDate()))};
    std::regex simpleTimeRegex("\\d+:\\d+:\\d+");

    auto time = std::sregex_iterator(timeStr.begin(), timeStr.end(), simpleTimeRegex)->str();
    boost::process::child notifyProcess(std::format("notify-send -a \"Напоминание: {}\" \"{}\"",
                time, notification.text()));
    notifyProcess.wait();
}

