#
# plugins/ragepic
# Ragepic plugin
#

project (ragepics)

        set (ragepics_SOURCES ${ragepics_SOURCE_DIR}/ragepics.cpp)
        set (ragepics_INCLUDES ${ragepics_SOURCE_DIR}/ragepics.h)

        add_library(ragepics MODULE ${ragepics_SOURCES} ${ragepics_INCLUDES})
        set_target_properties (ragepics PROPERTIES PREFIX "")

