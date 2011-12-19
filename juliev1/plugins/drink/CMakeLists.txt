#
# plugins/drink
# Drink plugin
#

project (drink)

	set (drink_SOURCES ${drink_SOURCE_DIR}/drink.cpp)
	set (drink_INCLUDES ${drink_SOURCE_DIR}/drink.h)

	add_library(drink MODULE ${drink_SOURCES} ${drink_INCLUDES})
	set_target_properties (drink PROPERTIES PREFIX "")

