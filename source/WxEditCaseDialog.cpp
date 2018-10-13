#include "prototyping/WxEditCaseDialog.h"
#include "prototyping/trigger/Event.h"
#include "prototyping/trigger/Print.h"
#include "prototyping/trigger/Factory.h"
#include "prototyping/view/WxPrint.h"

#include <wx/sizer.h>
#include <wx/treectrl.h>

namespace pt
{

WxEditCaseDialog::WxEditCaseDialog(wxWindow* parent, trigger::Event& event,
	                               trigger::Event::Case& ecase)
	: wxDialog(parent, wxID_ANY, "Case Editor (" + event.GetClassInfo().GetClassName() + ")", wxDefaultPosition, wxSize(800, 600))
{
	InitLayout(event, ecase);
}

void WxEditCaseDialog::InitLayout(trigger::Event& event,
	                              trigger::Event::Case& ecase)
{
	wxSizer* top_sizer = new wxBoxSizer(wxHORIZONTAL);

	m_detail = new WxActoonDetail(this);
	auto* case_tree = new WxCaseTree(this, m_detail, ecase, m_dirty);
	top_sizer->Add(new WxActionTree(this, case_tree, ecase, m_dirty));

	top_sizer->Add(case_tree);

	top_sizer->Add(m_detail);

	SetSizer(top_sizer);
}

//////////////////////////////////////////////////////////////////////////
// class WxEditCaseDialog::WxActionTree
//////////////////////////////////////////////////////////////////////////

WxEditCaseDialog::WxActionTree::WxActionTree(wxWindow* parent, WxCaseTree* case_tree,
	                                         trigger::Event::Case& ecase, bool& dirty)
	: wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 600),
		wxTR_HIDE_ROOT | wxTR_DEFAULT_STYLE)
	, m_case_tree(case_tree)
	, m_case(ecase)
	, m_dirty(dirty)
{
	Bind(wxEVT_TREE_ITEM_ACTIVATED, &WxActionTree::OnActionActivated, this, GetId());

	auto root = AddRoot("");

	auto item = AppendItem(root, trigger::Print::GetClassName());
	SetItemData(item, new Item(trigger::Print::GetClassName()));
}

void WxEditCaseDialog::WxActionTree::OnActionActivated(wxTreeEvent& event)
{
	auto name = static_cast<Item*>(GetItemData(event.GetItem()))->class_name;
	std::shared_ptr<trigger::Action> action =
		trigger::Factory::Instance()->NewAction(name);
	if (action) {
		m_dirty = true;
		m_case.actions.push_back(action);
		m_case_tree->InsertAction(action);
	}
}

//////////////////////////////////////////////////////////////////////////
// class WxEditCaseDialog::WxCaseTree
//////////////////////////////////////////////////////////////////////////

WxEditCaseDialog::WxCaseTree::WxCaseTree(wxWindow* parent, wxPanel* detail_panel,
	                                     trigger::Event::Case& ecase, bool& dirty)
	: wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxSize(300, 600))
	, m_detail_panel(detail_panel)
	, m_case(ecase)
	, m_dirty(dirty)
{
	Bind(wxEVT_TREE_SEL_CHANGED, &WxEditCaseDialog::WxCaseTree::OnActionSelected, this, GetId());

	m_root = AddRoot(m_case.name);
	for (auto& a : m_case.actions) {
		InsertActionImpl(a);
	}

	ExpandAll();
}

void WxEditCaseDialog::WxCaseTree::InsertAction(const trigger::ActionPtr& action)
{
	InsertActionImpl(action);

	ExpandAll();
}

void WxEditCaseDialog::WxCaseTree::OnActionSelected(wxTreeEvent& event)
{
	auto item = event.GetItem();
	if (item == m_root) {
		return;
	}

	wxPanel* detail_panel = nullptr;

	auto item_data = static_cast<Item*>(GetItemData(item));
	assert(item_data);
	auto name = item_data->action->GetClassInfo().GetClassName();
	if (name == trigger::Print::GetClassName()) {
		auto action = std::static_pointer_cast<trigger::Print>(item_data->action);
		detail_panel = new view::WxPrint(m_detail_panel, action, [=]() {
			m_dirty = true;
			SetItemText(item, action->GetDesc());
		});
	}

	if (detail_panel)
	{
		auto sizer = m_detail_panel->GetSizer();
		if (sizer) {
			sizer->Clear(true);
		} else {
			sizer = new wxBoxSizer(wxVERTICAL);
		}
		sizer->Add(detail_panel);
		m_detail_panel->SetSizer(sizer);
	}
}

void WxEditCaseDialog::WxCaseTree::InsertActionImpl(const trigger::ActionPtr& action)
{
	auto item = AppendItem(m_root, action->GetDesc());
	SetItemData(item, new Item(action));
}

}