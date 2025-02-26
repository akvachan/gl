#pragma once

#include <cstdlib>

namespace gl {

class VertexBuffer {
public:
  VertexBuffer(const void *data, uint32_t size);
  ~VertexBuffer();

  void bind() const;
  void unbind() const;

private:
  uint32_t _rendererId;
};

}
