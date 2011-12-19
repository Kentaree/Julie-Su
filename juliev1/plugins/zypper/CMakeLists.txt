#
# plugins/zypper/CMakeLists.txt
# Portage plugin
#

project (zypper)

	set (zypper_SOURCES ${zypper_SOURCE_DIR}/zypper.cpp)
	set (zypper_INCLUDES ${zypper_SOURCE_DIR}/zypper.h)

	add_library(zypper MODULE ${zypper_SOURCES} ${zypper_INCLUDES})
	set_target_properties (zypper PROPERTIES PREFIX "")

