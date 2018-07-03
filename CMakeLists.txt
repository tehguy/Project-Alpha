cmake_minimum_required(VERSION 3.7.2)
project(Project-Alpha)

add_subdirectory(sln/external-lib/SFML)
add_subdirectory(sln/external-lib/google-protobuf/cmake)

IF(WIN32 OR MSVC)
    set(SFML_EXT_PATH ${PROJECT_SOURCE_DIR}/sln/external-lib/SFML)
    set(PROTOBUF_EXT_PATH ${PROJECT_SOURCE_DIR}/sln/external-lib/google-protobuf)

    set(CompilerFlags
            CMAKE_CXX_FLAGS
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_C_FLAGS
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_RELEASE
            )
    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
ENDIF(WIN32 OR MSVC)