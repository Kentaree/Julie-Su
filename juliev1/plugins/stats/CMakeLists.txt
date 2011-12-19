#
# plugins/stats
# Stats plugin
#

project (stats)

	set (stats_SOURCES ${stats_SOURCE_DIR}/stats.cpp ${stats_SOURCE_DIR}/sqlite/database.cpp)
	set (stats_INCLUDES ${stats_SOURCE_DIR}/stats.h ${stats_SOURCE_DIR}/sqlite/database.h)

	add_library(stats MODULE ${stats_SOURCES} ${stats_INCLUDES})
	set_target_properties (stats PROPERTIES PREFIX "")

	target_link_libraries (stats sqlite3)

