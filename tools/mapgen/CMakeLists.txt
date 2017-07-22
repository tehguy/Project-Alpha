set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SFML COMPONENTS system graphics window REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../runtime/tools)

set(RUNTIME mapgen)

set(SOURCE_FILES
        src/main/main.cpp)

add_executable(${RUNTIME} ${SOURCE_FILES})
target_link_libraries(${RUNTIME} ${SFML_LIBRARIES})