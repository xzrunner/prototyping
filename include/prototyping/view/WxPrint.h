#pragma once

#include <wx/panel.h>
#include <wx/textctrl.h>

#include <memory>

namespace pt
{
namespace trigger { class Print; }
namespace view
{

class WxPrint : public wxPanel
{
public:
	WxPrint(wxWindow* parent, const std::shared_ptr<trigger::Print>& action,
		std::function<void()> changed_cb);

private:
	void InitLayout();

	void EnterTextValue(wxCommandEvent& event);

private:
	std::shared_ptr<trigger::Print> m_action;

	std::function<void()> m_changed_cb;

	wxTextCtrl* m_text;

}; // WxPrint

}
}