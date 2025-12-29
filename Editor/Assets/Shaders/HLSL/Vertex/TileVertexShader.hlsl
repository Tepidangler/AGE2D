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
    float4 Color : COLOR0;
    float2 UV : TEXCOORD0;
    float TexID : TEXID;
    float4 Position : SV_POSITION;
    int EntityID : ENTITYID;
};

VS_OUTPUT SimpleVertexShader(VS_INPUT Input)
{
    VS_OUTPUT Result;
    
    Result.Position = mul(vWVPMatrix, float4(Input.vPos, 1.f));
    Result.UV = Input.vUV;
    Result.TexID = Input.vTexID;
    Result.Color = Input.vColor;
    
    return Result;
}