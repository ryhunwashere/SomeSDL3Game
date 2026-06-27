cmake_minimum_required(VERSION 3.20)
project(SDL3Tutorial LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SDL3_ROOT       "C:/DevGame/vclib/SDL3-3.4.8"       CACHE PATH "Root of SDL3 installation")
set(SDL3_TTF_ROOT   "C:/DevGame/vclib/SDL3_ttf-3.2.0"   CACHE PATH "Root of SDL3_ttf installation")
set(SDL3_MIXER_ROOT "C:/DevGame/vclib/SDL3_mixer-3.2.4" CACHE PATH "Root of SDL3_mixer installation")

set(SOURCES
        src/main.cpp
        src/game.cpp

        src/engine/engine_renderer.cpp
        src/engine/engine_text.cpp

        src/entity/entity_player.cpp
        src/entity/entity_text.cpp
        src/entity/entity_button.cpp

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
        include/entity/entity_player.h
        include/entity/entity_text.h
        include/entity/entity_button.h
        include/entity/entity_bullet.h

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

        include/asset/asset_texture.h
        include/asset/asset_font.h
        include/asset/asset_audio.h
        include/asset/asset_track.h

        include/type/type_vector2f.h
        include/type/type_color.h

        include/util/util_logger.h
        include/util/util_math.h

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

target_link_directories(${PROJECT_NAME} PRIVATE
        "${SDL3_ROOT}/lib/x64"
        "${SDL3_TTF_ROOT}/lib/x64"
        "${SDL3_MIXER_ROOT}/lib/x64"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3.lib
        SDL3_ttf.lib
        SDL3_mixer.lib
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:_DEBUG;_CONSOLE>
        $<$<CONFIG:Release>:NDEBUG;_CONSOLE>
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4                         # Warning level 4
            /permissive-                # Conformance mode

            # Debug-only flags
            $<$<CONFIG:Debug>:
            /MDd                    # MultiThreadedDebug runtime
            /Oy-                    # Keep frame pointers
            /GZ                     # No dynamic debug helpers (UseDynamicDebugging=false)
            /Gw                     # String pooling
            /EHsc                   # Exception handling (SyncCThrow)
            /WX                     # Treat warnings as errors
            /fsanitize=address      # ASAN (EnableASAN=true)
            >

            # Release-only flags
            $<$<CONFIG:Release>:
            /MT                     # MultiThreaded runtime
            /Gy                     # Function-level linking
            /Ob2                    # Inline any suitable
            /Oi                     # Intrinsic functions
            /Ot                     # Favor speed
            /Oy                     # Omit frame pointers
            /arch:AVX2              # AVX2 instruction set
            /fp:fast                # Fast floating point
            /EHsc                   # Exception handling (SyncCThrow)
            /GF                     # String pooling
            /GL                     # Whole-program optimisation (pairs with /LTCG)
            >
    )

    target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:/LTCG>
            /MANIFEST                   # Enable manifest
    )
endif()

set(ASSET_SOURCE_DIR "${CMAKE_SOURCE_DIR}/asset")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_TTF_ROOT}/lib/x64/SDL3_ttf.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL3_ttf.dll"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/lib/x64/SDL3.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL3.dll"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_MIXER_ROOT}/lib/x64/SDL3_mixer.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL3_mixer.dll"

        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSET_SOURCE_DIR}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/asset"

        COMMENT "Copying SDL3 DLLs and game assets to output directory"
)

if(MSVC)
    set(MANIFEST_CONTENT
            "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>
<assembly xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\">
  <application xmlns=\"urn:schemas-microsoft-com:asm.v3\">
    <windowsSettings>
      <heapType xmlns=\"http://schemas.microsoft.com/SMI/2020/WindowsSettings\">segmentHeap</heapType>
    </windowsSettings>
  </application>
</assembly>")
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/SDL3Tutorial.manifest" "${MANIFEST_CONTENT}")
    target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/SDL3Tutorial.manifest")
endif()