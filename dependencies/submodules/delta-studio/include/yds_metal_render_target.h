#ifndef YDS_METAL_RENDER_TARGET_H
#define YDS_METAL_RENDER_TARGET_H

#include "yds_render_target.h"

class ysMetalRenderTarget : public ysRenderTarget {
    friend class ysMetalDevice;

public:
    ysMetalRenderTarget();
    virtual ~ysMetalRenderTarget();
};

#endif /* YDS_METAL_RENDER_TARGET_H */
