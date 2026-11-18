
Texture2D<float4> Texture : register(t0);
sampler TextureSampler : register(s0);

RWTexture2D<uint> TimeTexture : register(u0);

struct PSInput
{
    float4 color : COLOR0;
    float2 texCoord : TEXCOORD0;
};

struct PSOutPut
{
    float4 color;
    uint2 stamp;
};

cbuffer TimeTexInfo : register(b2)
{
    uint id;
    uint time;
}

PSOutPut main(PSInput pin) : SV_Target0
{
    PSOutPut pout;
    pout.color = Texture.Sample(TextureSampler, pin.texCoord) * pin.color;
    if (pout.color.a <= 0.1f)
    {
        discard;
    }
        
    pout.stamp.y = time;
    pout.stamp.x = id;
    return pout;
}
