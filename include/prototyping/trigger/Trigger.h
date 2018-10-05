#pragma once

#include "prototyping/trigger/Event.h"

#include <vector>
#include <memory>

namespace pt
{
namespace trigger
{

class Trigger
{
public:

	auto& GetEvents() const { return m_events; }
	void AddEvent(const EventPtr& event) {
		m_events.push_back(event);
	}

private:
	std::vector<EventPtr> m_events;

}; // trigger

}
}