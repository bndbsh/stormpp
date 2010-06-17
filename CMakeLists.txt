PROJECT(storm)

cmake_minimum_required(VERSION 2.4)
if (UNIX)
	add_definitions(-Wall -ansi -g -DUNIX)
else (UNIX)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
endif (UNIX)

include_directories(. src)

#CMake is adding directories in the second list to the linker search path in
#case they are needed to find libraries from the first list (for backwards
#compatibility with CMake 2.4).  Set policy CMP0003 to OLD or NEW to enable
#or disable this behavior explicitly.  Run "cmake --help-policy CMP0003" for
#more information.
if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set (STORM_SOURCES src/archive)

set (STORM_LIBRARIES StormLib)

set (TEST_SOURCES src/test/runner src/test/archivetest)

add_executable(test ${TEST_SOURCES})
target_link_libraries(test storm gtest)

add_dependencies(test engine xflight)
add_custom_command(TARGET test POST_BUILD COMMAND test WORKING_DIRECTORY ${xflight_SOURCE_DIR}/bin)

if (UNIX)
	add_library(storm SHARED ${STORM_SOURCES})
else (UNIX)
	add_library(storm STATIC ${STORM_SOURCES})
endif(UNIX)

target_link_libraries(storm ${STORM_LIBRARIES})

if (MSVC_IDE)
	# hack to get around the "Debug" and "Release" directories cmake tries to add on Windows
	set_target_properties (xflight PROPERTIES PREFIX "../")
	#	set_target_properties (toolset PROPERTIES PREFIX "../")
endif(MSVC_IDE)

