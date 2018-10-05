#include "prototyping/trigger/Print.h"

#include <cpputil/StringHelper.h>

#include <iostream>

namespace pt
{
namespace trigger
{

IMPLEMENT_CHILD_CLASS_INFO(Action, Print, Print)

Print::Print()
	: m_text("text")
{
}

void Print::Do() const
{
	std::cout << m_text << "\n";
}

std::string Print::ToLuaString() const
{
	return cpputil::StringHelper::Format("print(\"%s\")", m_text.c_str());
}

std::string Print::GetDesc() const
{
	return "print " + m_text;
}

}
}