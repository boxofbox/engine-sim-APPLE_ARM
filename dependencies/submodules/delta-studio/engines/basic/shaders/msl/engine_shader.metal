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
    float4 vertexPos;
    float2 texture;
    float3 normal;
};

struct ScreenVariables{
    float4x4 CameraView;
    float4x4 Projection;
    float4 CameraEye;
    
    float4 FogColor;
    float FogNear;
    float FogFar;
};

struct ObjectVariables{
    float4x4 Transform;
    float2 TexOffset;
    float2 TexScale;
    float4 Scale;
    
    float4 BaseColor;
    float4 Emission;
    float SpecularMix;
    float DiffuseMix;
    float Metallic;
    float DiffuseRoughness;
    float SpecularPower;
    float IncidentSpecular;
    
    int ColorReplace;
    int Lit;
};

struct SkinningVariables {
    float4x4 BoneTransform[256];
};

struct Light {
    float4 Position;
    float4 Color;
    float4 Direction;
    float Attenuation0;
    float Attenuation1;
    int FalloffEnabled;
    int Active;
};

struct Lighting {
    Light Lights[32];
    float4 AmbientLighting;
};


float pow5(float v) {
    return (v * v) * (v * v) * v;
}

float f_diffuse(float3 i, float3 o, float3 h, float3 normal, float power, float roughness) {
    float h_dot_i = dot(h, i);
    float h_dot_i_2 = h_dot_i * h_dot_i;
    float f_d90 = 0.5 + 2 * h_dot_i_2 * roughness;

    float cos_theta_i = dot(i, normal);
    float cos_theta_o = dot(o, normal);

    float f_d = (1 + (f_d90 - 1) * pow5(1 - cos_theta_i)) * (1 + (f_d90 - 1) * pow5(1 - cos_theta_o));
    return clamp(f_d * power * cos_theta_i, 0.0, 1.0);
}

float f_specular(float3 i, float3 o, float3 h, float3 normal, float F0, float power, float specularPower) {
    float3 reflected = -reflect(i, normal);
    float intensity = dot(reflected, o);

    if (intensity < 0) return 0;

    // Fresnel approximation
    float F0_scaled = 0.08 * F0;
    float o_dot_h = dot(o, h);
    float s = pow5(1 - o_dot_h);
    float F = F0_scaled + s * (1 - F0_scaled);

    return clamp(pow(intensity, specularPower) * F * power, 0.0, 1.0);
}

float f_specular_ambient(float3 o, float3 normal, float F0, float power) {
    // Fresnel approximation
    float F0_scaled = 0.08 * F0;
    float o_dot_n = dot(o, normal);
    float s = pow5(1 - o_dot_n);
    float F = F0_scaled + s * (1 - F0_scaled);

    return clamp(F * power, 0.0, 1.0);
}

float linearToSrgb(float u) {
    const float MinSrgbPower = 0.0031308;

    if (u < MinSrgbPower) {
        return 12.92 * u;
    }
    else {
        return 1.055 * pow(u, 1 / 2.4) - 0.055;
    }
}

float srgbToLinear(float u) {
    const float MinSrgbPower = 0.04045;

    if (u < MinSrgbPower) {
        return u / 12.92;
    }
    else {
        return pow((u + 0.055) / 1.055, 2.4);
    }
}

float3 linearToSrgb(float3 v) {
    return float3(
        linearToSrgb(v.r),
        linearToSrgb(v.g),
        linearToSrgb(v.b)
    );
}

float3 srgbToLinear(float3 v) {
    return float3(
        srgbToLinear(v.r),
        srgbToLinear(v.g),
        srgbToLinear(v.b)
    );
}

vertex VertexOut vertex_main(
    VertexIn in [[stage_in]],
    constant ScreenVariables &screenVars [[buffer(1)]],
    constant ObjectVariables &objectVars [[buffer(2)]],
    constant SkinningVariables &skinningVars [[buffer(3)]])
{
    
    VertexOut out;
    float4 inputPos = float4(in.position.xyz, 1.0);
    inputPos.xyz *= objectVars.Scale.xyz;
    inputPos = inputPos * objectVars.Transform;
    out.vertexPos = inputPos;
    inputPos = inputPos * screenVars.CameraView;
    inputPos = inputPos * screenVars.Projection;
    out.position = inputPos;
    
    out.texture = in.texture;
    float4 finalNormal = float4(in.normal.xyz, 0.0);
    out.normal = (finalNormal * objectVars.Transform).xyz;
    return out;
}
                             
