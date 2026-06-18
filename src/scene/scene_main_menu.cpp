#include <SDL3/SDL.h>
#include "scene/scene_main_menu.h"

#include "constant/constant.h"
#include "manager/manager_scene.h"
#include "util/util_math.h"

constexpr float MIN_WIDTH = 200.0f;
constexpr float MAX_WIDTH = 400.0f;
constexpr float INCREMENT_SPEED = 20.0f;
constexpr float SPEED_PER_SECOND = INCREMENT_SPEED * 60.0f;

rgp::MainMenuScene::MainMenuScene(GameContext& ctx) : Scene(ctx),
    m_menuMusic(std::make_unique<Track>(m_ctx.getAudioManager(), AudioType::MenuMusic, true)),
    m_musicStatusText(ctx.getTextFactory().create(FontType::ZenMaruMedium32Center, "")),
    m_buttonList([&ctx] {
        std::array<std::unique_ptr<ButtonEntity>, 3> buttons;

        constexpr auto COLOR = constant::color::WHITE_OPAQUE_F;

        for (size_t i = 0; i < buttons.size(); ++i) {
            const std::array<std::string, 3> labels = { "Play", "Options", "Exit" };
            constexpr float HEIGHT      = 50.0f;
            constexpr float BASE_Y      = 50.0f;
            constexpr float OFFSET_Y    = 100.0f;
            const auto index = static_cast<float>(i);
            const auto destRect = SDL_FRect{
                .x = 10.0f,
                .y = BASE_Y * index + 20.0f * index + OFFSET_Y,
                .w = MIN_WIDTH,
                .h = HEIGHT
            };

            buttons[i] = std::make_unique<ButtonEntity>(ctx, destRect, COLOR, labels[i]);
        }

        return buttons;
    }())
{
    updateButtonColors();
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
    const float dt = m_ctx.getTimeManager().getDeltaTime();
    m_now += dt;

    updateSelectedButton();

    animateButtonWidths(dt);

    for (const auto& button : m_buttonList) button->update();

    const auto& input = m_ctx.getInputManager();

    if (input.isKeyJustPressed(SDL_SCANCODE_ESCAPE)) {
        m_selectedMenu = m_buttonList.size() - 1;
        updateButtonColors();
    }

    if (input.isKeyJustPressed(SDL_SCANCODE_BACKSPACE)) {
        if (m_menuMusic->isPaused()) {
            m_menuMusic->resume();
            m_musicStatusText->setText("Music is playing");
        } else if (m_menuMusic->isPlaying()) {
            m_menuMusic->pause();
            m_musicStatusText->setText("Music is paused");
        }
    }

    if (input.isKeyJustPressed(SDL_SCANCODE_RETURN)) {
        if (m_selectedMenu == 0) return SceneType::LevelOne;
        if (m_selectedMenu == m_buttonList.size() - 1) return SceneType::Exit;
    }

    return SceneType::Continue;
}

void rgp::MainMenuScene::updateSelectedButton() {
    const auto& input      = m_ctx.getInputManager();
    const bool downPressed = input.isKeyJustPressed(SDL_SCANCODE_DOWN);
    const bool upPressed   = input.isKeyJustPressed(SDL_SCANCODE_UP);

    if (!downPressed && !upPressed) return;

    if (downPressed && m_selectedMenu < m_buttonList.size() - 1) {
        ++m_selectedMenu;
    } else if (upPressed && m_selectedMenu > 0) {
        --m_selectedMenu;
    }

    updateButtonColors();
}

void rgp::MainMenuScene::animateButtonWidths(const float dt) {
    for (size_t i = 0; i < m_buttonList.size(); ++i) {
        constexpr float ANIMATION_SPEED = 2.0f;
        if (i == m_selectedMenu) {
            m_buttonProgress[i] += dt * ANIMATION_SPEED;
            if (m_buttonProgress[i] > 1.0f) m_buttonProgress[i] = 1.0f;
        } else {
            m_buttonProgress[i] -= dt * ANIMATION_SPEED;
            if (m_buttonProgress[i] < 0.0f) m_buttonProgress[i] = 0.0f;
        }

        const float curveT = util::math::easeInOutCubed(m_buttonProgress[i]);

        const float targetWidth = MIN_WIDTH + curveT * (MAX_WIDTH - MIN_WIDTH);

        const float currentWidth = m_buttonList[i]->getWidth();
        const float deltaWidth = targetWidth - currentWidth;

        m_buttonList[i]->increaseWidth(deltaWidth);
    }
}

void rgp::MainMenuScene::updateButtonColors() const {
    for (size_t i = 0; i < m_buttonList.size(); ++i) {
        const bool isSelected = i == m_selectedMenu;

        const auto bgColor   = isSelected ? constant::color::BLACK_OPAQUE_F : constant::color::WHITE_OPAQUE_F;
        const auto textColor = isSelected ? constant::color::WHITE_OPAQUE   : constant::color::BLACK_OPAQUE;

        m_buttonList[i]->setColor(bgColor);
        m_buttonList[i]->getText()->setColor(textColor);
    }
}

void rgp::MainMenuScene::draw() {
    const auto interval = m_now * 2.0f;
    const auto red      = 0.5f + 0.5f * SDL_sinf(interval);
    const auto green    = 0.5f + 0.5f * SDL_sinf(interval + SDL_PI_F * 2.0f / 3.0f);
    const auto blue     = 0.5f + 0.5f * SDL_sinf(interval + SDL_PI_F * 4.0f / 3.0f);

    m_ctx.getRendererEngine().drawScreen({ red, green, blue, SDL_ALPHA_OPAQUE_FLOAT });

    for (const auto& button : m_buttonList) button->draw();

    m_musicStatusText->draw();
}