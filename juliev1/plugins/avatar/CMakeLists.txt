#
# plugins/avatar
# Avatar plugin
#

project (avatar)

	set (avatar_SOURCES ${avatar_SOURCE_DIR}/avatar.cpp)
	set (avatar_INCLUDES ${avatar_SOURCE_DIR}/avatar.h)

	add_library(avatar MODULE ${avatar_SOURCES} ${avatar_INCLUDES})
	set_target_properties (avatar PROPERTIES PREFIX "")

