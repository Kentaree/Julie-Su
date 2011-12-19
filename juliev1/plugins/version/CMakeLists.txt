#
# plugins/version
# Version plugin
#

project (version)

	set (version_SOURCES ${version_SOURCE_DIR}/version.cpp)
	set (version_INCLUDES ${version_SOURCE_DIR}/version.h)

	add_library(version MODULE ${version_SOURCES} ${version_INCLUDES})
	set_target_properties (version PROPERTIES PREFIX "")

