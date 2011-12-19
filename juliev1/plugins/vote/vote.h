//
/// \file plugins/vote/vote.h
/// \brief Vote plugin
//

#ifndef PLUGINS_VOTE_VOTE_H
#define PLUGINS_VOTE_VOTE_H

#include "../../bot/plugin.h"

#include <map>

class Vote : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);

	protected:
		//
		/// \brief Is a vote going on?
		//
		bool is_voting;

		//
		/// \brief The issue we're voting on
		//
		std::string issue;

		//
		/// \brief The possible voting choices : and current results
		//
		std::map <std::string, int> choices;

		//
		/// \brief The people who have voted this round
		//
		std::vector <std::string> people_voted;

		//
		/// \brief Current vote creator
		//
		std::string vote_creator;

		//
		/// \brief Current vote creator's user and host 'user@host'
		//
		std::string vote_creator_host;
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_VOTE_VOTE_H
