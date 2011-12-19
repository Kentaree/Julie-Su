#
# plugins/pastebin
# Pastebin plugin
#

project (pastebin)

	set (pastebin_SOURCES ${pastebin_SOURCE_DIR}/pastebin.cpp)
	set (pastebin_INCLUDES ${pastebin_SOURCE_DIR}/pastebin.h)

	add_library(pastebin MODULE ${pastebin_SOURCES} ${pastebin_INCLUDES})
	set_target_properties (pastebin PROPERTIES PREFIX "")

