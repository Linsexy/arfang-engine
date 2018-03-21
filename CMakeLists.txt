cmake_minimum_required(VERSION 3.10)

include_directories(include/)

set(LIB_TYPE SHARED)

if (WIN32)	
set(LIB_TYPE STATIC)
endif()

FILE(GLOB SRC_SEXY
        src/ecs/*.cpp
        src/utils/*.cpp
        src/DLLoader/*.cpp
        )

FILE(GLOB INC_SEXY
        include/*.hpp
        include/ecs/*.hpp
        include/utils/*.hpp
        include/DLLoader/*.hpp
        )

add_library(sexy_engine ${LIB_TYPE} ${SRC_SEXY} ${INC_SEXY})
if (UNIX)
target_link_libraries(sexy_engine stdc++fs )
endif()
