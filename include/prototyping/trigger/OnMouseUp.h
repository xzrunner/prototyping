#pragma once

#include "prototyping/trigger/Event.h"

namespace pt
{
namespace trigger
{

class OnMouseUp : public Event
{
protected:
	virtual const char* LuaFuncParams() const override {
		return "self, x, y";
	}

	DECLARE_CHILD_CLASS_INFO(Event)
	DECLARE_PT_EVENT

}; // OnMouseUp

}
}