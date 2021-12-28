cmake_minimum_required(VERSION 3.13)
project(new_electoral_college_state_categories)

set(SRC_DIR ./src)

add_executable(main ${SRC_DIR}/main.c ${SRC_DIR}/party.c ${SRC_DIR}/rating.c ${SRC_DIR}/state.c)
target_link_libraries(main json-c)
target_compile_definitions(main PRIVATE INCLUDED_LIB)