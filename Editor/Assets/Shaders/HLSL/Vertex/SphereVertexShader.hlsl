cbuffer WVPBuffer : register(b0)
{
    matrix vWVPMatrix;
}

cbuffer NormalMat : register(b1)
{
    matrix vNormalMatrix;
}

struct VS_INPUT
{
    float3 vPos : POSITION;
    float3 vNormal : NORMAL;
    float2 vTexCoords : TEXCOORDS;
    float4 vColor : COLOR;
    float vTexID : TexID;
    int vEntityID : ENTITYID;
    
};

struct VS_OUTPUT
{
    float3 WorldPosition : WorldPos;
    float3 Normal : NORMAL0;
    float4 Color : COLOR0;
    float TexID : TEXID;
    float2 TexCoords : TEXCOORD0;
    int EntityID : ENTITYID;
    float3 Position : SV_Position;
};

VS_INPUT SimpleVertexShader(VS_INPUT Input) : SV_Position
{
    VS_OUTPUT PixelInput;
    float3x3 TransformedNormMat = transpose(vNormalMatrix);
    PixelInput.WorldPosition = mul(vNormalMatrix,float4(Input.vPos, 1.f));
    PixelInput.Normal = mul(TransformedNormMat, Input.vNormal);
    PixelInput.Color = Input.vColor;
    PixelInput.TexID = Input.vTexID;
    PixelInput.TexCoords = Input.vTexCoords;
    PixelInput.EntityID = Input.vEntityID;
    
    return Input;
}