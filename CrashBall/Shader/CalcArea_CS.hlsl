
// 許容距離
static const float toleranceSqrt = 0.01f * 0.01f;
// カウンター数
static const int countSize = 8;

// 塗装テクスチャ
Texture2D PaintTexture : register(t0);

// 判定用の色
cbuffer Colors : register(b0)
{
    float4 gameColor[countSize];
};

struct CSOutput
{
    uint pixelCount;
};

// 合計計算結果格納先
RWStructuredBuffer<CSOutput> outPutPaintArea : register(u0);

// 計算結果格納先
groupshared uint s_count[countSize];

[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID, uint gi : SV_GroupIndex)
{
    if (gi < countSize)
        s_count[gi] = 0;
    
    GroupMemoryBarrierWithGroupSync();
    
    // 色の判定
    int id = countSize;
    float4 color = PaintTexture.Load(int3(DTid.xy, 0));
    [unroll]
    for (int i = 0; i < countSize; i++)
    {
        float delta = gameColor[i] - color;
        int ans = step(dot(delta, delta), toleranceSqrt);
        id = i * ans + id * (1 - ans);
    }
    
    if (id < countSize)
        InterlockedAdd(s_count[id], 1);
    
    GroupMemoryBarrierWithGroupSync();

    // ピクセル数の合算
    if (gi < countSize)
        InterlockedAdd(outPutPaintArea[gi].pixelCount, s_count[gi]);
}