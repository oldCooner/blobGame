cmake_minimum_required(VERSION 3.16)

### Definitions
set(PROJECT_NAME blobGame)
set(OUTPUT_NAME ${PROJECT_NAME}.out)
project( ${PROJECT_NAME} VERSION 1.0)

### Setup output dir
### required for ttf librariesd
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs")

### Dependencies
add_subdirectory(libs/SDL3 EXCLUDE_FROM_ALL)
add_subdirectory(libs/SDL3_image EXCLUDE_FROM_ALL)
add_subdirectory(libs/SDL3_ttf EXCLUDE_FROM_ALL)

include_directories("game"
                    "game/comps"
                    "game/levels"
                    "src/SDLTools"
                    )

set(SOURCE_FILES
    main.c
    game/Game.c
    game/comps/WaterGrid.c
    game/levels/BaseLevel.c
    game/levels/LevelOne.c
    game/levels/LevelTwo.c
    game/levels/LevelThree.c
    src/SDLTools/LTimer.c
    )

add_executable( ${OUTPUT_NAME} ${SOURCE_FILES} )
target_compile_options( ${OUTPUT_NAME} PRIVATE -Wall -Werror ) # warning failures for me only
target_link_libraries(${OUTPUT_NAME} PRIVATE SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image SDL3::SDL3)