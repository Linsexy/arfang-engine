cmake_minimum_required(VERSION 3.9)

project (Arfang)

set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include/)

set(LIB_TYPE SHARED)

if (WIN32)	
set(LIB_TYPE STATIC)
endif()

FILE(GLOB SRC_Af
        src/ecs/*.cpp
        src/utils/*.cpp
        src/DLLoader/*.cpp
        )

FILE(GLOB INC_Af
        include/*.hpp
        include/ecs/*.hpp
        include/utils/*.hpp
        include/DLLoader/*.hpp
        )

add_library(af_engine ${LIB_TYPE} ${SRC_Af} ${INC_Af})
if (UNIX)
target_link_libraries(af_engine stdc++fs)
endif()
