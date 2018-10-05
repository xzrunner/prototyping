#pragma once

#include "prototyping/trigger/Action.h"

namespace pt
{
namespace trigger
{

class Print : public Action
{
public:
	Print();

	virtual void Do() const;

	virtual std::string ToLuaString() const;

	virtual std::string GetDesc() const;

	auto& GetText() const { return m_text; }
	void SetText(const std::string& text) {
		m_text = text;
	}

private:
	std::string m_text;

	DECLARE_CHILD_CLASS_INFO(Action)

}; // Print

}
}