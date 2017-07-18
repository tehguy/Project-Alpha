set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SFML COMPONENTS system graphics window REQUIRED)

include_directories(${SFML_INCLUDE_DIR})


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../runtime/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../runtime/lib)
set(CMAKE_INSTALL_RPATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set (SOURCE_FILES
                                                include/core/constants.hpp
        src/core/core.cpp                       include/core/core.hpp
        src/core/perlinnoise.cpp                include/core/perlinnoise.hpp
        src/core/randomnumbergenerator.cpp      include/core/randomnumbergenerator.hpp

        src/gfx/gfx.cpp                         include/gfx/gfx.hpp
        src/gfx/renderable.cpp                  include/gfx/renderable.hpp

        src/entity/entity.cpp                   include/entity/entity.hpp
        src/entity/player.cpp                   include/entity/player.hpp

                                                include/enums/enums.hpp

        src/item/item.cpp                       include/item/item.hpp

        src/world/area.cpp                      include/world/area.hpp
        src/world/location.cpp                  include/world/location.hpp

        src/world/special/specialtile.cpp       include/world/special/specialtile.hpp

        src/world/terrain/grass.cpp             include/world/terrain/grass.hpp
        src/world/terrain/snow.cpp              include/world/terrain/snow.hpp
        src/world/terrain/terrain.cpp           include/world/terrain/terrain.hpp
        src/world/terrain/mountain.cpp          include/world/terrain/mountain.hpp
        src/world/terrain/water.cpp             include/world/terrain/water.hpp)

add_library (engine SHARED ${SOURCE_FILES})
target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine
        ${SFML_LIBRARIES})