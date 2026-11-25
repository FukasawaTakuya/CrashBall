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
    
    // ディヒューズ色を適用
    pout *= DiffuseColor;

    float3 lightdire = -normalize(LightDirection);
    float NdotL = dot(lightdire, pin.Normal);
    
   // float3 LightColor = float3(1, 1, 1) * lerp(0.8, 1.0, saturate(NdotL));
    float3 LightColor = float3(1, 1, 1) * lerp(0.5, 0.925f, step(-0.4f, NdotL));
        
    float3 lightcoord = pin.LightPosition.xyz / pin.LightPosition.w;
    
    float2 shadowUV;
    shadowUV.x =  lightcoord.x * 0.5f + 0.5f;
    shadowUV.y = -lightcoord.y * 0.5f + 0.5f;
    
    float shadowDepth = ShadowMap.Sample(Sampler, shadowUV).r;

    float bias = 0.001f;
    float shadow;
    shadow = lightcoord.z - bias > shadowDepth ? 0.5f : 1.0f;
    
    pout.xyz *= shadow;
   
    return pout;
}