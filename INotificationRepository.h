#pragma once

#include "Note.h"

#include <vector>

namespace notifications
{

class INotificationRepository
{
public:
    virtual const std::vector<Notification>& activeNotifications() = 0;
    virtual Notification& getNotificationById(unsigned int id)  = 0;
    virtual void saveNotification(const Notification &note) = 0;
    virtual void updateNotification(unsigned int id, const Notification &note) = 0;
    virtual void deleteNotification(unsigned int id) = 0;
    virtual ~INotificationRepository() = default;
    
protected:
    std::vector<Notification> m_notifications;
    Notification m_currNotification;
};

}
