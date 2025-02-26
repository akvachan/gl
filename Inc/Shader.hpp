#pragma once

#include <string>
#include <unordered_map>

namespace gl {

enum ShaderType {
  NONE = -1,
  VERTEX = 0,
  FRAGMENT = 1,
};

class Shader {
public:
  Shader(const std::string_view &filePath);
  ~Shader();

  void bind() const;
  void unbind() const;

  void setUniform1f(const std::string &name, const float f);
  void setUniform4f(const std::string &name, const std::array<float, 4> &floats);

private:
  uint32_t _rendererId;
  std::string _uniformName;
  std::unordered_map<std::string, int> _uniformLocations;

  std::pair<std::string, std::string>
  _parseShaderFile(const std::string_view path);
  int _compileShader(GLenum type, const std::string &source) const;
  int _getUniformLocation(const std::string &name);
  uint32_t _createShader(uint32_t vertexShaderId,
                         uint32_t fragmentShaderId) const;
};

} // namespace gl
