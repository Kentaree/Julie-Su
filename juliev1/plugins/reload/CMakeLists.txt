#
# plugins/reload
# Reload plugin
#

project (reload)

	set (reload_SOURCES ${reload_SOURCE_DIR}/reload.cpp)
	set (reload_INCLUDES ${reload_SOURCE_DIR}/reload.h)

	add_library(reload MODULE ${reload_SOURCES} ${reload_INCLUDES})
	set_target_properties (reload PROPERTIES PREFIX "")
