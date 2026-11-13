
Texture2D PaintTexture : register(t0);

struct CSOutput
{
    uint pixelCount;
};

cbuffer Colors : register(b0)
{
    float4 gameColor[8];
};

static const float tolerance = 0.1f;

RWStructuredBuffer<CSOutput> outPutPaintArea : register(u0);

groupshared uint s_count[8];

[numthreads(8, 8, 1)]
void main(uint3 DTid : SV_DispatchThreadID, uint gi : SV_GroupIndex)
{
    int resetIndex = min(gi, 7);
    s_count[resetIndex] = 0;
    
    GroupMemoryBarrierWithGroupSync();
    
    // 色の判定 (最後の要素は使わない)
    int id = 7;
    float4 color = PaintTexture.Load(int3(DTid.xy, 0));
    for (int i = 0; i < 7; i++)
    {
        float dis = distance(gameColor[i], color);
        int ans = step(abs(dis), tolerance);
        id = i * ans + id * (1 - ans);
    }
    
    InterlockedAdd(s_count[id], 1);
    
    GroupMemoryBarrierWithGroupSync();

    // ピクセル数の合算
    int resultIndex = min(gi, 7);
    InterlockedAdd(outPutPaintArea[resultIndex].pixelCount, s_count[resultIndex]);
}