// Engine : vertex.hpp

#pragma once

#ifndef ENGINE_GRAPHICS_VERTEX_CHPP
#define ENGINE_GRAPHICS_VERTEX_CHPP

#include <memory>

#include <GLM/glm.hpp>

#include "buffer.hpp"

struct Vertex {

    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec4 color;
};

class VertexArray {

public:

    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vtxBuffer);
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& idxBuffer);

    const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const;
    const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const;

private:

    unsigned int vtxAObj;
    unsigned int VertexBufferIndex;

    std::vector<std::shared_ptr<VertexBuffer>> VertexBuffers;
    std::shared_ptr<IndexBuffer> ptrIndexBuffer;
};

#endif
