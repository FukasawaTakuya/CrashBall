#include "Basic.hlsli"

// マテリアル情報
cbuffer ConstBuffer : register(b0)
{
    float4 BaseColor;
    float4 TextureIndex;
    float4 LightDirection;
    float4 DiffuseColor;
}

Texture2D Texture : register(t0);

SamplerState Sampler : register(s0);

Texture2D<float> ShadowMap : register(t1);

float4 main(PSInput pin) : SV_TARGET
{
    // テクスチャを使うか
    float useTex = step(0, TextureIndex.x);
    
    // ベースカラー
    float4 pout 
    = (Texture.Sample(Sampler, pin.Texcoord) + (1 - useTex))
    + BaseColor;
    
    // ディヒューズ色を適用
    pout *= DiffuseColor;

    float3 lightdire = -normalize(LightDirection);
    float Dot = dot(lightdire, pin.Normal);
        
    float3 lightcoord = pin.LightPosition.xyz / pin.LightPosition.w;
    
    float2 shadowUV;
    shadowUV.x =  lightcoord.x * 0.5f + 0.5f;
    shadowUV.y = -lightcoord.y * 0.5f + 0.5f;
    
    float shadowDepth = ShadowMap.Sample(Sampler, shadowUV).r;
    float shadow = 1.0f;

    shadow = lightcoord.z - 0.0015f > shadowDepth ?
                0.5f : 1.0f;
    
    pout.xyz *= shadow;
   
    return pout;
}