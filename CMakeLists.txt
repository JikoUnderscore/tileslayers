cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_GENERATOR_PLATFORM "x64")
set(VCPKG_TARGET_TRIPLET x64-windows-static)
set (CMAKE_CXX_STANDARD 23)

set(CMAKE_TOOLCHAIN_FILE "C:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake")
# ON Windows set one time then remove. Change path if difrent
# set(CMAKE_PREFIX_PATH "C:/tools/vcpkg/installed/x64-windows-static/share")
set(ZLIB_DIR "C:/tools/vcpkg/installed/x64-windows-static/share")

project(tilesslayers VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()



add_executable(${PROJECT_NAME} ./src/main.cpp)
# list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# find_package(ZLIB REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE ZLIB::ZLIB)


# include_directories(${SDL2_INCLUDE_DIRS})
# target_include_directories(${PROJECT_NAME} PRIVATE "C:/tools/vcpkg/installed/x64-windows-static/include")
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image-static)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
