#
# plugins/wolfram
# Wolfram plugin
#

project (wolfram)

	set (wolfram_SOURCES ${wolfram_SOURCE_DIR}/wolfram.cpp)
	set (wolfram_INCLUDES ${wolfram_SOURCE_DIR}/wolfram.h)

	add_library(wolfram MODULE ${wolfram_SOURCES} ${wolfram_INCLUDES})
	set_target_properties (wolfram PROPERTIES PREFIX "")

