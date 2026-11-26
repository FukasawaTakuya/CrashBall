#include "Basic.hlsli"

// マテリアル情報
cbuffer ConstBuffer : register(b0)
{
    float4 BaseColor;       // 使用色
    float4 TextureIndex;    // 使用テクスチャインデックス
    float4 LightDirection;  // ライト方向
    float4 DiffuseColor;    // ディヒューズ色
    float2 MaskSize;        // マスクのサイズ
}

// モデルのテクスチャ
Texture2D Texture : register(t0);

// シャドウマップ
Texture2D<float> ShadowMap : register(t1);

// 塗装テクスチャ
Texture2D PaintTexture : register(t2);

// マスク
Texture2D Mask : register(t3);

// 深度情報
Texture2D Depth : register(t4);

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
    
    pout *= DiffuseColor;
    
    // ペイントカラー
    float4 paint = PaintTexture.Sample(Sampler, pin.Texcoord);
        
    pout.r = paint.r + pout.r * (1 - paint.a);
    pout.g = paint.g + pout.g * (1 - paint.a);
    pout.b = paint.b + pout.b * (1 - paint.a);
    pout.a = paint.a + pout.a * (1 - paint.a);
    
    float3 lightdire = -normalize(LightDirection);
    float NdotL = dot(lightdire, pin.Normal);
    
    float3 LightColor = float3(1, 1, 1) * lerp(0.8, 1.0, saturate(NdotL));
    //float3 LightColor = float3(1, 1, 1) * lerp(0.5, 0.925f, step(-0.4f, NdotL));
    
    // xyは-1~1の座標、zが光源視点の深度
    float3 lightcoord = pin.LightPosition.xyz / pin.LightPosition.w;
    
    // シャドウマップのuv
    float2 shadowUV;
    shadowUV.x = lightcoord.x * 0.5f + 0.5f;
    shadowUV.y = -lightcoord.y * 0.5f + 0.5f;
    
    // シャドウマップの深度
    float shadowDepth = ShadowMap.Sample(Sampler, shadowUV).r;

    // 調整値
    float bias = 0.001f;
    // 影
    float shadow;
    shadow = lightcoord.z - bias > shadowDepth ? 0.5f : 1.0f;
    
    // UV範囲内チェック
    shadow = step(shadowUV.x, 1.0f) * shadow;
    shadow = step(0.0f, shadowUV.x) * shadow;
    shadow = step(shadowUV.y, 1.0f) * shadow;
    shadow = step(0.0f, shadowUV.y) * shadow;
    
    pout.xyz *= shadow;
    
    // マスクUV
    float2 maskUV = pin.Position.xy / MaskSize;
    
    // 深度
    float maskDepth = Depth.Sample(Sampler, maskUV);
    float4 mask = Mask.Sample(Sampler, maskUV);
    
    // 1ならマスクをかける
    float depthCheck = 1 - step(maskDepth, pin.Position.z);
    float maskCheck = step(1e-8f, mask.a);
    
    float isMask = maskCheck * depthCheck;
    pout = lerp(pout, float4(0.5, 0.5, 0.5, 1.0f), isMask);
    
    return pout;
}