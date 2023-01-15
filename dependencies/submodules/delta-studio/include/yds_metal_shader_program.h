#ifndef YDS_METAL_SHADER_PROGRAM_H
#define YDS_METAL_SHADER_PROGRAM_H

#include "yds_shader_program.h"
#include "../include/yds_metal_device.h"

class ysMetalShader;
class ysMetalShaderProgram : public ysShaderProgram {
    friend class ysMetalDevice;

public:
    ysMetalShaderProgram();
    ~ysMetalShaderProgram();
    ysMetalShader* m_shader;

protected:
    ysMetalShader *GetShader(ysShader::ShaderType type);

    
};

#endif /* YDS_METAL_SHADER_PROGRAM_H */
