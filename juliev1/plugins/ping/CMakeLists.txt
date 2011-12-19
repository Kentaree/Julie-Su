#
# plugins/ping
# Ping plugin
#

project (ping)

	set (ping_SOURCES ${ping_SOURCE_DIR}/ping.cpp)
	set (ping_INCLUDES ${ping_SOURCE_DIR}/ping.h)

	add_library(ping MODULE ${ping_SOURCES} ${ping_INCLUDES})
	set_target_properties (ping PROPERTIES PREFIX "")

