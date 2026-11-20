#include "CalcPaint.hlsli"

// 塗装テクスチャ
Texture2D PaintTexture : register(t0);

// 判定用の色
cbuffer Colors : register(b0)
{
    float4 gameColor[TEAM_NUM];
};

// 出力
struct CSOutput
{
    uint pixelCount;
};

// 合計計算結果格納先
RWStructuredBuffer<CSOutput> outPutPaintArea : register(u0);

// 計算結果格納先
groupshared uint s_count[TEAM_NUM];

[numthreads(32, 32, 1)]
void main(uint3 DTid : SV_DispatchThreadID, uint gi : SV_GroupIndex)
{
    if (gi < TEAM_NUM)
        s_count[gi] = 0;
    
    GroupMemoryBarrierWithGroupSync();
    
    // 色の判定
    int id = TEAM_NUM;
    float4 color = PaintTexture.Load(int3(DTid.xy, 0));
    [unroll]
    for (int i = 0; i < TEAM_NUM; i++)
    {
        float delta = gameColor[i] - color;
        int ans = step(dot(delta, delta), toleranceSqrt);
        id = i * ans + id * (1 - ans);
    }
    
    if (id < TEAM_NUM)
        InterlockedAdd(s_count[id], 1);
    
    GroupMemoryBarrierWithGroupSync();

    // ピクセル数の合算
    if (gi < TEAM_NUM)
        InterlockedAdd(outPutPaintArea[gi].pixelCount, s_count[gi]);
}