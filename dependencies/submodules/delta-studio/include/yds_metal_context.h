#ifndef YDS_METAL_CONTEXT_H
#define YDS_METAL_CONTEXT_H

#include "yds_window.h"
#include "yds_rendering_context.h"

class ysMetalDevice;

class ysMetalContext : public ysRenderingContext {
    friend ysMetalDevice;

public:
    ysMetalContext();
    ysMetalContext(ysWindowSystemObject::Platform platform);
    virtual ~ysMetalContext();

    virtual ysError Create(ysMetalDevice *device, ysWindow *window);
    virtual ysError Destroy();

    //VkSurfaceKHR GetSurface() const { return m_surface; }

protected:
    ysMetalDevice *m_device;

    //VkSurfaceKHR m_surface;
};

#endif /* YDS_METAL_CONTEXT_H */
