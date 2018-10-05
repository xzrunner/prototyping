#pragma once

#include <cpputil/ClassInfo.h>

#include <string>

namespace pt
{
namespace trigger
{

class Action
{
public:
	virtual ~Action() {}

	virtual void Do() const = 0;

	virtual std::string ToLuaString() const = 0;

	virtual std::string GetDesc() const = 0;

	DECLARE_BASE_CLASS_INFO(Action)

}; // Action

}
}