#pragma once

#include "prototyping/trigger/typedef.h"

#include <ee0/Observer.h>
#include <ee0/typedef.h>

#include <node0/typedef.h>

#include <wx/panel.h>
#include <wx/treectrl.h>

namespace pt
{

namespace trigger { class Trigger; }

class WxToolbarPanel : public wxPanel, public ee0::Observer
{
public:
	WxToolbarPanel(wxWindow* parent, const ee0::SubjectMgrPtr& sub_mgr);
	virtual ~WxToolbarPanel();

	virtual void OnNotify(uint32_t msg, const ee0::VariantSet& variants) override;

private:
	void InitLayout();

	void Clear();

	void OnAddPress(wxCommandEvent& event);
	void OnDelPress(wxCommandEvent& event);

private:
	void SetNode(const n0::SceneNodePtr& node);

private:
	class WxEventTreeCtrl : public wxTreeCtrl
	{
	public:
		WxEventTreeCtrl(wxWindow* parent,
			std::function<void(const std::string&)> update_cb);

		void Build(const trigger::Trigger& trigger);

		void InsertEvent(const trigger::EventPtr& event);
//		void InsertCase();

		void SetNode(const n0::SceneNodePtr& node) {
			m_node = node;
		}

	private:
		void OnItemActivated(wxTreeEvent& event);

		void UpdateNodeScript(const trigger::EventPtr& event);

	private:
		struct Item : public wxTreeItemData
		{
			Item(const trigger::EventPtr& event)
				: event(event) {}

			trigger::EventPtr event;

		}; // Item

	private:
		std::function<void(const std::string&)> m_update_cb;

		n0::SceneNodePtr m_node = nullptr;

		wxTreeItemId m_root;

	}; // WxEventTreeCtrl

private:
	ee0::SubjectMgrPtr m_sub_mgr;

	wxButton *m_btn_add, *m_btn_del;

	WxEventTreeCtrl* m_event_tree;

	wxTextCtrl* m_script_text;

	n0::SceneNodePtr m_node = nullptr;

}; // WxToolbarPanel

}