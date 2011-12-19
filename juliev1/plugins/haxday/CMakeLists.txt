#
# plugins/haxday
# HaxDay plugin
#

project (haxday)

	set (haxday_SOURCES ${haxday_SOURCE_DIR}/haxday.cpp)
	set (haxday_INCLUDES ${haxday_SOURCE_DIR}/haxday.h)

	add_library(haxday MODULE ${haxday_SOURCES} ${haxday_INCLUDES})
	set_target_properties (haxday PROPERTIES PREFIX "")

