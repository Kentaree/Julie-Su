#
# plugins/raw
# Raw plugin
#

project (raw)

	set (raw_SOURCES ${raw_SOURCE_DIR}/raw.cpp)
	set (raw_INCLUDES ${raw_SOURCE_DIR}/raw.h)

	add_library(raw MODULE ${raw_SOURCES} ${raw_INCLUDES})
	set_target_properties (raw PROPERTIES PREFIX "")

