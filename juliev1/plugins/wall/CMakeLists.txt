#
# plugins/wall
# Wall plugin
#

project (wall)

	set (wall_SOURCES ${wall_SOURCE_DIR}/wall.cpp)
	set (wall_INCLUDES ${wall_SOURCE_DIR}/wall.h)

	add_library(wall MODULE ${wall_SOURCES} ${wall_INCLUDES})
	set_target_properties (wall PROPERTIES PREFIX "")

