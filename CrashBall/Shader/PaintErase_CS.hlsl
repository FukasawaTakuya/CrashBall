#include "CalcPaint.hlsli"

RWTexture2D<float4> PaintTexture : register(u0);    // ペイントテクスチャ

RWTexture2D<uint2> PaintTimeTex : register(u1);     // ペイント時間テクスチャ

//RWStructuredBuffer<uint> partialCount : register(u2);   // 一部消去ビンカウント用

// 消去用定数バッファ
cbuffer EraseInfo : register(b1)
{
    int EraseBin;   // 消去処理
    int PartialNum; // 一部消去ピクセル数
}

groupshared uint partialCount;

[numthreads(32, 32, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{   
    // 初期化
    partialCount = 0;
    
    AllMemoryBarrierWithGroupSync();
    
    uint2 stamp = PaintTimeTex.Load(int3(DTid.xy, 0));
    
    if(stamp.y > 0)
    {
        uint bin = CalcBin(stamp);
        bool erase = false;
        
        // ビンが消去ビンより古ければ消去
        if (bin > EraseBin && EraseBin > stamp.x * BIN_NUM)
        {
            erase = true;
        }
        // ビンが消去ビンと同じなら一部消去
        else if (bin == EraseBin)
        {
            uint old;
            InterlockedAdd(partialCount, 1, old);
            erase = (old < PartialNum);
        }
        
        // 消去
        if(erase)
        {
            PaintTexture[DTid.xy] = float4(0, 0, 0, 0);
            PaintTimeTex[DTid.xy] = uint2(0, 0);
        }
    }
}