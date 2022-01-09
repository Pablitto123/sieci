cmake_minimum_required(VERSION 3.17)
project(sieci)

set(CMAKE_CXX_STANDARD 17)
#add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)
include_directories(
        include
)

set(SOURCE_FILES
        src/storage_types.cpp
        src/package.cpp
        src/nodes.cpp
        src/factory.cpp
        src/helpers.cpp
        )

add_executable(sieci ${SOURCE_FILES} main.cpp)






set(SOURCES_FILES_TESTS
        test/test_package.cpp
        test/test_package.cpp
        test/test_package_mm.cpp
        test/test_package_pm.cpp
        test/test_Wfactory_mm.cpp
        )

# Dodaj konfigurację typu `Test`.
add_executable(my_project_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

# Dodaj katalogi z plikami nagłówkowymi wyłącznie do konkretnej konfiguracji (tu: `Test`).
target_include_directories(my_project_test PUBLIC
        ../googletest-master/googlemock/include
        ../googletest-master/googletest/include
        )

# Dodaj podkatalog `googletest-master`.
add_subdirectory(../googletest-master googletest-master)

# Podlinkuj bibliotekę o identyfikatorze `gmock` (w pliku CMake) wyłącznie do konkretnej
# konfiguracji (tu: `Test`).
target_link_libraries(my_project_test gmock)