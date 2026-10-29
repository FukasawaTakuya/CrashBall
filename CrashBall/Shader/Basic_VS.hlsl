#include "Basic.hlsli"

cbuffer ConstBuffer : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Proj;
    float4x4 WorldInvertTranspose;
}

VSOutput main(VSInput vin)
{
    VSOutput vout;
    
    float4x4 WorldViewProj = mul(Proj, mul(View, World));
    
    // 座標変換
    vout.Position = mul(WorldViewProj, float4(vin.Position, 1.0f));

    // 法線変換
    vout.Normal = normalize(mul((float3x3)WorldInvertTranspose, vin.Normal));
    //vout.Normal = vin.Normal;
    
    // UV座標
    vout.Texcoord = vin.Texcoord;
   
	return vout;
}