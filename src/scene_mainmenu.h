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
		double m_now = 0.0;
	};
};