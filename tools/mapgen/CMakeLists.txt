IF(WIN32)
    set(SFML_INCLUDE_DIR ${SFML_EXT_PATH}/include)
    set(Protobuf_INCLUDE_DIRS ${PROTOBUF_EXT_PATH}/src)

    set(SFML_LIBRARIES sfml-graphics sfml-system sfml-window)
    set(Protobuf_LIBRARIES libprotobuf libprotobuf-lite libprotoc)
ENDIF(WIN32)
IF(UNIX)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

    find_package(SFML COMPONENTS system graphics window REQUIRED)
    find_package(Protobuf REQUIRED STATIC)
ENDIF(UNIX)

include_directories(${SFML_INCLUDE_DIR}
        ${Protobuf_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../runtime)

set(PROTOBUF_COMPILED_DIR ${PROJECT_SOURCE_DIR}/protos/protos)
set(RUNTIME mapgen)

set(SOURCE_FILES
        src/main/main.cpp

        src/mcore/mcore.cpp         include/mapgen/mcore/mcore.hpp

        src/mworld/marea.cpp        include/mapgen/mworld/marea.hpp
        src/mworld/mlocation.cpp    include/mapgen/mworld/mlocation.hpp)

add_executable(${RUNTIME} ${SOURCE_FILES})
target_include_directories(${RUNTIME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROTOBUF_COMPILED_DIR})
target_link_libraries(${RUNTIME}
        ${SFML_LIBRARIES}
        ${Protobuf_LIBRARIES}
        engine)
link_libraries(${PROJECT_SOURCE_DIR}/lib)