
Texture2D PaintTexture : register(t0);

struct CSInput
{
    uint pixelCount;
};

cbuffer Colors : register(b0)
{
    float4 gameColor[8];
};

float tolerance = 0.01f;

RWStructuredBuffer<CSInput> outPutPaintArea : register(u0);

groupshared uint s_count[8];

[numthreads(8, 8, 1)]
void main(uint3 DTid : SV_DispatchThreadID, uint gi : SV_GroupIndex)
{
    int resetIndex = min(gi, 7);
    s_count[resetIndex] = 0;
    
    GroupMemoryBarrierWithGroupSync();
    
    // 色の判定 (最後の要素は使わない)
    int id = 0;
    float4 color = PaintTexture.Load(int3(DTid.xy, 0));
    for (int i = 0; i < 7; i++)
    {
        float dis = distance(gameColor[i], color);
        int succeces = step(dis, tolerance);
        id = i * succeces + id * (1 - succeces);
    }
    InterlockedAdd(s_count[id], 1);
    
    GroupMemoryBarrierWithGroupSync();

    // ピクセル数の合算
    int resultIndex = min(gi, 7);
    InterlockedAdd(outPutPaintArea[resultIndex].pixelCount, s_count[resultIndex]);
}