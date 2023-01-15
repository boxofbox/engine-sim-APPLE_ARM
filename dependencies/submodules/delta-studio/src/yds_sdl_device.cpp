#include "../include/yds_sdl_device.h"
#include "../include/yds_sdl_window.h"
#include <SDL.h>


#include <vector>

ysSDLDevice::ysSDLDevice() {
    m_renderer = nullptr;
    //m_instance = nullptr;
}

ysSDLDevice::~ysSDLDevice() {
    /* void */
}

ysError ysSDLDevice::InitializeDevice() {
    YDS_ERROR_DECLARE("InitializeDevice");
    printf("init sdl device\n");

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSDLDevice::DestroyDevice() {
    YDS_ERROR_DECLARE("DestroyDevice");


    return YDS_ERROR_RETURN(ysError::None);
}

bool ysSDLDevice::CheckSupport() {
    return false;
}

ysError ysSDLDevice::CreateRenderingContext(ysRenderingContext **renderingContext, ysWindow *window) {
    YDS_ERROR_DECLARE("CreateRenderingContext");
    ysSdlWindow *sdlWindow = static_cast<ysSdlWindow *>(window);
    SetRenderer(sdlWindow->GetRenderer());
    return YDS_ERROR_RETURN(ysError::None);

}

ysError ysSDLDevice::UpdateRenderingContext(ysRenderingContext *context) {
    YDS_ERROR_DECLARE("UpdateRenderingContext");


    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSDLDevice::DestroyRenderingContext(ysRenderingContext *&context) {
    YDS_ERROR_DECLARE("DestroyRenderingContext");

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSDLDevice::SetContextMode(ysRenderingContext *context, ysRenderingContext::ContextMode mode) {
    return ysError();
}

ysError ysSDLDevice::CreateOnScreenRenderTarget(ysRenderTarget **newTarget, ysRenderingContext *context, bool depthBuffer) {
    YDS_ERROR_DECLARE("CreateOnScreenRenderTarget");

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSDLDevice::CreateOffScreenRenderTarget(ysRenderTarget **newTarget, int width, int height, ysRenderTarget::Format format, bool colorData, bool depthBuffer) {
    return ysError();
}

ysError ysSDLDevice::CreateSubRenderTarget(ysRenderTarget **newTarget, ysRenderTarget *parent, int x, int y, int width, int height) {
    return ysError();
}

ysError ysSDLDevice::ResizeRenderTarget(ysRenderTarget *target, int width, int height, int pwidth, int pheight) {
    return ysError();
}

ysError ysSDLDevice::DestroyRenderTarget(ysRenderTarget *&target) {
    return ysError();
}

ysError ysSDLDevice::SetRenderTarget(ysRenderTarget *target) {
    return ysError();
}

ysError ysSDLDevice::SetDepthTestEnabled(ysRenderTarget *target, bool enable) {
    return ysError();
}

ysError ysSDLDevice::ReadRenderTarget(ysRenderTarget *src, uint8_t *target) {
    return ysError();
}

ysError ysSDLDevice::ClearBuffers(const float *clearColor) {
    YDS_ERROR_DECLARE("ClearBuffers");

    SDL_SetRenderDrawColor(m_renderer, 255 * clearColor[0], 255 * clearColor[1], 255 * clearColor[2], 255 * clearColor[3]);
    SDL_RenderClear(m_renderer);
    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSDLDevice::Present() {
     YDS_ERROR_DECLARE("Present");
    SDL_RenderPresent(m_renderer);
    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSDLDevice::SetFaceCulling(bool faceCulling) {
    return ysError();
}

ysError ysSDLDevice::SetFaceCullingMode(CullMode cullMode) {
    return ysError();
}

ysError ysSDLDevice::CreateVertexBuffer(ysGPUBuffer **newBuffer, int size, char *data, bool mirrorToRam) {
    return ysError();
}

ysError ysSDLDevice::CreateIndexBuffer(ysGPUBuffer **newBuffer, int size, char *data, bool mirrorToRam) {
    return ysError();
}

ysError ysSDLDevice::CreateConstantBuffer(ysGPUBuffer **newBuffer, int size, char *data, bool mirrorToRam) {
    return ysError();
}

ysError ysSDLDevice::UseVertexBuffer(ysGPUBuffer *buffer, int stride, int offset) {
    return ysError();
}

ysError ysSDLDevice::UseIndexBuffer(ysGPUBuffer *buffer, int offset) {
    return ysError();
}

ysError ysSDLDevice::UseConstantBuffer(ysGPUBuffer *buffer, int slot) {
    return ysError();
}

ysError ysSDLDevice::EditBufferDataRange(ysGPUBuffer *buffer, char *data, int size, int offset) {
    return ysError();
}

ysError ysSDLDevice::EditBufferData(ysGPUBuffer *buffer, char *data) {
    return ysError();
}

ysError ysSDLDevice::DestroyGPUBuffer(ysGPUBuffer *&buffer) {
    return ysError();
}

ysError ysSDLDevice::CreateVertexShader(ysShader **newShader, const char *shaderFilename, const char *shaderName) {
    return ysError();
}

ysError ysSDLDevice::CreatePixelShader(ysShader **newShader, const char *shaderFilename, const char *shaderName) {
    return ysError();
}

ysError ysSDLDevice::DestroyShader(ysShader *&shader) {
    return ysError();
}

ysError ysSDLDevice::CreateShaderProgram(ysShaderProgram **newProgram) {
    return ysError();
}

ysError ysSDLDevice::DestroyShaderProgram(ysShaderProgram *&shader, bool destroyShaders) {
    return ysError();
}

ysError ysSDLDevice::AttachShader(ysShaderProgram *targetProgram, ysShader *shader) {
    return ysError();
}

ysError ysSDLDevice::LinkProgram(ysShaderProgram *program) {
    return ysError();
}

ysError ysSDLDevice::UseShaderProgram(ysShaderProgram *) {
    return ysError();
}

ysError ysSDLDevice::CreateInputLayout(ysInputLayout **newLayout, ysShader *shader, const ysRenderGeometryFormat *format) {
    return ysError();
}

ysError ysSDLDevice::UseInputLayout(ysInputLayout *layout) {
    return ysError();
}

ysError ysSDLDevice::DestroyInputLayout(ysInputLayout *&layout) {
    return ysError();
}

ysError ysSDLDevice::CreateTexture(ysTexture **texture, const char *fname) {
    return ysError();
}

ysError ysSDLDevice::CreateTexture(ysTexture **texture, int width, int height, const unsigned char *buffer) {
    return ysError();
}

ysError ysSDLDevice::UpdateTexture(ysTexture *texture, const unsigned char *buffer) {
    return ysError();
}

ysError ysSDLDevice::CreateAlphaTexture(ysTexture **texture, int width, int height, const unsigned char *buffer) {
    YDS_ERROR_DECLARE("CreateTexture");

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSDLDevice::DestroyTexture(ysTexture *&texture) {
    return ysError();
}

ysError ysSDLDevice::UseTexture(ysTexture *texture, int slot) {
    return ysError();
}

ysError ysSDLDevice::UseRenderTargetAsTexture(ysRenderTarget *renderTarget, int slot) {
    return ysError();
}

void ysSDLDevice::Draw(int numFaces, int indexOffset, int vertexOffset) {
}


// ctor magic to register as a subclass
static ysRegisterSubclass<ysSDLDevice> reg();
