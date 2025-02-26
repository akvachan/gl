#pragma once

#include <cstdlib>

namespace gl {

class IndexBuffer {
public:
  IndexBuffer(const uint32_t *data, uint32_t count);
  ~IndexBuffer();

  void bind() const;
  void unbind() const;

  inline uint32_t getCount() const;

private:
  uint32_t _rendererId;
  uint32_t _count;
};

} // namespace gl
