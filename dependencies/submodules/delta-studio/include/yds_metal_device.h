#ifndef YDS_METAL_DEVICE_H
#define YDS_METAL_DEVICE_H


#include "yds_device.h"
#include <SDL.h>
#include <Foundation/Foundation.hpp>
#include <Foundation/NSString.hpp>
#include <Metal/Metal.hpp>
#include <Metal/shared_ptr.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include "yds_window.h"


class ysMetalDevice : public ysDevice {
    
    ~ysMetalDevice();

public:
    static constexpr DeviceAPI SubclassID = DeviceAPI::Metal;

    ysMetalDevice();

    // Setup
    virtual ysError InitializeDevice();
    virtual ysError DestroyDevice();
    virtual bool CheckSupport();

    // Rendering Contexts
    virtual ysError CreateRenderingContext(ysRenderingContext **renderingContext, ysWindow *window);
    virtual ysError UpdateRenderingContext(ysRenderingContext *context);
    virtual ysError DestroyRenderingContext(ysRenderingContext *&context);
    virtual ysError SetContextMode(ysRenderingContext *context, ysRenderingContext::ContextMode mode);

    virtual ysError CreateOnScreenRenderTarget(ysRenderTarget **newTarget, ysRenderingContext *context, bool depthBuffer);
    virtual ysError CreateOffScreenRenderTarget(ysRenderTarget **newTarget, int width, int height, ysRenderTarget::Format format, bool colorData, bool depthBuffer);
    virtual ysError CreateSubRenderTarget(ysRenderTarget **newTarget, ysRenderTarget *parent, int x, int y, int width, int height);
    virtual ysError ResizeRenderTarget(ysRenderTarget *target, int width, int height, int pwidth, int pheight);
    virtual ysError DestroyRenderTarget(ysRenderTarget *&target);
    virtual ysError SetRenderTarget(ysRenderTarget *target);
    virtual ysError SetDepthTestEnabled(ysRenderTarget *target, bool enable);
    virtual ysError ReadRenderTarget(ysRenderTarget *src, uint8_t *target);

    virtual ysError ClearBuffers(const float *clearColor);
    virtual ysError Present();

    // State
    virtual ysError SetFaceCulling(bool faceCulling);
    virtual ysError SetFaceCullingMode(CullMode cullMode);

    // GPU Buffers
    virtual ysError CreateVertexBuffer(ysGPUBuffer **newBuffer, int size, char *data, bool mirrorToRam = false);
    virtual ysError CreateIndexBuffer(ysGPUBuffer **newBuffer, int size, char *data, bool mirrorToRam = false);
    virtual ysError CreateConstantBuffer(ysGPUBuffer **newBuffer, int size, char *data, bool mirrorToRam = false);
    virtual ysError UseVertexBuffer(ysGPUBuffer *buffer, int stride, int offset);
    virtual ysError UseIndexBuffer(ysGPUBuffer *buffer, int offset);
    virtual ysError UseConstantBuffer(ysGPUBuffer *buffer, int slot);
    virtual ysError EditBufferDataRange(ysGPUBuffer *buffer, char *data, int size, int offset);
    virtual ysError EditBufferData(ysGPUBuffer *buffer, char *data);
    virtual ysError DestroyGPUBuffer(ysGPUBuffer *&buffer);

    // Shaders
    virtual ysError CreateVertexShader(ysShader **newShader, const char *shaderFilename, const char *shaderName);
    virtual ysError CreatePixelShader(ysShader **newShader, const char *shaderFilename, const char *shaderName);
    virtual ysError DestroyShader(ysShader *&shader);

    // Shader Programs
    virtual ysError CreateShaderProgram(ysShaderProgram **newProgram);
    virtual ysError DestroyShaderProgram(ysShaderProgram *&shader, bool destroyShaders = false);
    virtual ysError AttachShader(ysShaderProgram *targetProgram, ysShader *shader);
    virtual ysError LinkProgram(ysShaderProgram *program);
    virtual ysError UseShaderProgram(ysShaderProgram *);

    // Input Layouts
    virtual ysError CreateInputLayout(ysInputLayout **newLayout, ysShader *shader, const ysRenderGeometryFormat *format);
    virtual ysError UseInputLayout(ysInputLayout *layout);
    virtual ysError DestroyInputLayout(ysInputLayout *&layout);

    // Textures
    virtual ysError CreateTexture(ysTexture **texture, const char *fname);
    virtual ysError CreateTexture(ysTexture **texture, int width, int height, const unsigned char *buffer);
    virtual ysError UpdateTexture(ysTexture *texture, const unsigned char *buffer);
    virtual ysError CreateAlphaTexture(ysTexture **texture, int width, int height, const unsigned char *buffer);
    virtual ysError DestroyTexture(ysTexture *&texture);
    virtual ysError UseTexture(ysTexture *texture, int slot);
    virtual ysError UseRenderTargetAsTexture(ysRenderTarget *renderTarget, int slot);

    virtual void Draw(int numFaces, int indexOffset, int vertexOffset);

    virtual MTL::VertexFormat ConvertInputLayoutFormat(ysRenderGeometryChannel::ChannelFormat format);
    virtual int GetStrideOfFormat(MTL::VertexFormat format);


protected:
    NS::AutoreleasePool* pPool;
    MTL::Device* m_device;
    MTL::shared_ptr<MTL::CommandQueue> m_queue;
    MTL::shared_ptr<MTL::CommandBuffer> pCmd;
    MTL::shared_ptr<MTL::RenderPassDescriptor> pRpd;
    MTL::RenderCommandEncoder* pEnc;
    MTL::DepthStencilState* p_depthStencilState;
    MTL::ClearColor clearColor;
    CA::MetalDrawable* m_drawable;
    CA::MetalLayer* swapchain;
    dispatch_semaphore_t _semaphore;
    uint8_t _frame;
    const int kMaxFramesInFlight = 1;
};

#endif /* YDS_METAL_DEVICE_H */
