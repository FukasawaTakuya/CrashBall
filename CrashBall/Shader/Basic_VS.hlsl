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
    
    // ライト計算
    vout.LightColor = float4(1, 1, 1, 1);
    
    vout.Texcoord = vin.Texcoord;
    
    
	return vout;
}