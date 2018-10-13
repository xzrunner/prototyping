#include "prototyping/trigger/Factory.h"
#include "prototyping/trigger/Action.h"
#include "prototyping/trigger/Event.h"

namespace pt
{
namespace trigger
{

CU_SINGLETON_DEFINITION(Factory);

Factory::Factory()
{
}

void Factory::RegisterEvent(cpputil::ClassInfo<Event>* ci)
{
	auto& name = ci->GetClassName();
	if (m_event_map.find(name) == m_event_map.end()) {
		m_event_map.insert({ name, ci });
	}
}

std::unique_ptr<Event> Factory::NewEvent(const std::string& class_name)
{
	auto itr = m_event_map.find(class_name);
	if (itr == m_event_map.end()) {
		return nullptr;
	}

	return itr->second->GetCtor()();
}

void Factory::RegisterAction(cpputil::ClassInfo<Action>* ci)
{
	auto& name = ci->GetClassName();
	if (m_action_map.find(name) == m_action_map.end()) {
		m_action_map.insert({ name, ci });
	}
}

std::unique_ptr<Action> Factory::NewAction(const std::string& class_name)
{
	auto itr = m_action_map.find(class_name);
	if (itr == m_action_map.end()) {
		return nullptr;
	}

	return itr->second->GetCtor()();
}

}
}