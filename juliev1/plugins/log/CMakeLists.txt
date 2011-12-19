#
# plugins/log
# Log plugin
#

project (log)

	set (log_SOURCES ${log_SOURCE_DIR}/log.cpp)
	set (log_INCLUDES ${log_SOURCE_DIR}/log.h)

	add_library(log MODULE ${log_SOURCES} ${log_INCLUDES})
	set_target_properties (log PROPERTIES PREFIX "")

