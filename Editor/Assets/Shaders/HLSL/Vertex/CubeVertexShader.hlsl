 cbuffer WVPBuffer : register(b0)
{
    matrix vWVPMatrix;
}


struct VS_INPUT
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
    float4 vColor : COLOR;
    float vTexID : TEXID;
    float vTilingFactor : TILINGFACTOR;
    int vEntityID : ENTITYID;
};

struct VS_OUTPUT
{
    float2 o_UV : TEXCOORD0;
    float4 o_Color : COLOR0;
    float o_TexID : TEXID;
    int o_EntityID : ENTITYID;
    float4 Position : SV_POSITION;  
};



VS_OUTPUT SimpleVertexShader(VS_INPUT input)
{
    VS_OUTPUT Result;

    Result.Position = mul(vWVPMatrix, float4(input.vPos, 1.f));
    Result.o_UV = input.vUV;
    Result.o_TexID = input.vTexID;
    Result.o_Color = input.vColor;
    Result.o_EntityID = input.vEntityID;

    return Result;
}