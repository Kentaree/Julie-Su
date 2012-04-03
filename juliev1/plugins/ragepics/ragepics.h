//
/// \file plugins/ragepics/ragepics.h
/// \brief Ragepics plugin
//

#pragma once

#include "../../bot/plugin.h"

class Ragepics : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);
