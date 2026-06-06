//#pragma once
//#include <vector>
//#include <memory>
//#include "interface_drawable.h"
//#include "interface_updatable.h"
//
//namespace rgp {
//    class Scene : public IDrawable, public IUpdatable {
//    public:
//        Scene()           = default;
//        ~Scene() override = default;
//
//        void update() override {
//            for (auto& u : updatables) u->update();
//        }
//
//        void draw() override {
//            for (auto& d : drawables) d->draw();
//        }
//
//    private:
//        std::vector<std::shared_ptr<IUpdatable>> updatables;
//        std::vector<std::shared_ptr<IDrawable>> drawables;
//    };
//}