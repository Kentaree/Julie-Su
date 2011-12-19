#
# plugins/level
# Level plugin
#

project (level)

	set (level_SOURCES ${level_SOURCE_DIR}/level.cpp)
	set (level_INCLUDES ${level_SOURCE_DIR}/level.h)

	add_library(level MODULE ${level_SOURCES} ${level_INCLUDES})
	set_target_properties (level PROPERTIES PREFIX "")

