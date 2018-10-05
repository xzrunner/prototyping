#pragma once

#include "prototyping/trigger/typedef.h"

#include <cpputil/ClassInfo.h>

#include <vector>
#include <memory>

namespace pt
{
namespace trigger
{

class Event
{
public:
	virtual ~Event() {}

	virtual const char* LuaFuncName() const = 0;

	std::string GenLuaFunc() const;

	void Do();

protected:
	virtual const char* LuaFuncParams() const = 0;

public:
	struct Case
	{
		std::string name = "case";

		ConditionPtr condition = nullptr;
		std::vector<ActionPtr> actions;
	};

	Case& GetFirstCase();

private:
	std::vector<Case> m_cases;

	DECLARE_BASE_CLASS_INFO(Event)

}; // Event

}
}

#define DECLARE_PT_EVENT                                 \
public:                                                  \
	virtual const char* LuaFuncName() const override {   \
		return LUA_FUNC_NAME;                            \
	}                                                    \
	static const char* LUA_FUNC_NAME;

#define IMPLEMENT_PT_EVENT(type, name)                   \
	const char* type::LUA_FUNC_NAME = #name;
