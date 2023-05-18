cmake_minimum_required(VERSION 3.0)
project(TestTask)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(SOURCES
    main.cpp
)
add_executable(main ${SOURCES})
target_include_directories(main PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/include)

enable_testing()

add_executable(UnitTests tests/unit_tests.cpp )
target_include_directories(UnitTests PRIVATE ${GTEST_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(UnitTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(FunctionalTests tests/functional_tests.cpp )
target_include_directories(FunctionalTests PRIVATE ${GTEST_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(FunctionalTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} "stdc++fs" "c++experimental")

add_executable(PerformanceTests tests/performance_tests.cpp )
target_include_directories(PerformanceTests PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(PerformanceTests "stdc++fs" "c++experimental")
