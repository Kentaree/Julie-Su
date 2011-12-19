#
# plugins/echo
# Echo plugin
#

project (echo)

	set (echo_SOURCES ${echo_SOURCE_DIR}/echo.cpp)
	set (echo_INCLUDES ${echo_SOURCE_DIR}/echo.h)

	add_library(echo MODULE ${echo_SOURCES} ${echo_INCLUDES})
	set_target_properties (echo PROPERTIES PREFIX "")

