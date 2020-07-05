project(base)

set(EXECUTABLE_OUTPUT_PATH /home/ruanjian/workspace/project/base/output/release/bin)

add_executable(parse_json parse_json.cc)
target_link_libraries(parse_json base)

