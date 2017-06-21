set (SOURCE_FILES
        src/main.cpp)

add_executable (CPPAdventures ${SOURCE_FILES})

target_link_libraries (CPPAdventures LINK_PUBLIC engine)
