#include "Basic.hlsli"

// マテリアル情報
cbuffer ConstBuffer : register(b0)
{
    float4 BaseColor;
    float4 TextureIndex;
    float4 LightDirection;
}

Texture2D Texture : register(t0);

Texture2D PaintTexture : register(t1);

SamplerState samplaer : register(s0);

float4 main(PSInput pin) : SV_TARGET
{
    // テクスチャを使うか
    float useTex = step(0, TextureIndex.x);
    
    // ベースカラー
    float4 pout
    = (Texture.Sample(samplaer, pin.Texcoord) + (1 - useTex))
    + BaseColor;
    
    float4 paint = PaintTexture.Sample(samplaer, pin.Texcoord);
    float isPaint = step(0.5f, paint.a);
    pout = paint * isPaint + float4(1, 1, 1, 1) * (1 - isPaint) * pout;
    
    float3 lightdire = -normalize(LightDirection);
    float Dot = dot(lightdire, pin.Normal);
    
    float3 LightColor = float3(1, 1, 1) * lerp(0.5, 0.925f, step(-0.4f, Dot));

    // ライトの計算
    pout *= float4(LightColor, 1.0f);
            
    return pout;
}