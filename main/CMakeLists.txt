project(base)

set(EXECUTABLE_OUTPUT_PATH /home/ruanjian/workspace/project/base/output/debug/bin)

add_executable(ByteBuffer_Test ByteBuffer_Test.cc)
target_link_libraries(ByteBuffer_Test base)

add_executable(WeJson_Test WeJson_Test.cc)
target_link_libraries(WeJson_Test base)

