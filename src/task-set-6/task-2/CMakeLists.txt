add_executable(task-6-2 main.cpp)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/tape.txt
    ${CMAKE_CURRENT_BINARY_DIR}/tape.txt
    COPYONLY
)
