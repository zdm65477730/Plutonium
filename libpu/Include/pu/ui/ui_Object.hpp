
#pragma once
#include <pu/ui/ui_Types.hpp>
#include <pu/render/render_Renderer.hpp>

namespace pu::ui {

    class Object {

        private:
            Mutex lock;

        public:
            Object() : lock(CreateMutex()) {}

            virtual PositionAndSize GetPositionAndSize() = 0;
            virtual void Render() = 0;

            void DoRender() PU_LOCKED_SCOPE(this->lock, {
                this->Render();
            })

            template<typename O, typename ...Args>
            inline static std::shared_ptr<Object> New(Args &&...args) {
                return NewInstance<Object, O>(args...);
            }
    };
}