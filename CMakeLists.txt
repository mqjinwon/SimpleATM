cmake_minimum_required(VERSION 3.0.0)
project(SimpleAtm VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(SimpleAtmLib STATIC
    src/account.cpp
    src/bank.cpp
    src/atm.cpp
)
target_include_directories(SimpleAtmLib PUBLIC include)

add_executable(SimpleAtm main.cpp)
target_link_libraries(SimpleAtm SimpleAtmLib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
