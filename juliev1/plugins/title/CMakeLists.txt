#
# plugins/title
# Title plugin
#

project (title)

	set (title_SOURCES ${title_SOURCE_DIR}/title.cpp)
	set (title_INCLUDES ${title_SOURCE_DIR}/title.h)

	add_library(title MODULE ${title_SOURCES} ${title_INCLUDES})
	set_target_properties (title PROPERTIES PREFIX "")

