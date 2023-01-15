#ifndef YDS_OPENGL_SHADER_PROGRAM_H
#define YDS_OPENGL_SHADER_PROGRAM_H

#include "yds_shader_program.h"

class ysOpenGLShader;
class ysOpenGLShaderProgram : public ysShaderProgram {
    friend class ysOpenGLDevice;

public:
    ysOpenGLShaderProgram();
    ~ysOpenGLShaderProgram();
    unsigned int m_handle;

protected:
    ysOpenGLShader *GetShader(ysShader::ShaderType type);

    
};

#endif /* YDS_OPENGL_SHADER_PROGRAM_H */
