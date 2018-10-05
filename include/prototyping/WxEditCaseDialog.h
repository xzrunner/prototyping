#pragma once

#include "prototyping/trigger/Event.h"
#include "prototyping/trigger/typedef.h"

#include <wx/dialog.h>
#include <wx/treectrl.h>

namespace pt
{

class WxEditCaseDialog : public wxDialog
{
public:
	WxEditCaseDialog(wxWindow* parent, trigger::Event& event,
		trigger::Event::Case& ecase);

	bool IsDirty() const { return m_dirty; }

private:
	void InitLayout(trigger::Event& event,
		trigger::Event::Case& ecase);

private:
	class WxCaseTree;
	class WxActionTree : public wxTreeCtrl
	{
	public:
		WxActionTree(wxWindow* parent, WxCaseTree* case_tree,
			trigger::Event::Case& ecase, bool& dirty);

	private:
		void OnActionActivated(wxTreeEvent& event);

	private:
		struct Item : public wxTreeItemData
		{
			Item(const std::string& class_name)
				: class_name(class_name) {}
			std::string class_name;
		}; // Item

	private:
		WxCaseTree* m_case_tree = nullptr;

		trigger::Event::Case& m_case;

		bool& m_dirty;

	}; // WxActionTree

	class WxCaseTree : public wxTreeCtrl
	{
	public:
		WxCaseTree(wxWindow* parent, wxPanel* detail_panel,
			trigger::Event::Case& ecase, bool& dirty);

		void InsertAction(const trigger::ActionPtr& action);

	private:
		void OnActionSelected(wxTreeEvent& event);

		void InsertActionImpl(const trigger::ActionPtr& action);

	private:
		struct Item : public wxTreeItemData
		{
			Item(const trigger::ActionPtr& action)
				: action(action) {}
			trigger::ActionPtr action;
		}; // Item

	private:
		wxPanel* m_detail_panel = nullptr;

		trigger::Event::Case& m_case;

		bool& m_dirty;

		wxTreeItemId m_root;

	}; // WxCaseTree

	class WxActoonDetail : public wxPanel
	{
	public:
		WxActoonDetail(wxWindow* parent)
			: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(300, 600))
		{
		}

	}; // WxActoonDetail

private:
	WxActoonDetail* m_detail = nullptr;

	bool m_dirty = false;

}; // WxEditCaseDialog

}