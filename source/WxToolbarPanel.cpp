#include "prototyping/WxToolbarPanel.h"
#include "prototyping/CompTrigger.h"
#include "prototyping/WxEditCaseDialog.h"
#include "prototyping/trigger/Trigger.h"
#include "prototyping/trigger/Event.h"
#include "prototyping/trigger/Factory.h"

#include <ee0/WxListSelectDlg.h>
#include <ee0/SubjectMgr.h>
#include <ee0/GameObj.h>

#include <guard/check.h>
#include <node0/SceneNode.h>
#include <node2/CompScript.h>

#include <wx/sizer.h>
#include <wx/button.h>

namespace
{

struct EventItemData : public wxTreeItemData
{
	EventItemData(const std::string& name)
		: name(name) {}

	std::string name;

}; // EventItemData

}

namespace pt
{

WxToolbarPanel::WxToolbarPanel(wxWindow* parent,
	                           const ee0::SubjectMgrPtr& sub_mgr)
	: wxPanel(parent)
	, m_sub_mgr(sub_mgr)
{
	m_sub_mgr->RegisterObserver(ee0::MSG_NODE_SELECTION_INSERT, this);
	m_sub_mgr->RegisterObserver(ee0::MSG_NODE_SELECTION_DELETE, this);
	m_sub_mgr->RegisterObserver(ee0::MSG_NODE_SELECTION_CLEAR, this);

	InitLayout();
}

WxToolbarPanel::~WxToolbarPanel()
{
	m_sub_mgr->UnregisterObserver(ee0::MSG_NODE_SELECTION_INSERT, this);
	m_sub_mgr->UnregisterObserver(ee0::MSG_NODE_SELECTION_DELETE, this);
	m_sub_mgr->UnregisterObserver(ee0::MSG_NODE_SELECTION_CLEAR, this);
}

void WxToolbarPanel::OnNotify(uint32_t msg, const ee0::VariantSet& variants)
{
	switch (msg)
	{
	case ee0::MSG_NODE_SELECTION_INSERT:
	{
		auto var = variants.GetVariant("obj");
		GD_ASSERT(var.m_type == ee0::VT_PVOID, "no var in vars: obj");
		ee0::GameObj* obj = static_cast<ee0::GameObj*>(var.m_val.pv);
		GD_ASSERT(obj, "err scene obj");

		SetNode(*obj);
	}
		break;
	case ee0::MSG_NODE_SELECTION_DELETE:
	{
		auto var = variants.GetVariant("obj");
		GD_ASSERT(var.m_type == ee0::VT_PVOID, "no var in vars: obj");
		ee0::GameObj* obj = static_cast<ee0::GameObj*>(var.m_val.pv);
		GD_ASSERT(obj, "err scene obj");

		if (*obj == m_node) {
			Clear();
		}
	}
		break;
	case ee0::MSG_NODE_SELECTION_CLEAR:
		Clear();
		break;
	}
}

void WxToolbarPanel::InitLayout()
{
	wxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);

	// buttons
	{
		wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

		m_btn_add = new wxButton(this, wxID_ANY, "+", wxDefaultPosition, wxSize(20, 20));
		Connect(m_btn_add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler(WxToolbarPanel::OnAddPress));
		sizer->Add(m_btn_add, 0, wxLEFT | wxRIGHT, 5);

		m_btn_del = new wxButton(this, wxID_ANY, "-", wxDefaultPosition, wxSize(20, 20));
		Connect(m_btn_del->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler(WxToolbarPanel::OnDelPress));
		sizer->Add(m_btn_del, 0, wxLEFT | wxRIGHT, 5);

		top_sizer->Add(sizer);
	}
	// event list
	top_sizer->Add(m_event_tree = new WxEventTreeCtrl(this, [&](const std::string& str) {
		m_script_text->SetValue(str);
	}), 1, wxEXPAND);
	// script text
	top_sizer->Add(m_script_text = new wxTextCtrl(
		this, wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY), 1, wxEXPAND);

	SetSizer(top_sizer);
}

