cmake_minimum_required(VERSION 3.7.2)
project(Project-Alpha)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${SFML_INCLUDE_DIR})

set(SOURCE
                                            src/main.cpp
        src/core/constants.hpp
        src/core/perlin_noise.hpp           src/core/perlin_noise.cpp
        src/core/random_number_gen.hpp

        src/entity/entity.hpp               src/entity/entity.cpp
        src/entity/player.hpp               src/entity/player.cpp

        src/gfx/gfx.hpp                     src/gfx/gfx.cpp
        src/gfx/renderable.hpp              src/gfx/renderable.cpp

        src/world/terrain/terrain.hpp       src/world/terrain/terrain.cpp
        src/world/terrain/terrain_gen.hpp

        src/world/area.hpp                  src/world/area.cpp
        src/world/location.hpp              src/world/location.cpp
        src/world/tile.hpp                  src/world/tile.cpp)


IF(UNIX)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

    find_package(SFML 2 COMPONENTS system graphics window REQUIRED)
ENDIF(UNIX)

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

add_executable(palpha ${SOURCE})
target_link_libraries(palpha ${SFML_LIBRARIES})