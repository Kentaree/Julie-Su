#
# plugins/map
# Map plugin
#

project (map)

	set (map_SOURCES ${map_SOURCE_DIR}/map.cpp)
	set (map_INCLUDES ${map_SOURCE_DIR}/map.h)

	add_library(map MODULE ${map_SOURCES} ${map_INCLUDES})
	set_target_properties (map PROPERTIES PREFIX "")

