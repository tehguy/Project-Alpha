cmake_minimum_required(VERSION 3.7.2)
project(Project-Alpha)

IF(WIN32 OR MSVC)
    set(SFML_EXT_PATH ${PROJECT_SOURCE_DIR}/lib/SFML)

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