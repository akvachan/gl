#include "VertexBufferLayout.hpp"

namespace gl {

VertexBufferLayout::VertexBufferLayout()
    : _elements({}), _stride(0) {}

const std::vector<VertexBufferElement> &
VertexBufferLayout::getElements() const {
  return _elements;
}

void VertexBufferLayout::addInt(int32_t count) {
  _elements.push_back({GL_INT, count, GL_FALSE});
  constexpr uint32_t typeSize = sizeof(int);
  uint32_t width = count * typeSize;
  _stride += width;
}

void VertexBufferLayout::addFloat(int32_t count) {
  _elements.push_back({GL_FLOAT, count, GL_FALSE});
  constexpr uint32_t typeSize = sizeof(float);
  uint32_t width = count * typeSize;
  _stride += width;
}

void VertexBufferLayout::addUint(int32_t count) {
  _elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  constexpr uint32_t typeSize = sizeof(uint32_t);
  uint32_t width = count * typeSize;
  _stride += width;
}

void VertexBufferLayout::addUbyte(int32_t count) {
  _elements.push_back({GL_UNSIGNED_BYTE, count, GL_FALSE});
  constexpr uint32_t typeSize = sizeof(uint8_t);
  uint32_t width = count * typeSize;
  _stride += width;
}

uint32_t VertexBufferLayout::getStride() const { return _stride; }


} // namespace gl
