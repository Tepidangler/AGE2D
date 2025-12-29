cbuffer WVPBuffer : register(b0)
{
    matrix vWVPMatrix;
}

struct VS_INPUT
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
    float2 vTexCoord : TEXCOORD;
    int vEntityID : ENTITYID;
    
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR0;
    float2 TexCoords : TEXCOORD0;
    int EntityID : ENTITYID;
};

VS_OUTPUT SimpleVertexShader(VS_INPUT Input)
{
    VS_OUTPUT Result;
    Result.Position = mul(vWVPMatrix, float4(Input.vPos, 1.0f));
    Result.Color = Input.vColor;
    Result.EntityID = Input.vEntityID;
    
	return Result;
}