#include "IndexBuffer.hpp"
#include "Renderer.hpp"

namespace gl {

IndexBuffer::IndexBuffer(const uint32_t *data, uint32_t count)
    : _count(count) {
  GL_CALL(glGenBuffers(1, &_rendererId));
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId));
  GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data,
                       GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() { GL_CALL(glDeleteBuffers(1, &_rendererId)); }

void IndexBuffer::bind() const {
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId));
}

void IndexBuffer::unbind() const { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); }

inline uint32_t IndexBuffer::getCount() const { return _count; }

}
