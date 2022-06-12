project(GMParser)
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)



include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



add_executable(${PROJECT_NAME}
    src/main.cc
    src/gmparser.cc
    src/site_generator.cc

)

enable_testing()

add_executable(
  gm_tests
  tests/gmparser_tests.cc
  tests/site_gen_tests.cc
  src/site_generator.cc
  src/gmparser.cc
)
target_link_libraries(
  gm_tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(gm_tests)