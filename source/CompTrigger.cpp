#include "prototyping/CompTrigger.h"

namespace pt
{

const char* const CompTrigger::TYPE_NAME = "pt_trigger";

std::unique_ptr<n0::NodeComp> CompTrigger::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompTrigger>();
	return comp;
}

void CompTrigger::AddLuaFunc(const std::string& name, const std::string& func)
{
	for (auto& itr : m_lua_funcs) {
		if (itr.first == name) {
			itr.second = func;
			return;
		}
	}
	m_lua_funcs.push_back({ name, func });
}

}