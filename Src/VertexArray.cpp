#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Utils.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

namespace gl {

VertexArray::VertexArray() { GL_CALL(glGenVertexArrays(1, &_rendererId)); }

VertexArray::~VertexArray() { GL_CALL(glDeleteVertexArrays(1, &_rendererId)); }

void VertexArray::bind() const { GL_CALL(glBindVertexArray(_rendererId)); }

void VertexArray::unbind() const { GL_CALL(glBindVertexArray(0)); }

void VertexArray::addBuffer(const VertexBuffer &vertexBuffer,
                            VertexBufferLayout &vertexBufferLayout) {
  bind();
  vertexBuffer.bind();
  const std::vector<VertexBufferElement> &elements =
      vertexBufferLayout.getElements();

  uint32_t offset = 0;
  for (uint32_t i = 0; i < elements.size(); i++) {
    const auto &[type, count, normalized] = elements[i];
    GL_CALL(glEnableVertexAttribArray(i));
    GL_CALL(glVertexAttribPointer(
        i, count, type, normalized, vertexBufferLayout.getStride(),
        reinterpret_cast<void *>(static_cast<uintptr_t>(offset))));
    offset += count * getTypeSize(type);
  }
}

} // namespace gl
