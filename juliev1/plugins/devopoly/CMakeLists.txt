#
# plugins/devopoly
# Devopoly plugin
#

project (devopoly)

	set (devopoly_SOURCES
		${devopoly_SOURCE_DIR}/boardpiece.cpp
		${devopoly_SOURCE_DIR}/devopoly.cpp
		${devopoly_SOURCE_DIR}/goboardpiece.cpp
		${devopoly_SOURCE_DIR}/propertyboardpiece.cpp
		${devopoly_SOURCE_DIR}/player.cpp
	)

	set (devopoly_INCLUDES
		${devopoly_SOURCE_DIR}/boardpiece.h
		${devopoly_SOURCE_DIR}/devopoly.h
		${devopoly_SOURCE_DIR}/goboardpiece.h
		${devopoly_SOURCE_DIR}/propertyboardpiece.h
		${devopoly_SOURCE_DIR}/player.h
	)

	add_library(devopoly MODULE ${devopoly_SOURCES} ${devopoly_INCLUDES})
	set_target_properties (devopoly PROPERTIES PREFIX "")

