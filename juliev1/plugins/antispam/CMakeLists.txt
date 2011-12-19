#
# plugins/antispam
# AntiSpam plugin
#

project (antispam)

	set (antispam_SOURCES ${antispam_SOURCE_DIR}/antispam.cpp)
	set (antispam_INCLUDES ${antispam_SOURCE_DIR}/antispam.h)

	add_library(antispam MODULE ${antispam_SOURCES} ${antispam_INCLUDES})
	set_target_properties (antispam PROPERTIES PREFIX "")

