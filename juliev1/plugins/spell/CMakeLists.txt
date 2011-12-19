#
# plugins/spell
# Spell plugin
#

project (spell)

	set (spell_SOURCES ${spell_SOURCE_DIR}/spell.cpp)
	set (spell_INCLUDES ${spell_SOURCE_DIR}/spell.h)

	add_library(spell MODULE ${spell_SOURCES} ${spell_INCLUDES})
	set_target_properties (spell PROPERTIES PREFIX "")

