set (SOURCE_FILES
                                            include/core/core.hpp
        src/core/location.cpp               include/core/location.hpp
        src/core/world.cpp                  include/core/world.hpp

        src/entity/entity.cpp               include/entity/entity.hpp
        src/entity/player.cpp               include/entity/player.hpp
        src/entity/monster.cpp              include/entity/monster.hpp

                                            include/enum/enums.hpp

        src/item/item.cpp                   include/item/item.hpp

        src/quests/quest.cpp                include/quests/quest.hpp
        src/quests/questcompletionitem.cpp  include/quests/questcompletionitem.hpp)

add_library (engine SHARED ${SOURCE_FILES})
target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
