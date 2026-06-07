#pragma once
#include <memory>
#include <array>
#include "scene.h"
#include "entity_text.h"

namespace rgp {
	class MainMenuScene : public Scene {
	public:
		MainMenuScene();
		~MainMenuScene() override;

		void update() override;
		void draw() override;

	private:
		const double m_initTime;
		const std::unique_ptr<TextEntity> m_timerText;

		double m_now = 0.0;
		std::array<char, 32> m_textBuffer{};
	};
};