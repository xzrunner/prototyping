#pragma once

#include <ee2/ArrangeNodeOP.h>

namespace pt
{

class ArrangeNodeOP : public ee2::ArrangeNodeOP
{
public:
	ArrangeNodeOP(const std::shared_ptr<pt0::Camera>& camera,
		ee0::WxStagePage& stage);

	virtual bool OnKeyDown(int key_code) override;
	virtual bool OnKeyUp(int key_code) override;

	virtual bool OnMouseLeftDown(int x, int y) override;
	virtual bool OnMouseLeftUp(int x, int y) override;
	virtual bool OnMouseRightDown(int x, int y) override;
	virtual bool OnMouseRightUp(int x, int y) override;
	virtual bool OnMouseMove(int x, int y) override;

private:
	void CallMouseFunc(const char* name, int x, int y);

}; // ArrangeNodeOP

}