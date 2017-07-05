find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

#find_package(Boost 1.64.0 COMPONENTS serialization REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../runtime/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../runtime/lib)
set(CMAKE_INSTALL_RPATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set (SOURCE_FILES
        src/core/core.cpp                       include/core/core.hpp
        src/core/diceroller.cpp                 include/core/diceroller.hpp
        src/core/frame.cpp                      include/core/frame.hpp
        src/core/frame_game.cpp                 include/core/frame_game.hpp
        src/core/frame_stats.cpp                include/core/frame_stats.hpp
        src/core/perlinnoise.cpp                include/core/perlinnoise.hpp
        src/core/randomnumbergenerator.cpp      include/core/randomnumbergenerator.hpp
        src/core/screen.cpp                     include/core/screen.hpp

        src/entity/entity.cpp                   include/entity/entity.hpp
        src/entity/player.cpp                   include/entity/player.hpp

                                                include/enums/enums.hpp

        src/item/item.cpp                       include/item/item.hpp

        src/world/area.cpp                      include/world/area.hpp
        src/world/location.cpp                  include/world/location.hpp

        src/world/terrain/grass.cpp             include/world/terrain/grass.hpp
        src/world/terrain/snow.cpp              include/world/terrain/snow.hpp
        src/world/terrain/terrain.cpp           include/world/terrain/terrain.hpp
        src/world/terrain/wall.cpp              include/world/terrain/wall.hpp
        src/world/terrain/water.cpp             include/world/terrain/water.hpp)

add_library (engine SHARED ${SOURCE_FILES})
target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine ${CURSES_LIBRARIES})