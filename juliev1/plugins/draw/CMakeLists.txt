#
# plugins/draw
# Draw plugin
#

project (draw)

	set (draw_SOURCES ${draw_SOURCE_DIR}/draw.cpp)
	set (draw_INCLUDES ${draw_SOURCE_DIR}/draw.h)

	add_library(draw MODULE ${draw_SOURCES} ${draw_INCLUDES})
	set_target_properties (draw PROPERTIES PREFIX "")

	target_link_libraries (draw sqlite3)

