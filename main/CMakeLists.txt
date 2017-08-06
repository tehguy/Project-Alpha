set(RUNTIME CPPClient)

set (SOURCE_FILES
        src/main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../runtime)

if(UNIX)
    set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN/lib")
ENDIF(UNIX)

add_executable (${RUNTIME} ${SOURCE_FILES})
target_link_libraries (${RUNTIME} engine)
link_libraries(${CMAKE_CURRENT_BINARY_DIR}/lib)