fragment float4 fragment_main(
    VertexOut in [[stage_in]],
    constant ScreenVariables &screenVars [[buffer(1)]],
    constant ObjectVariables &objectVars [[buffer(2)]],
    constant SkinningVariables &skinningVars [[buffer(3)]],
    constant Lighting &lightingVars [[buffer(4)]],
    texture2d< float, access::sample > diffuseTex [[texture(0)]])
{
    const float FullSpecular = 1 / 0.08;

    float3 totalLighting = float3(1.0, 1.0, 1.0);
    float3 normal = normalize(in.normal.xyz);

    float4 baseColor;
    //float roughness = 0.5;
    //float power = 1.0;

    if (objectVars.ColorReplace == 0) {
        constexpr sampler s(address::clamp_to_edge, filter::linear);
        float4 diffuse = diffuseTex.sample(s, in.texture).rgba;
        baseColor = float4(srgbToLinear(diffuse.rgb), diffuse.a) * objectVars.BaseColor;
    }
    else {
        baseColor = objectVars.BaseColor;
    }

    totalLighting = baseColor.rgb;

    if (objectVars.Lit == 1) {
        float3 o = normalize(screenVars.CameraEye.xyz - in.vertexPos.xyz);
        float cos_theta_o = dot(o, normal);

        float3 ambientSpecular = f_specular_ambient(o, normal, objectVars.IncidentSpecular, objectVars.SpecularMix) * lightingVars.AmbientLighting.rgb;
        float3 ambientDiffuse = f_diffuse(o, o, o, normal, objectVars.DiffuseMix, objectVars.DiffuseRoughness) * lightingVars.AmbientLighting.rgb * baseColor.rgb;
        float3 ambientMetallic = f_specular_ambient(o, normal, FullSpecular, 1.0) * lightingVars.AmbientLighting.rgb * baseColor.rgb;

        totalLighting = mix(
            ambientSpecular + ambientDiffuse,
            ambientMetallic,
            objectVars.Metallic);
        totalLighting += objectVars.Emission.rgb;

        for (int li = 0; li < 32; ++li) {
            if (lightingVars.Lights[li].Active == 0) continue;

            float3 i = lightingVars.Lights[li].Position.xyz - in.vertexPos.xyz;
            float inv_dist = 1.0 / length(i);
            i *= inv_dist;

            float cos_theta_i = dot(i, normal);

            if (cos_theta_i < 0) continue;
            if (cos_theta_o < 0) continue;

            float3 h = normalize(i + o);
            float3 diffuse = f_diffuse(i, o, h, normal, objectVars.DiffuseMix, objectVars.DiffuseRoughness) * baseColor.rgb * lightingVars.Lights[li].Color.rgb;
            float3 specular = f_specular(i, o, h, normal, objectVars.IncidentSpecular, objectVars.SpecularMix, objectVars.SpecularPower) * lightingVars.Lights[li].Color.rgb;
            float3 metallic = float3(0.0, 0.0, 0.0);

            if (objectVars.Metallic > 0) {
                metallic = f_specular(i, o, h, normal, FullSpecular, 1, objectVars.SpecularPower) * lightingVars.Lights[li].Color.rgb * baseColor.rgb;
            }

            // Spotlight calculation
            float spotCoherence = -dot(i, lightingVars.Lights[li].Direction.xyz);
            float spotAttenuation = 1.0;
            if (spotCoherence > lightingVars.Lights[li].Attenuation0) spotAttenuation = 1.0;
            else if (spotCoherence < lightingVars.Lights[li].Attenuation1) spotAttenuation = 0.0;
            else {
                float t = lightingVars.Lights[li].Attenuation0 - lightingVars.Lights[li].Attenuation1;
                if (t == 0) spotAttenuation = 1.0;
                else spotAttenuation = (spotCoherence - lightingVars.Lights[li].Attenuation1) / t;
            }

            float falloff = 1.0;
            if (lightingVars.Lights[li].FalloffEnabled == 1) {
                falloff = (inv_dist * inv_dist);
            }

            float3 bsdf = mix(
                diffuse + specular,
                metallic,
                objectVars.Metallic);

            totalLighting += falloff * bsdf * spotAttenuation * spotAttenuation * spotAttenuation;
        }
    }
    
    const float distanceToCamera = length(screenVars.CameraEye.xyz - in.vertexPos.xyz);
        const float fogAttenuation = (clamp(distanceToCamera, screenVars.FogNear, screenVars.FogFar) - screenVars.FogNear) / (screenVars.FogFar - screenVars.FogNear);
    return float4(
                            linearToSrgb(
                                mix(
                                    totalLighting.rgb,
                                    screenVars.FogColor.rgb,
                                    fogAttenuation)), baseColor.a);
}
