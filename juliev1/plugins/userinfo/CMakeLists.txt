#
# plugins/userinfo
# UserInfo plugin
#

project (userinfo)

	set (userinfo_SOURCES ${userinfo_SOURCE_DIR}/userinfo.cpp)
	set (userinfo_INCLUDES ${userinfo_SOURCE_DIR}/userinfo.h)

	add_library(userinfo MODULE ${userinfo_SOURCES} ${userinfo_INCLUDES})
	set_target_properties (userinfo PROPERTIES PREFIX "")

