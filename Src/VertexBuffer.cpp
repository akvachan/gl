#include "VertexBuffer.hpp"
#include "Renderer.hpp"

namespace gl {

VertexBuffer::VertexBuffer(const void *data, uint32_t size) {
  GL_CALL(glGenBuffers(1, &_rendererId));
  GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, _rendererId));
  GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() { GL_CALL(glDeleteBuffers(1, &_rendererId)); }

void VertexBuffer::bind() const {
  GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, _rendererId));
}

void VertexBuffer::unbind() const { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); }

} // namespace gl
