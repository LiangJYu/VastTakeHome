cmake_minimum_required(VERSION 3.14)

project(
    moon_mining
    VERSION 0.1.0
    DESCRIPTION "Simulation for lunar He-3 space mining operation."
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)


# ---- Declare library ----

add_library(
    moon_mining_lib OBJECT
    src/MiningTruck.cpp
    src/OperationClock.cpp
)

target_include_directories(
    moon_mining_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src"
)

target_compile_features(moon_mining_lib PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(moon_mining_exe src/main.cpp)
add_executable(moon_mining::exe ALIAS moon_mining_exe)

set_property(TARGET moon_mining_exe PROPERTY OUTPUT_NAME moon_mining)

target_compile_features(moon_mining_exe PRIVATE cxx_std_20)

target_link_libraries(moon_mining_exe PRIVATE moon_mining_lib)
target_compile_features(moon_mining_exe PRIVATE cxx_std_20)

# ---- GoogleTest Integration ----

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ---- Enable CTest and add tests ----
enable_testing()

set(TESTFILES
    tests/MiningTruck.cpp
    tests/OperationClockTest.cpp
    )

foreach(FILENAME ${TESTFILES})
    get_filename_component(TARGET ${FILENAME} NAME_WE)

    # Add test executable
    add_executable(${TARGET} ${FILENAME})

    target_link_libraries(${TARGET} PRIVATE GTest::gtest_main moon_mining_lib)

    target_include_directories(${TARGET} PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_compile_features(${TARGET} PRIVATE cxx_std_20)

    add_test(NAME ${TARGET} COMMAND ${TARGET})
endforeach()
