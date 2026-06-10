cmake_minimum_required(VERSION 3.20)
project(SDL3Tutorial LANGUAGES CXX C)

# ============================================================
# C++ / C standards
# ============================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ============================================================
# SDL3 / SDL3_ttf paths
# Mirrors the hard-coded paths in the .vcxproj.
# Override these on the command line if your layout differs:
#   cmake -DSDL3_ROOT=C:/MyLibs/SDL3-3.4.8 ...
# ============================================================
set(SDL3_ROOT     "C:/DevGame/vclib/SDL3-3.4.8"     CACHE PATH "Root of SDL3 installation")
set(SDL3_TTF_ROOT "C:/DevGame/vclib/SDL3_ttf-3.2.0" CACHE PATH "Root of SDL3_ttf installation")

# ============================================================
# Source files
# ============================================================
set(SOURCES
        src/engine_input.cpp
        src/engine_texture.cpp
        src/entity_player.cpp
        src/game.cpp
        src/main.cpp
        src/engine_renderer.cpp
        src/manager_scene.cpp
        src/scene_mainmenu.cpp
        src/scene_level1.cpp
        src/util_logger.cpp
)

set(HEADERS
        src/entity.h
        src/entity_player.h
        src/interface_drawable.h
        src/interface_eventhandlable.h
        src/interface_updatable.h
        src/game.h
        src/engine_input.h
        src/engine_renderer.h
        src/manager_scene.h
        src/engine_texture.h
        src/scene.h
        src/scene_mainmenu.h
        src/scene_level1.h
        src/asset_texture.h
        src/type_vector2f.h
        src/util_logger.h
)

# ============================================================
# Executable
# ============================================================
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# ============================================================
# Include directories
# ============================================================
target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
        "${SDL3_ROOT}/include"
        "${SDL3_TTF_ROOT}/include"
)

# ============================================================
# Link libraries
# ============================================================
target_link_directories(${PROJECT_NAME} PRIVATE
        "${SDL3_ROOT}/lib/x64"
        "${SDL3_TTF_ROOT}/lib/x64"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3.lib
        SDL3_ttf.lib
)

# ============================================================
# Compiler options (mirroring Debug|x64 and Release|x64 settings)
# ============================================================
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

    # Link-time code generation for Release (mirrors LinkTimeCodeGeneration=UseLinkTimeCodeGeneration)
    target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:/LTCG>
            /MANIFEST                   # Enable manifest
    )
endif()

# ============================================================
# Post-build: copy DLLs and assets next to the executable
# Mirrors the PostBuildEvent xcopy commands in the .vcxproj
# ============================================================
set(ASSET_SOURCE_DIR "${CMAKE_SOURCE_DIR}")   # same as $(SolutionDir)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_TTF_ROOT}/lib/x64/SDL3_ttf.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL3_ttf.dll"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/lib/x64/SDL3.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL3.dll"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${ASSET_SOURCE_DIR}/ZenMaruGothic-Medium.ttf"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/ZenMaruGothic-Medium.ttf"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${ASSET_SOURCE_DIR}/player1_sprite.png"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/player1_sprite.png"

        COMMENT "Copying SDL3 DLLs and game assets to output directory"
)

# ============================================================
# Segment heap manifest (EnableSegmentHeap=true)
# Inject the application manifest with heapType="segmentHeap"
# ============================================================
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