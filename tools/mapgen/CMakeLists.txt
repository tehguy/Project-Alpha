set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SFML COMPONENTS system graphics window REQUIRED)
find_package(Protobuf REQUIRED)

include_directories(${SFML_INCLUDE_DIR}
        ${Protobuf_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../runtime/tools)

set(PROTOBUF_COMPILED_DIR ${PROJECT_SOURCE_DIR}/protos/protos)
set(RUNTIME mapgen)

set(SOURCE_FILES
        src/main/main.cpp)

add_executable(${RUNTIME} ${SOURCE_FILES})
target_include_directories(${RUNTIME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROTOBUF_COMPILED_DIR})
target_link_libraries(${RUNTIME}
        ${SFML_LIBRARIES}
        ${Protobuf_LIBRARIES})