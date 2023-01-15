//
//  console_shader.metal
//  
//
//  Created by jake on 9/18/22.
//

#include <metal_stdlib>
using namespace metal;

struct VertexIn{
    float2 position [[attribute(0)]];
    float2 texture [[attribute(1)]];
    float4 color [[attribute(2)]];
};

struct VertexOut{
    float4 position [[position]];
    float2 texture;
    float4 color;
};

struct ScreenVariables{
    float4x4 CameraView;
    float4x4 Projection;
};

struct ObjectVariables{
    float4 MulCol;
    float2 TexOffset;
    float2 TexScale;
};

vertex VertexOut vertex_main(
    VertexIn in [[stage_in]],
    constant ScreenVariables &screenVars [[buffer(1)]],
    constant ObjectVariables &objectVars [[buffer(2)]])
{
    VertexOut out;
    out.position = float4(in.position, -1.0, 1.0) * screenVars.CameraView * screenVars.Projection;
    out.texture = in.texture * objectVars.TexScale + objectVars.TexOffset;
    out.color = in.color;
    return out;
}
                             
fragment float4 fragment_main(
    VertexOut in [[stage_in]],
    constant ObjectVariables &objectVars [[buffer(2)]],
    texture2d< float, access::sample > diffuseTex [[texture(0)]])
{
    constexpr sampler s(address::clamp_to_edge, filter::linear);
    float a = diffuseTex.sample(s, in.texture).r;
    return float4(a, a, a, a) * objectVars.MulCol * in.color;
}
