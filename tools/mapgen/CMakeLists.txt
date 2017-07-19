set(RUNTIME mapgen)

set(SOURCE_FILES
        src/main/main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../runtime/tools)

add_executable(${RUNTIME} ${SOURCE_FILES})