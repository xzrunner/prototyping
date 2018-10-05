#include "prototyping/trigger/Event.h"
#include "prototyping/trigger/Condition.h"
#include "prototyping/trigger/Action.h"
#include "prototyping/trigger/Factory.h"

#include <cpputil/StringHelper.h>

namespace pt
{
namespace trigger
{

IMPLEMENT_BASE_CLASS_INFO(Event, Factory, RegisterEvent)

std::string Event::GenLuaFunc() const
{
	std::string body;
	for (auto& c : m_cases)
	{
		body += cpputil::StringHelper::Format(
			"-- %s\n", c.name.c_str());
		// todo condition
		for (auto& action : c.actions) {
			body += action->ToLuaString() + "\n";
		}
	}

	return cpputil::StringHelper::Format(R"(
function %s(%s)
	%s
end
)" + 1, LuaFuncName(), LuaFuncParams(), body.c_str());
}

void Event::Do()
{
	for (auto& c : m_cases) {
		if (!c.condition || c.condition->Meet()) {
			for (auto& a : c.actions) {
				a->Do();
			}
		}
	}
}

Event::Case& Event::GetFirstCase()
{
	if (m_cases.empty()) {
		m_cases.push_back(Case());
	}
	return m_cases[0];
}

}
}