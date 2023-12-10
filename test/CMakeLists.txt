project(coinhsl-cpp-test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} coinhsl-linsolve gfortran GTest::gtest_main)

gtest_discover_tests(${PROJECT_NAME})
