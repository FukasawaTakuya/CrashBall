
static const float toleranceSqrt = 0.001f * 0.001f;
static const int countSize = 8;

Texture2D PaintTexture : register(t0);

cbuffer Colors : register(b0)
{
    float4 gameColor[countSize];
};


struct CSOutput
{
    uint pixelCount;
};

RWStructuredBuffer<CSOutput> outPutPaintArea : register(u0);
RWTexture2D<float4> RWPaintTexture : register(u1);

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
    
    RWPaintTexture[DTid.xy] = float4(1, 0, 0, 1);

}