#
# plugins/help
# Help plugin
#

project (help)

	set (help_SOURCES ${help_SOURCE_DIR}/help.cpp)
	set (help_INCLUDES ${help_SOURCE_DIR}/help.h)

	add_library(help MODULE ${help_SOURCES} ${help_INCLUDES})
	set_target_properties (help PROPERTIES PREFIX "")

