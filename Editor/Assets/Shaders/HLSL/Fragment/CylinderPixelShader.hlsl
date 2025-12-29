struct PS_INPUT
{
    float4 Position : POSITION;
    float2 Height : HEIGHT;
    float2 TexCoords : TEXCOORD0;
    float4 Color : COLOR0;
    float TexID : TEXID;
    float TilingFactor : TILINGFACTOR;
    float Radius : RADIUS;
    int EntityID : ENTITYID;
    
};

PS_INPUT SimplePixelShader(PS_INPUT input) : SV_TARGET
{
    PS_INPUT Output;
    
    float Distance = abs(float2(length(input.Position.xz), input.Position.y)) - input.Height;
	
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}