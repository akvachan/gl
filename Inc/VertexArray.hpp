#pragma once

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

namespace gl {

class VertexArray {
public:
  VertexArray();
  ~VertexArray();
  void addBuffer(const VertexBuffer &vertexBuffer,
                 VertexBufferLayout &vertexBufferLayout);
  void bind() const;
  void unbind() const;

private:
  uint32_t _rendererId;
};

} // namespace gl
