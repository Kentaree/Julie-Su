#
# plugins/big
# Bug plugin
#

project (bug)

	set (bug_SOURCES ${bug_SOURCE_DIR}/bug.cpp)
	set (bug_INCLUDES ${bug_SOURCE_DIR}/bug.h)

	add_library(bug MODULE ${bug_SOURCES} ${bug_INCLUDES})
	set_target_properties (bug PROPERTIES PREFIX "")

