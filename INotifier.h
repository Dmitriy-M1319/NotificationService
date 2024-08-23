#pragma once

#include "Note.h"

namespace notifications
{

class INotifier {
public:
    virtual void notify(const Notification&) = 0;
};
}
