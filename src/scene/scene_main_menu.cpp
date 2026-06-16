#include <SDL3/SDL.h>
#include "scene/scene_main_menu.h"

#include "constant/constant.h"
#include "manager/manager_scene.h"

rgp::MainMenuScene::MainMenuScene(GameContext& ctx) : Scene(ctx),
    m_menuMusic(std::make_unique<Track>(m_ctx.getAudioManager(), AudioType::MenuMusic, true)),
    m_musicStatusText(ctx.getTextFactory().create(FontType::ZenMaruMedium24, "")),
    m_button(std::make_unique<ButtonEntity>(
        ctx,
        SDL_FRect{ .x = 10.0f, .y = 50.0f, .w = 50.0f, .h = 50.0f },
        constant::color::WHITE_OPAQUE_F,
        [&ctx](ButtonEntity& btn) -> void {
            const auto& input = ctx.getInputManager();

            if (input.isKeyJustPressed(SDL_SCANCODE_L)) {
                if (btn.getColor() == constant::color::WHITE_OPAQUE_F) {
                    btn.setColor(constant::color::BLACK_OPAQUE_F);
                    SDL_Log("Button color is now black");
                } else {
                    btn.setColor(constant::color::WHITE_OPAQUE_F);
                    SDL_Log("Button color is now white");
                }
            }

            constexpr float WIDTH_INCREMENT_VALUE = 10.0f;

            if (input.isKeyDown(SDL_SCANCODE_RIGHTBRACKET) && btn.getWidth() <= 1000.0f)
                btn.increaseWidth(WIDTH_INCREMENT_VALUE);

            if (input.isKeyDown(SDL_SCANCODE_LEFTBRACKET) && btn.getWidth() >= 0.0f)
                btn.increaseWidth(-WIDTH_INCREMENT_VALUE);
        }))
{
    m_menuMusic->play();

    m_musicStatusText->setColor(constant::color::WHITE_OPAQUE);
    m_musicStatusText->setPosition({ 5.0f, 300.0f });
    m_musicStatusText->setText("Music is playing");

    SDL_Log("Main menu scene loaded.");
}

rgp::MainMenuScene::~MainMenuScene() {
	SDL_Log("Main menu scene unloaded.");
}

auto rgp::MainMenuScene::update() -> SceneType {
    m_now += m_ctx.getTimeManager().getDeltaTime();

    m_button->update();

    const auto& input = m_ctx.getInputManager();

    if (input.isKeyJustPressed(SDL_SCANCODE_P))
        return SceneType::LevelOne;

    if (input.isKeyJustPressed(SDL_SCANCODE_BACKSPACE)) {
        if (m_menuMusic->isPaused()) {
            m_menuMusic->resume();
            m_musicStatusText->setText("Music is playing");
        }
        else if (m_menuMusic->isPlaying()) {
            m_menuMusic->pause();
            m_musicStatusText->setText("Music is paused");
        }
    }

    return SceneType::Continue;
}

void rgp::MainMenuScene::draw() {
    const auto interval = m_now * 2.0f;
    const auto red      = 0.5f + 0.5f * SDL_sinf(interval);
    const auto green    = 0.5f + 0.5f * SDL_sinf(interval + SDL_PI_F * 2.0f / 3.0f);
    const auto blue     = 0.5f + 0.5f * SDL_sinf(interval + SDL_PI_F * 4.0f / 3.0f);

    m_ctx.getRendererEngine().draw({ red, green, blue, SDL_ALPHA_OPAQUE_FLOAT });

    m_button->draw();

    m_musicStatusText->draw();
}