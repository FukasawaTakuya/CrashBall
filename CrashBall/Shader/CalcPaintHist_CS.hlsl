#include "CalcPaint.hlsli"

Texture2D<uint2> PaintTimeTex : register(t0); // ペイント時間テクスチャ

RWStructuredBuffer<uint> Hist : register(u0); // ヒストグラム

RWTexture2D<uint2> PaintTimeTexOut : register(u1); // ペイント時間テクスチャコピー用

// 計算結果格納先
groupshared uint s_Histcount[BIN_NUM * TEAM_NUM];

[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID, uint gi : SV_GroupIndex)
{
    // ヒストグラム初期化
    if (gi < BIN_NUM * TEAM_NUM)
        s_Histcount[gi] = 0;
    
    GroupMemoryBarrierWithGroupSync();
    
    // タイムスタンプを取得
    uint2 stamp = PaintTimeTex.Load(int3(DTid.xy, 0));
    if(stamp.y > 0 && nowFrame > stamp.y)
    {
        uint age = AgeBin(stamp.y);
       
        InterlockedAdd(s_Histcount[age + (BIN_NUM) * stamp.x], 1);
    }

    GroupMemoryBarrierWithGroupSync();
    
    if (gi < BIN_NUM * TEAM_NUM)
        InterlockedAdd(Hist[gi], s_Histcount[gi]);
    
    // ペイント時間テクスチャをコピー
    PaintTimeTexOut[DTid.xy] = PaintTimeTex[DTid.xy];

}