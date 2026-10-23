#include "Basic.hlsli"

// マテリアル情報
cbuffer ConstBuffer : register(b1)
{
    float4 baseColor;
    float4 materialIndex;
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

    // ライトの計算
    pout *= float4(pin.LightColor, 1.0f);
    
    return pout;
}