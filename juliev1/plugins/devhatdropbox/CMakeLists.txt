#
# plugins/devhatdropbox
# Devhat Dropbox
#

project (devhatdropbox)

	include_directories (inotify-tools-3.13/libinotifytools/src)

	set (devhatdropbox_SOURCES ${devhatdropbox_SOURCE_DIR}/devhatdropbox.cpp
		inotify-tools-3.13/libinotifytools/src/inotifytools.c
		inotify-tools-3.13/libinotifytools/src/redblack.c
	)
	set (devhatdropbox_INCLUDES ${devhatdropbox_SOURCE_DIR}/devhatdropbox.h
	)

	add_library(devhatdropbox MODULE ${devhatdropbox_SOURCES} ${devhatdropbox_INCLUDES})
	set_target_properties (devhatdropbox PROPERTIES PREFIX "")

