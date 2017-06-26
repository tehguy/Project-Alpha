find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set (SOURCE_FILES
        src/core/core.cpp                       include/core/core.hpp
        src/core/diceroller.cpp                 include/core/diceroller.hpp
        src/core/frame.cpp                      include/core/frame.hpp
        src/core/perlinnoise.cpp                include/core/perlinnoise.hpp
        src/core/randomnumbergenerator.cpp      include/core/randomnumbergenerator.hpp
        src/core/screen.cpp                     include/core/screen.hpp

        src/entity/entity.cpp                   include/entity/entity.hpp
        src/entity/player.cpp                   include/entity/player.hpp

                                                include/enums/enums.hpp)

add_library (engine SHARED ${SOURCE_FILES})
target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine ${CURSES_LIBRARIES})
