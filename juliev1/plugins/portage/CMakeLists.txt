#
# plugins/portage
# Portage plugin
#

project (portage)

	set (portage_SOURCES ${portage_SOURCE_DIR}/portage.cpp)
	set (portage_INCLUDES ${portage_SOURCE_DIR}/portage.h)

	add_library(portage MODULE ${portage_SOURCES} ${portage_INCLUDES})
	set_target_properties (portage PROPERTIES PREFIX "")

