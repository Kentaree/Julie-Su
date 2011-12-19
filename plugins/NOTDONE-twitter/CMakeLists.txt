#
# plugins/twitter
# Twitter plugin
#

project (twitter)

	include_directories (twitcurl)

	set (twitter_SOURCES ${twitter_SOURCE_DIR}/twitter.cpp
		${twitter_SOURCE_DIR}/twitcurl/twitcurl.cpp
	)
	set (twitter_INCLUDES ${twitter_SOURCE_DIR}/twitter.h
	)

	add_library(twitter MODULE ${twitter_SOURCES} ${twitter_INCLUDES})
	set_target_properties (twitter PROPERTIES PREFIX "")

