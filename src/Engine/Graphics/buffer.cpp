// Engine : buffer.cpp

#include "buffer.hpp"

BufferElement::BufferElement(ShaderDataType _type, const std::string& _name, bool _normalized) {

    type = _type;
    name = _name;
    size = ShaderDataTypeSize(_type);
    normalized = _normalized;
}

uint32_t BufferElement::GetComponentCount() const {
    switch (type) {
    case ShaderDataType::Float:         return 1;
    case ShaderDataType::Float2:        return 2;
    case ShaderDataType::Float3:        return 3;
    case ShaderDataType::Float4:        return 4;
    case ShaderDataType::Mat3:          return 3 * 3;   // Check validity of size
    case ShaderDataType::Mat4:          return 4 * 4;
    case ShaderDataType::Int:           return 1;
    case ShaderDataType::Int2:          return 2;
    case ShaderDataType::Int3:          return 3;
    case ShaderDataType::Int4:          return 4;
    case ShaderDataType::Bool:          return 1;
    default:                            return 0;
    }
}


BufferLayout::BufferLayout() {
    stride = 0;
}

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) 
    : elements(elements) {

    CalculateOffsetsAndStride();
}

unsigned int BufferLayout::GetStride() const {
    return stride;
}
const std::vector<BufferElement>& BufferLayout::GetElements() const {
    return elements;
}

std::vector<BufferElement>::iterator BufferLayout::begin() {
    return elements.begin();
}
std::vector<BufferElement>::iterator BufferLayout::end() {
    return elements.end();
}
std::vector<BufferElement>::const_iterator BufferLayout::begin() const {
    return elements.begin();
}
std::vector<BufferElement>::const_iterator BufferLayout::end() const {
    return elements.end();
}

void BufferLayout::CalculateOffsetsAndStride() {

    size_t offset = 0;
    stride = 0;

    for (auto& element : elements) {

        element.offset = offset;

        offset += element.size;
        stride += element.size;
    }
}


VertexBuffer::VertexBuffer() {
    vtxbobj = 0;
}

VertexBuffer::~VertexBuffer() {
    glad_glDeleteBuffers(1, &vtxbobj);
}

void VertexBuffer::Bind() const {
    glad_glBindBuffer(GL_ARRAY_BUFFER, vtxbobj);
}

void VertexBuffer::Unbind() const {
    glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* _data, const uint32_t _size) {
    glad_glBindBuffer(GL_ARRAY_BUFFER, vtxbobj);
    glad_glBufferSubData(GL_ARRAY_BUFFER, 0, _size, _data);
}

const BufferLayout& VertexBuffer::GetLayout() const {
    return layout;
}
void VertexBuffer::SetLayout(const BufferLayout& _layout) {
    layout = _layout;
}

void VertexBuffer::Create(uint32_t _size) {
    glad_glCreateBuffers(1, &vtxbobj);
    glad_glBindBuffer(GL_ARRAY_BUFFER, vtxbobj);
    glad_glBufferData(GL_ARRAY_BUFFER, _size, nullptr, GL_DYNAMIC_DRAW);
}
void VertexBuffer::Create(float* _vertices, uint32_t _size) {
    glad_glCreateBuffers(1, &vtxbobj);
    glad_glBindBuffer(GL_ARRAY_BUFFER, vtxbobj);
    glad_glBufferData(GL_ARRAY_BUFFER, _size, _vertices, GL_STATIC_DRAW);
}


IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t _size) {

    count = sizeof(indices) / sizeof(uint32_t);

    glad_glCreateBuffers(1, &idxbobj);
    glad_glBindBuffer(GL_ARRAY_BUFFER, idxbobj);
    glad_glBufferData(GL_ARRAY_BUFFER, _size, indices, GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer() {
    glad_glDeleteBuffers(1, &idxbobj);
}

void IndexBuffer::Bind() const {
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxbobj);
}
void IndexBuffer::Unbind() const {
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const unsigned int IndexBuffer::GetCount() const {
    return count;
}
