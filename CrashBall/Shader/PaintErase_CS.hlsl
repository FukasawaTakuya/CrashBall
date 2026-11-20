#include "CalcPaint.hlsli"

RWTexture2D<float4> PaintTexture : register(u0);

RWTexture2D<uint2> PaintTimeTex : register(u1);

RWStructuredBuffer<uint> partialCount : register(u2);

cbuffer EraseInfo : register(b1)
{
    int EraseNum;
    int EraseBin;
    int PartialNum;
}

[numthreads(32, 32, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{   
    partialCount[0] = 0;
    
    AllMemoryBarrierWithGroupSync();
    
    uint2 stamp = PaintTimeTex.Load(int3(DTid.xy, 0));
    
    if(stamp.y > 0)
    {
        uint age = AgeBin(stamp.y);
        uint bin = age + BIN_NUM * stamp.x;
        bool erase = false;
        
        if (bin > EraseBin && EraseBin > stamp.x * BIN_NUM)
        {
            erase = true;
        }
        else if (bin == EraseBin)
        {
            uint old;
            InterlockedAdd(partialCount[0], 1, old);
            erase = (old < PartialNum);
        }
        
        if(erase)
        {
            PaintTexture[DTid.xy] = float4(0, 0, 0, 0);
            PaintTimeTex[DTid.xy] = uint2(0, 0);
        }
    }
}