#
# plugins/apt/CMakeLists.txt
# Apt plugin
#

project (apt)

	set (apt_SOURCES ${apt_SOURCE_DIR}/apt.cpp)
	set (apt_INCLUDES ${apt_SOURCE_DIR}/apt.h)

	add_library(apt MODULE ${apt_SOURCES} ${apt_INCLUDES})
	set_target_properties (apt PROPERTIES PREFIX "")

