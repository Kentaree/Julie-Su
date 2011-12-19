#
# plugins/build
# Build plugin
#

project (build)

	set (build_SOURCES ${build_SOURCE_DIR}/build.cpp)
	set (build_INCLUDES ${build_SOURCE_DIR}/build.h)

	add_library(build MODULE ${build_SOURCES} ${build_INCLUDES})
	set_target_properties (build PROPERTIES PREFIX "")

