add_executable(task-4-1 main.cpp hash-table.cpp)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/users.txt
    ${CMAKE_CURRENT_BINARY_DIR}/users.txt
    COPYONLY
)
