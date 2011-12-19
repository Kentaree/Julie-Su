#
# plugins/youtube
# Youtube plugin
#

project (youtube)

	set (youtube_SOURCES ${youtube_SOURCE_DIR}/youtube.cpp)
	set (youtube_INCLUDES ${youtube_SOURCE_DIR}/youtube.h)

	add_library(youtube MODULE ${youtube_SOURCES} ${youtube_INCLUDES})
	set_target_properties (youtube PROPERTIES PREFIX "")

