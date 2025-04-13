cmake_minimum_required(VERSION 3.25)

enable_testing()

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test executable
add_executable(testOEngine TestEngine.cpp
        TestKeys.cpp
        TestKeyboard.cpp)
target_link_libraries(testOEngine ${GTEST_LIBRARIES} GTest::Main OEngine)

# Register the test
add_test(NAME EngineTests COMMAND testOEngine)