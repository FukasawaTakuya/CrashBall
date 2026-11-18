
Texture2D<uint2> PaintTimeTex : register(t0);

RWStructuredBuffer<uint> Hist : register(u0);

static uint binNum = 16;

cbuffer HistInfo : register(b0)
{
    uint nowFrame;  // 現フレーム
    uint binWidth;  // ビンの幅
}

// 計算結果格納先
groupshared uint s_Histcount[128];


[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID, uint gi : SV_GroupIndex)
{
    if (gi < 128)
        s_Histcount[gi] = 0;
    
    GroupMemoryBarrierWithGroupSync();
    
    uint2 stamp = PaintTimeTex.Load(DTid);
    uint age = min((nowFrame - stamp.y) / binWidth, binNum - 1);
    
    GroupMemoryBarrierWithGroupSync();
   
    if (gi < 128)
        InterlockedAdd(s_Histcount[age + (binNum - 1) * stamp.x], step(1, stamp.y));
    
    if (gi < binNum * 8)
        InterlockedAdd(Hist[gi], s_Histcount[gi]);
}