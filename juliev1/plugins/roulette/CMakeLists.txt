#
# plugins/roulette
# Roulette plugin
#

project (roulette)

	set (roulette_SOURCES ${roulette_SOURCE_DIR}/roulette.cpp)
	set (roulette_INCLUDES ${roulette_SOURCE_DIR}/roulette.h)

	add_library(roulette MODULE ${roulette_SOURCES} ${roulette_INCLUDES})
	set_target_properties (roulette PROPERTIES PREFIX "")

