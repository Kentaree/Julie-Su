#
# plugins/google
# Google plugin
#

project (google)

	set (google_SOURCES ${google_SOURCE_DIR}/google.cpp)
	set (google_INCLUDES ${google_SOURCE_DIR}/google.h)

	add_library(google MODULE ${google_SOURCES} ${google_INCLUDES})
	set_target_properties (google PROPERTIES PREFIX "")

