#
# plugins/todo
# Todo plugin
#

project (todo)

	set (todo_SOURCES ${todo_SOURCE_DIR}/todo.cpp)
	set (todo_INCLUDES ${todo_SOURCE_DIR}/todo.h)

	add_library(todo MODULE ${todo_SOURCES} ${todo_INCLUDES})
	set_target_properties (todo PROPERTIES PREFIX "")

