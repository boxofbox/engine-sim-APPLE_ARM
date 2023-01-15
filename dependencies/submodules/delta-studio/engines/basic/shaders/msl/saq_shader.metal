//
//  engine_shader.metal
//  
//
//  Created by jake on 9/19/22.
//

#include <metal_stdlib>
using namespace metal;

struct VertexIn{
    float4 position [[attribute(0)]];
    float2 texture [[attribute(1)]];
    float4 normal [[attribute(2)]];
};

struct VertexOut{
    float4 position [[position]];
    float2 texture;
};

vertex VertexOut vertex_main(
    VertexIn in [[stage_in]])
{
    VertexOut out;
    float4 inputPos = float4(in.position.xyz, 1.0);
    out.position = inputPos;
    out.texture = in.texture;
    return out;
}
                             
fragment float4 fragment_main(
    VertexOut in [[stage_in]],
    texture2d< float, access::sample > layer0 [[texture(0)]],
    texture2d< float, access::sample > layer1 [[texture(1)]])
{
    constexpr sampler s(address::clamp_to_edge, filter::linear);
    float4 l0_color = layer0.sample(s, in.texture).rgba;
    float4 l1_color = layer1.sample(s, in.texture).rgba;

    float alpha = l1_color.a;

    return alpha * l1_color + (1 - alpha) * l0_color;
}
