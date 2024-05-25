cmake_minimum_required(VERSION 3.23)
project(nowclaire C)

set(CMAKE_C_STANDARD 23)

# Main executable sources
set(SRC_SOURCES
        src/main.c
        src/config.c
)

# Test executable sources
set(TEST_SOURCES
        tests/main.c
        src/config.c
        tests/parse_args_test.c
)

# Add the main executable
add_executable(nowclaire ${SRC_SOURCES})
target_include_directories(nowclaire PUBLIC src)

# Add the test executable
add_executable(test ${TEST_SOURCES})
target_include_directories(test PUBLIC src tests)
