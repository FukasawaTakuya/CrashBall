
struct VSInput
{
    float3 Position : POSITION;
    float3 Normal   : NORMAL;
    float2 Texcoord : TEXCOORD;
};

struct VSOutput
{
    float4 Position     : SV_Position;
    float3 LightColor   : LIGHTCOLOR;
    float2 Texcoord     : TEXCOORD;
};

struct PSInput
{
    float4 Position     : SV_Position;
    float3 LightColor   : LIGHTCOLOR;
    float2 Texcoord     : TEXCOORD;
};