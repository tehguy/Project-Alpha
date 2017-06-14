set (SOURCE_FILES
        ./src/test.cpp)

set (HEADER_FILES
        )

add_library (engine
        ${SOURCE_FILES}
        ${HEADER_FILES})

target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
