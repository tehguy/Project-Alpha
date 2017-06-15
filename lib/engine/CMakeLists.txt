set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set (SOURCE_FILES
        src/core/world.cpp                  include/core/world.hpp

        src/entity/entity.cpp               include/entity/entity.hpp
        src/entity/player.cpp               include/entity/player.hpp
        src/entity/monster.cpp              include/entity/monster.hpp

        src/item/item.cpp                   include/item/item.hpp

        src/quests/questcompletionitem.cpp  include/quests/questcompletionitem.hpp)

add_library (engine SHARED
        ${SOURCE_FILES})
target_link_libraries(engine sqlite3)
target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
