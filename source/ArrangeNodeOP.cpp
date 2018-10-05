#include "prototyping/ArrangeNodeOP.h"
#include "prototyping/trigger/OnMouseDown.h"
#include "prototyping/trigger/OnMouseUp.h"
#include "prototyping/trigger/OnMouseMove.h"

#include <ee0/CameraHelper.h>
#include <ee2/ArrangeNodeCfg.h>
#include <ee2/ArrangeNodeImpl.h>
#include <ee2/NodeSelectOP.h>

#include <node0/SceneNode.h>
#include <node2/CompScript.h>

namespace pt
{

ArrangeNodeOP::ArrangeNodeOP(const std::shared_ptr<pt0::Camera>& camera,
	                         ee0::WxStagePage& stage)
	: ee2::ArrangeNodeOP(camera, stage)
{
	auto& cfg = m_impl->GetCfgRef();
	cfg.is_auto_align_open = false;
	cfg.is_deform_open = false;
	cfg.is_offset_open = false;
	cfg.is_rotate_open = false;

	auto select_op = std::make_shared<ee2::NodeSelectOP>(camera, stage);
	SetPrevEditOP(select_op);
}

bool ArrangeNodeOP::OnKeyDown(int key_code)
{
	if (ee2::ArrangeNodeOP::OnKeyDown(key_code)) {
		return true;
	}

	return false;
}

bool ArrangeNodeOP::OnKeyUp(int key_code)
{
	if (ee2::ArrangeNodeOP::OnKeyUp(key_code)) {
		return true;
	}

	return false;
}

bool ArrangeNodeOP::OnMouseLeftDown(int x, int y)
{
	if (ee2::ArrangeNodeOP::OnMouseLeftDown(x, y)) {
		return true;
	}

	CallMouseFunc(trigger::OnMouseDown::LUA_FUNC_NAME, x, y);

	return false;
}

bool ArrangeNodeOP::OnMouseLeftUp(int x, int y)
{
	if (ee2::ArrangeNodeOP::OnMouseLeftUp(x, y)) {
		return true;
	}

	CallMouseFunc(trigger::OnMouseUp::LUA_FUNC_NAME, x, y);

	return false;
}

bool ArrangeNodeOP::OnMouseRightDown(int x, int y)
{
	if (ee2::ArrangeNodeOP::OnMouseRightDown(x, y)) {
		return true;
	}

	CallMouseFunc(trigger::OnMouseDown::LUA_FUNC_NAME, x, y);

	return false;
}

bool ArrangeNodeOP::OnMouseRightUp(int x, int y)
{
	if (ee2::ArrangeNodeOP::OnMouseRightUp(x, y)) {
		return true;
	}

	CallMouseFunc(trigger::OnMouseUp::LUA_FUNC_NAME, x, y);

	return false;
}

bool ArrangeNodeOP::OnMouseMove(int x, int y)
{
	if (ee2::ArrangeNodeOP::OnMouseMove(x, y)) {
		return true;
	}

	CallMouseFunc(trigger::OnMouseMove::LUA_FUNC_NAME, x, y);

	return false;
}

void ArrangeNodeOP::CallMouseFunc(const char* name, int x, int y)
{
	auto pos = ee0::CameraHelper::TransPosScreenToProject(*m_camera, x, y);
	m_impl->TraversePosIn(pos, [&](const ee0::GameObj& obj)->bool {
		if (obj->HasUniqueComp<n2::CompScript>()) {
			auto& cscript = obj->GetUniqueComp<n2::CompScript>();
			cscript.GetImpl().CallMouseFunc(name, pos.x, pos.y);
		}
		return true;
	});
}

}