#include "Basic.hlsli"

cbuffer ConstBuffer : register(b0)
{
    float4x4 World;                 // ワールド行列
    float4x4 View;                  // ビュー行列
    float4x4 Proj;                  // プロジェクション行列
    float4x4 WorldInvertTranspose;  // ワールド逆転置行列
}

cbuffer LightBuffer : register(b1)
{
    float4x4 LightView; // 光源視点のビュー行列
    float4x4 LightProj; // 光源視点のプロジェクション行列
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