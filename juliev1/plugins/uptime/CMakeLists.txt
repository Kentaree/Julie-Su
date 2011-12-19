#
# plugins/uptime
# Uptime plugin
#

project (uptime)

	set (uptime_SOURCES ${uptime_SOURCE_DIR}/uptime.cpp)
	set (uptime_INCLUDES ${uptime_SOURCE_DIR}/uptime.h)

	add_library(uptime MODULE ${uptime_SOURCES} ${uptime_INCLUDES})
	set_target_properties (uptime PROPERTIES PREFIX "")

