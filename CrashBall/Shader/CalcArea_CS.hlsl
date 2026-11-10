
Texture2D PaintTexture : register(t0);

SamplerState Sampler : register(s0);

RWStructuredBuffer<uint> outPutPaintArea : register(u0);

[numthreads(8, 8, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    outPutPaintArea[DTid.x] = 0;
}