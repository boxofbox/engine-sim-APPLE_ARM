#include "../include/yds_metal_shader.h"


ysMetalShader::ysMetalShader() : ysShader(DeviceAPI::Metal) {
    m_shader = nullptr;
    m_pipelineState = nullptr;
}

ysMetalShader::~ysMetalShader() {
    /* void */
}
