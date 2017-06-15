set (SOURCE_FILES
        src/main.cpp)

set (HEADER_FILES
        )

add_executable (CPPAdventures
        ${SOURCE_FILES}
        ${HEADER_FILES})

target_link_libraries (CPPAdventures LINK_PUBLIC engine)
