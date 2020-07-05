project(base)

set(LIBRARY_OUTPUT_PATH /home/ruanjian/workspace/project/base/output/release/lib)
aux_source_directory(. DIR_LIB_SRCS)

add_library (base ${DIR_LIB_SRCS})

target_link_libraries(base -lpthread)
