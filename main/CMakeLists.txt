#cmake_minimum_required (VERSION 3.7.2)
#project (CPPAdventure)

set(RUNTIME CPPAdventures)

set (SOURCE_FILES
        src/main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../runtime)
set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN/lib")

add_executable (CPPAdventures ${SOURCE_FILES})
target_link_libraries (${RUNTIME} engine)
link_libraries(${CMAKE_CURRENT_BINARY_DIR}/lib)