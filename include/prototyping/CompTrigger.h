#pragma once

#include "prototyping/trigger/Trigger.h"

#include <node0/NodeComp.h>

namespace pt
{

class CompTrigger : public n0::NodeComp
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::CompID TypeID() const override {
		return n0::GetCompTypeID<CompTrigger>();
	}
	virtual std::unique_ptr<n0::NodeComp> Clone(const n0::SceneNode& node) const override;

	auto& GetImpl() const { return m_impl; }
	auto& GetImpl() { return m_impl; }

	void AddLuaFunc(const std::string& name, const std::string& func);
	auto& GetLuaFuncs() const { return m_lua_funcs; }

	static const char* const TYPE_NAME;

private:
	trigger::Trigger m_impl;

	std::vector<std::pair<std::string, std::string>> m_lua_funcs;

}; // CompTrigger

}