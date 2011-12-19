#
# plugins/dice
# Dice plugin
#

project (dice)

	set (dice_SOURCES ${dice_SOURCE_DIR}/dice.cpp)
	set (dice_INCLUDES ${dice_SOURCE_DIR}/dice.h)

	add_library(dice MODULE ${dice_SOURCES} ${dice_INCLUDES})
	set_target_properties (dice PROPERTIES PREFIX "")

