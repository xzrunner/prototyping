#pragma once

#include "prototyping/trigger/typedef.h"

#include <cu/cu_macro.h>
#include <cpputil/ClassInfo.h>

#include <map>

namespace pt
{
namespace trigger
{

class Factory
{
public:
	void RegisterEvent(cpputil::ClassInfo<Event>* ci);
	std::unique_ptr<Event> NewEvent(const std::string& class_name);

	void RegisterAction(cpputil::ClassInfo<Action>* ci);
	std::unique_ptr<Action> NewAction(const std::string& class_name);

	auto& GetAllEvents() const { return m_event_map; }

private:
	std::map<std::string, cpputil::ClassInfo<Event>*>  m_event_map;
	std::map<std::string, cpputil::ClassInfo<Action>*> m_action_map;

	CU_SINGLETON_DECLARATION(Factory)

}; // Factory

}
}