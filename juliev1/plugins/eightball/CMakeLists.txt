#
# plugins/eightball
# eightball plugin
#

project (eightball)

	set (eightball_SOURCES ${eightball_SOURCE_DIR}/eightball.cpp)
	set (eightball_INCLUDES ${eightball_SOURCE_DIR}/eightball.h)

	add_library (eightball MODULE ${eightball_SOURCES} ${eightball_INCLUDES})
	set_target_properties (eightball PROPERTIES PREFIX "")

