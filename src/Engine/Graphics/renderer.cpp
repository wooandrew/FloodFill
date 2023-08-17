// Engine : renderer.cpp

#include "renderer.hpp"

#include "vertex.hpp"
#include "buffer.hpp"

#include <memory>

namespace Renderer {

    struct RendererData {

        RendererData() = default;

        // Batch Rendering Params -- Per batch
        const uint32_t MaxQuads = 10000;
        const uint32_t MaxVertices = MaxQuads * 4;
        const uint32_t MaxIndices = MaxQuads * 6;

        // Vertex Array Data
        std::unique_ptr<VertexArray> __quad_vtx_array;
        std::shared_ptr<VertexBuffer> __quad_vtx_buffer;
        unsigned int __quad_index_count = 0;

        Vertex* __quad_vtx_buf_base = nullptr;
        Vertex* __quad_vtx_buf_ptr = nullptr;

        glm::vec2 WindowSize = { 1000, 618 };
    };

    RendererData rd;

    void init(const glm::vec2& _WindowSize) {

        rd.WindowSize = _WindowSize;

        // Create Vertex Array
        rd.__quad_vtx_array = std::make_unique<VertexArray>();
        rd.__quad_vtx_buf_base = new Vertex[rd.MaxVertices];
        rd.__quad_vtx_buf_ptr = rd.__quad_vtx_buf_base;

        // Create Vertex Buffer
        rd.__quad_vtx_buffer = std::make_shared<VertexBuffer>();
        rd.__quad_vtx_buffer->Create(rd.MaxVertices * sizeof(Vertex));

        rd.__quad_vtx_buffer->SetLayout({ { ShaderDataType::Float3, "a_Position" },
                                          { ShaderDataType::Float2, "a_TexCoord" },
                                          { ShaderDataType::Float4, "a_Color"},
                                          { ShaderDataType::Float, "a_TexSlot"} });

        rd.__quad_vtx_array->AddVertexBuffer(rd.__quad_vtx_buffer);

        // Create Index Buffer
        uint32_t* __quad_indices = new uint32_t[rd.MaxIndices];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < rd.MaxIndices; i += 6) {

            __quad_indices[i + 0] = offset + 0;
            __quad_indices[i + 1] = offset + 1;
            __quad_indices[i + 2] = offset + 2;

            __quad_indices[i + 3] = offset + 2;
            __quad_indices[i + 4] = offset + 3;
            __quad_indices[i + 5] = offset + 0;

            offset += 4;
        }

        std::shared_ptr<IndexBuffer> __quad_ib = std::make_shared<IndexBuffer>(__quad_indices, rd.MaxIndices * sizeof(uint32_t));
        rd.__quad_vtx_array->SetIndexBuffer(__quad_ib);
    }
}
