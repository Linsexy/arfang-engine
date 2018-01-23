include_directories(${rtype_SOURCE_DIR}/sexy_engine/include/)
include_directories(${rtype_SOURCE_DIR}/client/include/)
include_directories(${rtype_SOURCE_DIR}/game_server/include/)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${rtype_SOURCE_DIR}")


FILE(GLOB SRC_SEXY
        src/ecs/*.cpp
        src/ecs/Component/*.cpp
        src/utils/*.cpp
        src/DLLoader/*.cpp
        )

FILE(GLOB INC_SEXY
        include/*.hpp
        include/ecs/*.hpp
        include/ecs/Components/*.hpp
        include/utils/*.hpp
        include/DLLoader/*.hpp
        )

add_library(sexy_engine SHARED ${SRC_SEXY} ${INC_SEXY})
target_link_libraries(sexy_engine stdc++fs )