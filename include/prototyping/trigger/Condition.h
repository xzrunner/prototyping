#pragma once

namespace pt
{
namespace trigger
{

class Condition
{
public:
	virtual ~Condition() {}

	virtual bool Meet() const = 0;

}; // Condition

}
}