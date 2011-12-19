//
/// \file plugins/todo/todo.h
/// \brief Todo plugin
//

#ifndef PLUGINS_TODO_TODO_H
#define PLUGINS_TODO_TODO_H

#include "../../bot/plugin.h"

#include <vector>
#include <string>
#include <utility>

class Todo : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);

		void outputUserList (std::string nick, std::string target, bool pm);

		void addToUserList (std::string nick, std::string message);
		void removeFromUserList (std::string nick, int num);

		// Write the list to a file
		void writeTodoList (std::string filename);

		// Read the list from a file
		void readTodoList (std::string filename);

		std::string swapUserListElements (std::string nick, int item1, int item2);

	protected:
		// Our lists : format is vector<username, username's list>
		std::vector<std::pair<std::string, std::vector<std::string> > > todolists;

};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_ECHO_ECHO_H
