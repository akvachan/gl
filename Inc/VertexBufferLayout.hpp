#pragma once

#include "Gl.hpp"

#include <vector>

namespace gl {

struct VertexBufferElement {
  uint32_t type;
  int32_t count;
  uint8_t normalized;
};

class VertexBufferLayout {
public:
  VertexBufferLayout();

  void addInt(int32_t count);
  void addFloat(int32_t count);
  void addUint(int32_t count);
  void addUbyte(int32_t count);

  const std::vector<VertexBufferElement> &getElements() const;
  uint32_t getStride() const;

private:
  std::vector<VertexBufferElement> _elements;
  uint32_t _stride;
};

} // namespace gl
