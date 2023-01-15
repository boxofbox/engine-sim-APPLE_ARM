#include "../include/yds_metal_shader_program.h"

#include "../include/yds_metal_shader.h"

ysMetalShaderProgram::ysMetalShaderProgram() : ysShaderProgram(DeviceAPI::Metal) {
    m_shader = nullptr;
}

ysMetalShaderProgram::~ysMetalShaderProgram() {
    /* void */
}

ysMetalShader *ysMetalShaderProgram::GetShader(ysShader::ShaderType type) {
    return static_cast<ysMetalShader *>(m_shaderSlots[(int)type]);
}
