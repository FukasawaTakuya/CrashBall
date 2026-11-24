#include "Basic.hlsli"

cbuffer ConstBuffer : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Proj;
    float4x4 WorldInvertTranspose;
}

cbuffer LightBuffer : register(b1)
{
    float4x4   LightView;
    float4x4 LightProj;
}

VSOutput main(VSInput vin)
{
    VSOutput vout;
    
    float4x4 worldViewProj = mul(Proj, mul(View, World));
    
    // 座標変換
    vout.Position = mul(worldViewProj, float4(vin.Position, 1.0f));

    // 法線変換
    vout.Normal = normalize(mul((float3x3)WorldInvertTranspose, vin.Normal));
    
    // UV座標
    vout.Texcoord = vin.Texcoord;
    
    // 光源視点のポジション
    float4x4 lightWorldViewProj;

    lightWorldViewProj = mul(LightProj, mul(LightView, World));
   
    vout.LightPosition = mul(lightWorldViewProj, float4(vin.Position, 1.0f));
    
	return vout;
}