//
/// \file bot/source/plugin.cpp
/// \brief A plugin class
//

#include "plugin.h"

namespace JulieSu
{
	Plugin::Plugin (void)
	: name ("<unspec>"), description("<unspec>"), author("<unspec>")
	{
	}

	Plugin::~Plugin (void)
	{
	}

	void Plugin::loop (void)
	{}

	JulieSu::PluginType Plugin::getType (void)
	{
		return type;
	}

	std::string Plugin::getAuthor (void)
	{
		return author;
	}

	std::string Plugin::getName (void)
	{
		return name;
	}

	std::string Plugin::getDescription (void)
	{
		return description;
	}
}
