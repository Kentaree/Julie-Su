#
# bot/CMakeLists.txt
# Builds the main part for Julie-Su
#

cmake_minimum_required (VERSION 2.4.2)

set (CMAKE_BUILD_TYPE debug)

project (juliesu)

	set(juliesu_INCLUDES
		${juliesu_SOURCE_DIR}/bot.h
		${juliesu_SOURCE_DIR}/config.h
		${juliesu_SOURCE_DIR}/connection.h
		${juliesu_SOURCE_DIR}/global.h
		${juliesu_SOURCE_DIR}/level.h
		${juliesu_SOURCE_DIR}/managedplugin.h
		${juliesu_SOURCE_DIR}/message.h
		${juliesu_SOURCE_DIR}/output.h
		${juliesu_SOURCE_DIR}/plugin.h
		${juliesu_SOURCE_DIR}/pluginmanager.h
	)

	set (juliesu_SOURCES
		${juliesu_SOURCE_DIR}/bot.cpp
		${juliesu_SOURCE_DIR}/config.cpp
		${juliesu_SOURCE_DIR}/connection.cpp
		${juliesu_SOURCE_DIR}/global.cpp
		${juliesu_SOURCE_DIR}/level.cpp
		${juliesu_SOURCE_DIR}/main.cpp
		${juliesu_SOURCE_DIR}/managedplugin.cpp
		${juliesu_SOURCE_DIR}/message.cpp
		${juliesu_SOURCE_DIR}/output.cpp
		${juliesu_SOURCE_DIR}/plugin.cpp
		${juliesu_SOURCE_DIR}/pluginmanager.cpp
	)


	add_executable (juliesu ${juliesu_SOURCES} ${juliesu_INCLUDES})
	target_link_libraries (juliesu dl expat)

