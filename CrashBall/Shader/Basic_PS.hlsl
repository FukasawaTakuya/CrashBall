#include "Basic.hlsli"

// マテリアル情報
cbuffer ConstBuffer : register(b1)
{
    float4 baseColor;
    float4 materialIndex;
    float4 LightDirection;
}

Texture2D Texture : register(t0);

SamplerState samplaer : register(s0);

float4 main(PSInput pin) : SV_TARGET
{
    // テクスチャを使うか
    float useTex = step(0, materialIndex.x);
    
    // ベースカラー
    float4 pout 
    = Texture.Sample(samplaer, pin.Texcoord) * useTex
    + baseColor * (1 - useTex);

    float3 lightdire = normalize(LightDirection);
    float Dot = dot(lightdire, pin.Normal);
    
    float3 LightColor = float3(1, 1, 1) * lerp(0.8, 1.0, saturate(Dot));
    //float3 LightColor = float3(1, 1, 1) * lerp(0.5, 0.925f, step(-0.4f, Dot));

    // ライトの計算
    pout *= float4(LightColor, 1.0f);
    
    return pout;
}