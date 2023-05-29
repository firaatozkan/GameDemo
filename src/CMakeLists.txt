find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src *.cpp)

add_library(GameDemo ${SOURCES})
add_library(GameDemoShared SHARED ${SOURCES})

target_include_directories(
    GameDemo
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(
    GameDemoShared
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
    GameDemo
    PUBLIC
    SDL2::SDL2
    SDL2_image::SDL2_image
)

target_link_libraries(
    GameDemoShared
    PUBLIC
    SDL2::SDL2
    SDL2_image::SDL2_image
)

if (UNIX OR APPLE)
    target_link_libraries(
        GameDemo
        PUBLIC
        pthread
    )

    target_link_libraries(
        GameDemoShared
        PUBLIC
        pthread
    )
endif()