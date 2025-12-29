cbuffer WVPBuffer : register(b0)
{
    matrix vWVPMatrix;
}

struct VS_INPUT
{
    float3 vWPos : WORLDPOSITION;
    float3 vLPos : LOCALPOSITION;
    float4 vColor : COLOR;
    float vThickness : THICKNESS;
    float vFade : FADE;
    int vEntityID : ENTITYID;
    
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 LocalPosition : LOCALPOSITON;
    float4 Color : COLOR0;
    float Thickness : THICKNESS;
    float Fade : FADE;
    int EntityID : ENTITYID;
    
};


VS_OUTPUT SimpleVertexShader(VS_INPUT Input)
{
    VS_OUTPUT Result;
    Result.LocalPosition = Input.vLPos;
    Result.Color = Input.vColor;
    Result.Thickness = Input.vThickness;
    Result.Fade = Input.vFade;
    
    Result.EntityID = Input.vEntityID;
    
    Result.Pos = mul(vWVPMatrix, float4(Input.vWPos, 1.f));
    
	return Result;
}