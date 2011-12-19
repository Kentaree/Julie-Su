#
# plugins/time
# Time plugin
#

project (time)

	set (time_SOURCES ${time_SOURCE_DIR}/time.cpp)
	set (time_INCLUDES ${time_SOURCE_DIR}/time.h)

	add_library(time MODULE ${time_SOURCES} ${time_INCLUDES})
	set_target_properties (time PROPERTIES PREFIX "")

