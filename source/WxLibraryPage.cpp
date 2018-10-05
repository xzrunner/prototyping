#include "prototyping/WxLibraryPage.h"

#include <ee0/WxLibraryList.h>
#include <ee0/WxLibraryItem.h>

#include <boost/filesystem.hpp>

namespace pt
{

WxLibraryPage::WxLibraryPage(wxWindow* parent,
	                         const std::string& name,
	                         const std::string& dir,
	                         const rapidjson::Value& items_val)
	: ee0::WxLibraryPage(parent, name, true)
{
	LoadFromJson(dir, items_val);
}

void WxLibraryPage::LoadFromJson(const std::string& dir,
	                             const rapidjson::Value& items_val)
{
	for (auto& item_val : items_val.GetArray())
	{
		auto name = item_val["name"].GetString();
		auto src = item_val["src"].GetString();
		auto path = boost::filesystem::absolute(src, dir);
		m_list->Insert(std::make_shared<ee0::WxLibraryItem>(path.string(), name));
	}
}

}