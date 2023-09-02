find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src *.cpp)

add_executable(GameDemo ${SOURCES})

target_include_directories(
    GameDemo
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
    GameDemo
    PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
)

add_compile_definitions(ASSETS_DIR="${PROJECT_SOURCE_DIR}/assets/")