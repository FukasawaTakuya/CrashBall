#include "Basic.hlsli"

// マテリアル情報
cbuffer ConstBuffer : register(b0)
{
    float4 BaseColor;
    float4 TextureIndex;
    float4 LightDirection;
    float4 DiffuseColor;
}

// モデルのテクスチャ
Texture2D Texture : register(t0);

// シャドウマップ
Texture2D<float> ShadowMap : register(t1);

// 塗装テクスチャ
Texture2D PaintTexture : register(t2);

// サンプラー
SamplerState Sampler : register(s0);

float4 main(PSInput pin) : SV_TARGET
{
    // テクスチャを使うか
    float useTex = step(0, TextureIndex.x);
    
    // ベースカラー
    float4 pout
    = (Texture.Sample(Sampler, pin.Texcoord) + (1 - useTex))
    + BaseColor;
    
    pout *= DiffuseColor;
    
    // ペイントカラー
    float4 paint = PaintTexture.Sample(Sampler, pin.Texcoord);
        
    pout.r = paint.r + pout.r * (1 - paint.a);
    pout.g = paint.g + pout.g * (1 - paint.a);
    pout.b = paint.b + pout.b * (1 - paint.a);
    pout.a = paint.a + pout.a * (1 - paint.a);
    
    float3 lightdire = -normalize(LightDirection);
    float NdotL = dot(lightdire, pin.Normal);
    
    float3 LightColor = float3(1, 1, 1) * lerp(0.8, 1.0, saturate(NdotL));
    //float3 LightColor = float3(1, 1, 1) * lerp(0.5, 0.925f, step(-0.4f, NdotL));
    
    // 光源視点の
    float3 lightcoord = pin.LightPosition.xyz / pin.LightPosition.w;
    
    float2 shadowUV;
    shadowUV.x =  lightcoord.x * 0.5f + 0.5f;
    shadowUV.y = -lightcoord.y * 0.5f + 0.5f;
    
    // 
    float shadowDepth = ShadowMap.Sample(Sampler, shadowUV).r;
    float bias = 0.0007f;
    float shadow;
    shadow = lightcoord.z - bias > shadowDepth ? 0.5f : 1.0f;
    
    shadow = step(shadowUV.x, 1.0f) * shadow;
    shadow = step(0.0f, shadowUV.x) * shadow;
    shadow = step(shadowUV.y, 1.0f) * shadow;
    shadow = step(0.0f, shadowUV.y) * shadow;
    
    pout.xyz *= shadow;
    
    return pout;
}