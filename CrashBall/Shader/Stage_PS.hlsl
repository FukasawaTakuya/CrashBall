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

SamplerState Sampler : register(s0);

float4 main(PSInput pin) : SV_TARGET
{
    // テクスチャを使うか
    float useTex = step(0, TextureIndex.x);
    
    // ベースカラー
    float4 pout
    = (Texture.Sample(Sampler, pin.Texcoord) + (1 - useTex))
    + BaseColor;
    
    // ペイントカラー
    float4 paint = PaintTexture.Sample(Sampler, pin.Texcoord);
        
    pout.r = paint.r + pout.r * (1 - paint.a);
    pout.g = paint.g + pout.g * (1 - paint.a);
    pout.b = paint.b + pout.b * (1 - paint.a);
    pout.a = paint.a + pout.a * (1 - paint.a);
    
    float3 lightdire = -normalize(LightDirection);
    float Dot = dot(lightdire, pin.Normal);
    
    float3 LightColor = float3(1, 1, 1) * lerp(0.5, 0.925f, step(-0.4f, Dot));
    
    // ライトの計算
    pout *= float4(LightColor, 1.0f);
            
    return pout;
}