#include "Basic.hlsli"

cbuffer ConstBuffer : register(b0)
{
    float4x4 WorldViewProj;
    float4x4 WorldInvertTranspose;
    float4 LightDirection;
}

VSOutput main(VSInput vin)
{
    VSOutput vout;
    
    // 座標変換
    vout.Position = mul(WorldViewProj, float4(vin.Position, 1.0f));
    
    float3 lightdire = LightDirection;
    float Dot = dot(lightdire, vin.Normal);
    
    // ライト計算
    vout.LightColor = float4(1,1,1,1) * lerp(0.75, 1.0f, saturate(Dot));
    
    vout.Texcoord = vin.Texcoord;
    
    
	return vout;
}