
# Galen Cochrane
# Copyright (C) 2016
# This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)

# No lesser version of cMake may be used.
cmake_minimum_required( VERSION 3.3 )

# Assign a project name
project( BNO055 )

option( BNO055_COMPILE_STANDALONE "Use included main to test bno055" ON)

if( NOT WIN32 )
    # these are the compiler flags to be used on gcc
    set( CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_CXX_FLAGS} -ggdb3     -Wall -std=c++11         " )
    set( CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_CXX_FLAGS} -Ofast     -Wall -std=c++11 -DNDEBUG" )
    set( CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS} -Og -ggdb3 -Wall -std=c++11 -DNDEBUG" )
endif()

set( LIBS         ${LIBS}         )
set( INCLUDE_DIRS ${INCLUDE_DIRS} )
set( SOURCE_FILES ${SOURCE_FILES}
        bno055DataSheet.h
        bno055DataStructures.cpp
        bno055DataStructures.h
        Bno055Interface.cpp
        Bno055Interface.h
        UartInterface.cpp
        UartInterface.h
        )

include_directories( ${INCLUDE_DIRS} )
if ( BNO055_COMPILE_STANDALONE )
    set( SOURCE_FILES ${SOURCE_FILES} test.cpp )
    add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )
    target_link_libraries( ${PROJECT_NAME} ${LIBS} )
else( BNO055_COMPILE_STANDALONE )
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} )
    target_link_libraries( ${PROJECT_NAME} ${LIBS} )
    target_include_directories( ${PROJECT_NAME} ${INCLUDE_DIRS} )
endif( BNO055_COMPILE_STANDALONE )