#
# plugins/phenny
# Phenny services plugin
#

project (phenny)

	set (phenny_SOURCES ${phenny_SOURCE_DIR}/phenny.cpp)
	set (phenny_INCLUDES ${phenny_SOURCE_DIR}/phenny.h)

	add_library(phenny MODULE ${phenny_SOURCES} ${phenny_INCLUDES})
	set_target_properties (phenny PROPERTIES PREFIX "")

