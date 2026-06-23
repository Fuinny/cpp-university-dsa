add_executable(task-2-1 main.cpp linked-list.cpp)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/grades.txt
    ${CMAKE_CURRENT_BINARY_DIR}/grades.txt
    COPYONLY
)