void WxToolbarPanel::Clear()
{
	SetNode(nullptr);
	m_event_tree->DeleteAllItems();
}

void WxToolbarPanel::OnAddPress(wxCommandEvent& event)
{
	if (!m_node) {
		return;
	}

	std::vector<std::pair<std::string, wxTreeItemData*>> event_list;
	for (auto& e : trigger::Factory::Instance()->GetAllEvents()) {
		auto& name = e.first;
		event_list.push_back({ name, new EventItemData(name) });
	}

	ee0::WxListSelectDlg dlg(this, "Create event",
		event_list, m_btn_add->GetScreenPosition());
	if (dlg.ShowModal() != wxID_OK) {
		return;
	}

	auto data = static_cast<EventItemData*>(dlg.GetSelected());
	assert(data);

	if (!m_node->HasUniqueComp<CompTrigger>()) {
		m_node->AddUniqueComp<CompTrigger>();
	}
	auto& ct = m_node->GetUniqueComp<CompTrigger>();
	auto e = trigger::Factory::Instance()->NewEvent(data->name);
	ct.GetImpl().AddEvent(e);
	m_event_tree->InsertEvent(e);
}

void WxToolbarPanel::OnDelPress(wxCommandEvent& event)
{
}

void WxToolbarPanel::SetNode(const n0::SceneNodePtr& node)
{
	m_node = node;
	m_event_tree->SetNode(node);

	if (node && node->HasUniqueComp<CompTrigger>())
	{
		auto& ct = node->GetUniqueComp<CompTrigger>();
		m_event_tree->Build(ct.GetImpl());
		auto& funcs = ct.GetLuaFuncs();
		if (!funcs.empty())
		{
			std::string str;
			for (auto& f : funcs) {
				str += f.second + "\n";
			}
			m_script_text->SetValue(str);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// class WxToolbarPanel::WxEventTreeCtrl
//////////////////////////////////////////////////////////////////////////

WxToolbarPanel::WxEventTreeCtrl::WxEventTreeCtrl(wxWindow* parent,
	                                             std::function<void(const std::string&)> update_cb)
	: wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxSize(300, 400),
		wxTR_HIDE_ROOT | wxTR_DEFAULT_STYLE)
	, m_update_cb(update_cb)
{
	Bind(wxEVT_TREE_ITEM_ACTIVATED, &WxEventTreeCtrl::OnItemActivated, this, GetId());
}

void WxToolbarPanel::WxEventTreeCtrl::Build(const trigger::Trigger& trigger)
{
	DeleteAllItems();

	m_root = AddRoot("root");

	auto& events = trigger.GetEvents();
	for (auto& event : events) {
		InsertEvent(event);
	}
}

void WxToolbarPanel::WxEventTreeCtrl::InsertEvent(const trigger::EventPtr& event)
{
	if (!m_root.IsOk()) {
		m_root = AddRoot("root");
	}

	auto item = InsertItem(m_root, 0, event->GetClassInfo().GetClassName());
	SetItemData(item, new Item(event));
}

void WxToolbarPanel::WxEventTreeCtrl::OnItemActivated(wxTreeEvent& event)
{
	wxTreeItemId item = event.GetItem();
	auto item_data = (Item*)GetItemData(item);
	assert(item_data);

	auto& e = item_data->event;
	WxEditCaseDialog dlg(this, *e, e->GetFirstCase());
	dlg.ShowModal();

	if (dlg.IsDirty()){
		UpdateNodeScript(e);
	}
}

void WxToolbarPanel::WxEventTreeCtrl::UpdateNodeScript(const trigger::EventPtr& event)
{
	assert(m_node->HasUniqueComp<n2::CompScript>());
	auto& cs = m_node->GetUniqueComp<n2::CompScript>();

	std::string str = event->GenLuaFunc();
	cs.GetImpl().AddFunc(event->LuaFuncName(), str);

	auto& ct = m_node->GetUniqueComp<CompTrigger>();
	ct.AddLuaFunc(event->LuaFuncName(), str);

	m_update_cb(str);
}

}