set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set (SOURCE_FILES
        src/sys.cpp     include/sys.hpp)

add_library (system SHARED ${SOURCE_FILES})
target_link_libraries (system sqlite3)
target_include_directories (system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})