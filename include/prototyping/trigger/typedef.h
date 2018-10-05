#pragma once

#include <memory>

namespace pt
{
namespace trigger
{

class Event;
using EventPtr = std::shared_ptr<Event>;

class Condition;
using ConditionPtr = std::shared_ptr<Condition>;

class Action;
using ActionPtr = std::shared_ptr<Action>;

}
}