#include "../include/yds_metal_context.h"

ysMetalContext::ysMetalContext()
    : ysRenderingContext(DeviceAPI::Metal, ysWindowSystemObject::Platform::Unknown) 
{
    /*void*/
}

ysMetalContext::ysMetalContext(ysWindowSystemObject::Platform platform)
    : ysRenderingContext(DeviceAPI::Metal, ysWindowSystemObject::Platform::Unknown) 
{
    /* void */
}

ysMetalContext::~ysMetalContext() {
    /* void */
}

ysError ysMetalContext::Create(ysMetalDevice *device, ysWindow *window) {
    YDS_ERROR_DECLARE("Create");

    m_device = device;

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysMetalContext::Destroy() {
    YDS_ERROR_DECLARE("DestroyContext");

    return YDS_ERROR_RETURN(ysError::None);
}
