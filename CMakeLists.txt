cmake_minimum_required(VERSION 3.20)
project(SDL3Tutorial LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_mixer REQUIRED)

set(SOURCES
        src/main.cpp
        src/game.cpp

        src/engine/engine_renderer.cpp
        src/engine/engine_text.cpp

        src/entity/entity_player.cpp
        src/entity/entity_text.cpp
        src/entity/entity_button.cpp
        src/entity/entity_enemy.cpp

        src/manager/manager_input.cpp
        src/manager/manager_texture.cpp
        src/manager/manager_audio.cpp
        src/manager/manager_scene.cpp
        src/manager/manager_time.cpp
        src/manager/manager_event.cpp
        src/manager/manager_bullet.cpp

        src/scene/scene_main_menu.cpp
        src/scene/scene_level_one.cpp

        src/asset/asset_font.cpp
        src/asset/asset_texture.cpp
        src/asset/asset_audio.cpp
        src/asset/asset_track.cpp

        src/factory/factory_font.cpp
)

set(HEADERS
        include/game.h
        include/game_context.h
        include/except_sdl.h

        include/engine/engine_renderer.h
        include/engine/engine_text.h

        include/entity/entity.h
        include/entity/entity_character.h
        include/entity/entity_player.h
        include/entity/entity_enemy.h
        include/entity/entity_text.h
        include/entity/entity_button.h
        include/entity/entity_bullet.h
        include/entity/entity_player.h

        include/manager/manager_input.h
        include/manager/manager_texture.h
        include/manager/manager_scene.h
        include/manager/manager_time.h
        include/manager/manager_audio.h
        include/manager/manager_event.h
        include/manager/manager_bullet.h

        include/scene/scene.h
        include/scene/scene_main_menu.h
        include/scene/scene_level_one.h

        include/interface/interface_drawable.h
        include/interface/interface_event_handlable.h
        include/interface/interface_updatable.h
        include/interface/interface_fixed_updatable.h

        include/asset/asset_texture.h
        include/asset/asset_font.h
        include/asset/asset_audio.h
        include/asset/asset_track.h

        include/type/type_vector2f.h
        include/type/type_color.h
        include/type/type_circle.h

        include/util/util_logger.h
        include/util/util_math.h
        include/util/util_intersect.h
        include/util/util_storage.h

        include/constant/constant.h

        include/factory/factory_font.h

        include/enum/enum_fonttype.h
        include/enum/enum_scenetype.h
        include/enum/enum_texture_type.h
        include/enum/enum_audio_type.h
        include/enum/enum_bullet_type.h

        include/event/event.h
        include/event/event_scene_change.h
        include/event/event_player_lives_change.h
        include/event/event_pause_state_change.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
        "${SDL3_ROOT}/include"
        "${SDL3_TTF_ROOT}/include"
        "${SDL3_MIXER_ROOT}/include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:_DEBUG;_CONSOLE>
        $<$<CONFIG:Release>:NDEBUG;_CONSOLE>
)

set(ASSET_SOURCE_DIR "${CMAKE_SOURCE_DIR}/asset")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSET_SOURCE_DIR}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/asset"
        COMMENT "Copying game assets"
)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE:SDL3_ttf::SDL3_ttf>
            $<TARGET_FILE:SDL3_mixer::SDL3_mixer>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMENT "Copying SDL3 DLLs"
    )
endif()