set (SOURCE_FILES
        src/core/core.cpp                   include/core/core.hpp
        src/core/diceroller.cpp             include/core/diceroller.hpp
        src/core/location.cpp               include/core/location.hpp
        src/core/locationlogic.cpp          include/core/locationlogic.hpp
        src/quests/questlogic.cpp           include/quests/questlogic.hpp
        src/core/randomnumbergenerator.cpp  include/core/randomnumbergenerator.hpp
        src/core/world.cpp                  include/core/world.hpp

        src/entity/entity.cpp               include/entity/entity.hpp
        src/entity/player.cpp               include/entity/player.hpp
        src/entity/monster.cpp              include/entity/monster.hpp

                                            include/enum/enums.hpp

        src/item/healingpotion.cpp          include/item/healingpotion.hpp
        src/item/inventoryitem.cpp          include/item/inventoryitem.hpp
        src/item/item.cpp                   include/item/item.hpp
        src/item/lootitem.cpp               include/item/lootitem.hpp
        src/item/weapon.cpp                 include/item/weapon.hpp

        src/quests/playerquest.cpp          include/quests/playerquest.hpp
        src/quests/quest.cpp                include/quests/quest.hpp
        src/quests/questcompletionitem.cpp  include/quests/questcompletionitem.hpp)

add_library (engine SHARED ${SOURCE_FILES})
#target_link_libraries (engine system)
target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
