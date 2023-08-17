// Engine : buffer.hpp

#pragma once

#ifndef ENGINE_GRAPHICS_BUFFER_CHPP
#define ENGINE_GRAPHICS_BUFFER_CHPP

#include <string>
#include <vector>
#include <initializer_list>

#include "shader.hpp"

struct BufferElement {

    std::string name;
    ShaderDataType type;
    unsigned int size;
    size_t offset;
    bool normalized;

    BufferElement() = default;
    BufferElement(ShaderDataType _type, const std::string& _name, bool _normalized = false);

    uint32_t GetComponentCount() const;
};


class BufferLayout {

public:

    BufferLayout();
    BufferLayout(const std::initializer_list<BufferElement>& elements);

    unsigned int GetStride() const;
    const std::vector<BufferElement>& GetElements() const;

    std::vector<BufferElement>::iterator begin();
    std::vector<BufferElement>::iterator end();
    std::vector<BufferElement>::const_iterator begin() const;
    std::vector<BufferElement>::const_iterator end() const;

private:

    // https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_buffer_offset_and_stride
    void CalculateOffsetsAndStride();

    std::vector<BufferElement> elements;
    unsigned int stride;
};

class VertexBuffer {

public:

    VertexBuffer();
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    void SetData(const void* _data, const uint32_t _size);

    const BufferLayout& GetLayout() const;
    void SetLayout(const BufferLayout& _layout);

    void Create(uint32_t _size);
    void Create(float* _vertices, uint32_t _size);

private:

    unsigned int vtxbobj;
    BufferLayout layout;
};

class IndexBuffer {

public:

    IndexBuffer(uint32_t* _indices, uint32_t _size); // Maybe change uint32_t to be a template type
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    const unsigned int GetCount() const;

private:

    unsigned int count;
    unsigned int idxbobj;
};

#endif // !ENGINE_GRAPHICS_BUFFER_CHPP
