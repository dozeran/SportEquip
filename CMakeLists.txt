
cmake_minimum_required(VERSION 3.16)

project(SportEquip VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# GoogleTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

# Бібліотека проєкту
add_library(sport_equip_lib
    src/Money.cpp
    src/SportEquipment.cpp
    src/Library.cpp
)

target_include_directories(sport_equip_lib PUBLIC include)

# Основна програма
add_executable(SportEquip
    src/main.cpp
)

target_link_libraries(SportEquip PRIVATE sport_equip_lib)

# Автоматичні тести
enable_testing()

add_executable(SportEquipTests
    tests/test_operators.cpp
)

target_link_libraries(SportEquipTests
    PRIVATE
    sport_equip_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(SportEquipTests)

# AddressSanitizer та UndefinedBehaviorSanitizer
option(ENABLE_SANITIZERS "Enable AddressSanitizer and UBSan" OFF)

if(ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    foreach(target sport_equip_lib SportEquip SportEquipTests)
        target_compile_options(${target} PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
        )

        target_link_options(${target} PRIVATE
            -fsanitize=address,undefined
        )
    endforeach()
endif()
