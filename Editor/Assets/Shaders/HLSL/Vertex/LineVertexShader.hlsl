cbuffer WVPBuffer : register(b0)
{
    matrix vWVPMatrix;
}

struct VS_INPUT
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
    int vEntityID : ENTITYID;
    
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : Color0;
    int EntityID : ENTITYID;
};

VS_OUTPUT SimpleVertexShader(VS_INPUT input)
{
    VS_OUTPUT Result;
    
    Result.Color = input.vColor;
    Result.EntityID = input.vEntityID;
    
    Result.Pos = mul(vWVPMatrix, float4(input.vPos, 1.0));
    
    
	return Result;
}