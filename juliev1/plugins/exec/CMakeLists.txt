#
# plugins/exec
# Exec plugin
#

project (exec)

	set (exec_SOURCES ${exec_SOURCE_DIR}/exec.cpp)
	set (exec_INCLUDES ${exec_SOURCE_DIR}/exec.h)

	add_library(exec MODULE ${exec_SOURCES} ${exec_INCLUDES})
	set_target_properties (exec PROPERTIES PREFIX "")

