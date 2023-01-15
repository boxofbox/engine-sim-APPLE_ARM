#include "../include/yds_metal_texture.h"

ysMetalTexture::ysMetalTexture() : ysTexture(DeviceAPI::Metal) {
    m_texture = nullptr;
}

ysMetalTexture::~ysMetalTexture() {
    /* void */
}
