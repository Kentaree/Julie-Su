#
# plugins/action
# Action plugin
#

project (action)

	set (action_SOURCES ${action_SOURCE_DIR}/action.cpp)
	set (action_INCLUDES ${action_SOURCE_DIR}/action.h)

	add_library(action MODULE ${action_SOURCES} ${action_INCLUDES})
	set_target_properties (action PROPERTIES PREFIX "")

