//
/// \file plugins/eightball/eightball.cpp
/// \brief Eightball plugin
//

#include "eightball.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void EightBall::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "EightBall";
	this->description = "Ask the wonderous 8ball a question.";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void EightBall::free (void)
{}

void EightBall::run (JulieSu::Irc::Message message)
{
	std::vector <std::string> good_answers;
	good_answers.push_back ("Yes");
	good_answers.push_back ("Signs point to Yes");
	good_answers.push_back ("It is certain");
	good_answers.push_back ("Most likely");
	good_answers.push_back ("If you give thothonegan money");

	std::vector<std::string> bad_answers;
	bad_answers.push_back ("No");
	bad_answers.push_back ("Outlook not so good");
	bad_answers.push_back ("Better not tell you");
	bad_answers.push_back ("My reply is no");
	bad_answers.push_back ("My sources say no");
	bad_answers.push_back ("I slept with your wife");

	std::string result;
	if (rand() % 2 == 1)
	{
		random_shuffle (good_answers.begin(), good_answers.end());
		result = good_answers[0];
	}
	else
	{
		random_shuffle (bad_answers.begin(), bad_answers.end());
		result = bad_answers[0];
	}

	std::string msg = "[8ball] " + result;

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msg);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new EightBall;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

