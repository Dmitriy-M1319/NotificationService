#pragma once

#include "INotifier.h"

namespace notifications
{

class GNotifier: public INotifier
{
public:
    void notify(const Notification& notification) override;
};

}
