#
# plugins/pizza
# Pizza plugin
#

project (pizza)

	set (pizza_SOURCES ${pizza_SOURCE_DIR}/pizza.cpp)
	set (pizza_INCLUDES ${pizza_SOURCE_DIR}/pizza.h)

	add_library(pizza MODULE ${pizza_SOURCES} ${pizza_INCLUDES})
	set_target_properties (pizza PROPERTIES PREFIX "")

