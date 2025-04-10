find_package(SFML REQUIRED)

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
    sfml::sfml
)