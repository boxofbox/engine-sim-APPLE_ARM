#ifndef YDS_METAL_INPUT_LAYOUT_H
#define YDS_METAL_INPUT_LAYOUT_H

#include "yds_input_layout.h"

#include "yds_dynamic_array.h"

class ysMetalDevice;

struct ysMetalLayoutChannel : public ysDynamicArrayElement {
    int m_length = 0;
    int m_size = 0;
    int m_offset = 0;
    int m_type = 0;
};

class ysMetalInputLayout : public ysInputLayout {
    friend ysMetalDevice;

public:
    ysMetalInputLayout();
    virtual ~ysMetalInputLayout();

protected:
    int m_size;

    ysDynamicArray<ysMetalLayoutChannel, 16> m_channels;
};

#endif /* YDS_METAL_INPUT_LAYOUT_H */
