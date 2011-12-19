#
# plugins/bofh
# BOFH plugin
#

project (bofh)

	set (bofh_SOURCES ${bofh_SOURCE_DIR}/bofh.cpp)
	set (bofh_INCLUDES ${bofh_SOURCE_DIR}/bofh.h)

	add_library(bofh MODULE ${bofh_SOURCES} ${bofh_INCLUDES})
	set_target_properties (bofh PROPERTIES PREFIX "")

