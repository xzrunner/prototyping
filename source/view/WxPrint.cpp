#include "prototyping/view/WxPrint.h"
#include "prototyping/trigger/Print.h"

namespace pt
{
namespace view
{

WxPrint::WxPrint(wxWindow* parent, const std::shared_ptr<trigger::Print>& action,
	             std::function<void()> changed_cb)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(300, 600))
	, m_action(action)
	, m_changed_cb(changed_cb)
{
	InitLayout();
}

void WxPrint::InitLayout()
{
	m_text = new wxTextCtrl(this, wxID_ANY, m_action->GetText(),
		wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Connect(m_text->GetId(), wxEVT_COMMAND_TEXT_ENTER,
		wxCommandEventHandler(WxPrint::EnterTextValue));
}

void WxPrint::EnterTextValue(wxCommandEvent& event)
{
	m_action->SetText(m_text->GetValue().ToStdString());
	m_changed_cb();
}

}
}