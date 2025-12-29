cbuffer WVPBuffer : register(b0)
{
    matrix vWVPMatrix;
}

struct VS_INPUT
{
    float3 vPosition : POSITION;
    float2 vTexCoords : TEXCOORD;
    float2 vHeight : HEIGHT;
    float4 vColor : COLOR;
    float vTexID : TEXID;
    float vTilingFactor : TILINGFACTOR;
    float vRadius : RADIUS;
    
    
    int vEntityID : ENTITYID;
    
};

struct VS_OUTPUT
{
    float4 Position : SV_Position;
    float3 LocalPosition : POSITION;
    float2 Height : HEIGHT;
    float2 TexCoords : TEXCOORD0;
    float4 Color : COLOR0;
    float TexID : TEXID;
    float TilingFactor : TILINGFACTOR;
    float Radius : RADIUS;
    
    int EntityID : ENTITYID;
};

VS_OUTPUT SimpleVertexShader(VS_INPUT input)
{
    VS_OUTPUT Result;
    
    Result.Position = mul(vWVPMatrix, float4(input.vPosition, 1.f));
    Result.TexCoords = input.vTexCoords;
    Result.TexID = input.vTexID;
    Result.Color = input.vColor;
    Result.Height = input.vHeight;
    Result.Radius = input.vRadius;
    Result.TilingFactor = input.vTilingFactor;
    Result.LocalPosition = input.vPosition;
    
    
	return Result;
}