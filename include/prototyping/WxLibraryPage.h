#pragma once

#include <ee0/WxLibraryPage.h>

#include <rapidjson/document.h>

#include <string>

namespace pt
{

class WxLibraryPage : public ee0::WxLibraryPage
{
public:
	WxLibraryPage(wxWindow* parent, const std::string& name,
		const std::string& dir, const rapidjson::Value& items_val);

private:
	void LoadFromJson(const std::string& dir,
		const rapidjson::Value& items_val);

}; // WxLibraryPage

}