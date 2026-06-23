add_executable(task-3-2 main.cpp binary-tree.cpp)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/text.txt
    ${CMAKE_CURRENT_BINARY_DIR}/text.txt
    COPYONLY
)
