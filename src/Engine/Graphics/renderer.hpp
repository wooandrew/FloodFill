// Engine : renderer.hpp

#pragma once

#ifndef ENGINE_GRAPHICS_RENDERER_CHPP
#define ENGINE_GRAPHICS_RENDERER_CHPP

#include "camera.hpp"

#include <GLM/glm.hpp>

namespace Renderer {

    struct RenderData {

        glm::vec3 position;
        glm::vec2 scale;
        glm::vec4 color;
    };

    void init(const glm::vec2& _WindowSize);
    void shutdown();
    
    void StartScene(const Camera& camera);
};

#endif
