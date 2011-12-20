//
/// \file plugins/ragepics/ragepics.cpp
/// \brief RagePics plugin
//

#include "ragepics.h"

void RagePics::init (JulieSu::Bot* bot)
{
	this->author = "kentaree";
	this->name = "RagePics";
	this->description = "ragepics ragepics ragepics";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;

	this->responses["sadok"] = "http://goo.gl/WNEDd";
	this->responses["allthe"] = "http://goo.gl/6xCAg";
        this->responses["women"] = "http://goo.gl/uMsmA";
}

void RagePics::free (void)
{}

void RagePics::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);
	std::string verb = arguments.substr(0,arguments.find(" "));
	std::map<std::string,std::string>::iterator it = this->responses.find(verb);
	if(it == this->responses.end()) {
	  return; 
	}

	std::string response = std::string("[ragepic] ") + (*it).second;
	  if (message.privmsg_target == bot->getName()) {
		bot->getConnection()->sendPrivMsg (message.nick, arguments);
	  } else {
		bot->getConnection()->sendPrivMsg (message.privmsg_target, arguments);
	  }
}

JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new RagePics;
	temp->init (bot);
	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();
	delete plugin;
}

