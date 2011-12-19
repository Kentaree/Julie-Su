#
# plugins/vote
# Vote plugin
#

project (vote)

	set (vote_SOURCES ${vote_SOURCE_DIR}/vote.cpp)
	set (vote_INCLUDES ${vote_SOURCE_DIR}/vote.h)

	add_library(vote MODULE ${vote_SOURCES} ${vote_INCLUDES})
	set_target_properties (vote PROPERTIES PREFIX "")

