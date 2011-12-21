//
/// \file plugins/ragepics/ragepics.cpp
/// \brief RagePics plugin
//

#include "ragepics.h"
#include <sstream>

void RagePics::init (JulieSu::Bot* bot)
{
	this->author = "kentaree";
	this->name = "RagePics";
	this->description = "ragepics ragepics ragepics";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;

	this->responses["ok"] = "http://goo.gl/WNEDd";
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
	
	std::string target = (message.privmsg_target == bot->getName()) ? message.nick : message.privmsg_target;
	std::map<std::string,std::string>::iterator it = this->responses.find(verb);
	if(it == this->responses.end()) {
	  sendOptions(target);
	  return; 
	}

	std::string response = std::string("[ragepic] ") + (*it).second;
	bot->getConnection()->sendPrivMsg (target, response);
}

void RagePics::sendOptions(std::string target)
{
  std::stringstream options;
  options << "Possible options:";
  for(std::map<std::string,std::string>::iterator it = this->responses.begin(); it != this->responses.end(); it++) {
    options << " " << (*it).first << ",";
  }

  std::string complete = options.str();
  complete = complete.erase(complete.length()-1,1);
  bot->getConnection()->sendPrivMsg (target, complete);
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

