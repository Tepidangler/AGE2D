struct PS_INPUT
{
    float4 Color : COLOR0;
    float2 TexCoords : TEXCOORD0;
    int EntityID : ENTITYID;
};

SamplerState Sampler0 : register(s0);
Texture2D FontAtlas : register(t0);


float ScreenPXRange(PS_INPUT Input)
{
    uint miplevels;
    uint width;
    uint height;
    
    FontAtlas.GetDimensions(0, width, height, miplevels);
    const float PxRange = 2.0;
    float2 UnitRange = float2(PxRange, PxRange) / float2(width, height);
    float2 ScreenTexSize = float2(1.0f, 1.0f) / fwidth(Input.TexCoords);
    
    return max(0.5f * dot(UnitRange, ScreenTexSize), 1.0f);

}

float Median(float R, float G, float B)
{
    return max(min(R, G), min(max(R, G), B));

}

PS_INPUT SimplePixelShader(PS_INPUT input) : SV_TARGET
{
    PS_INPUT output;
    
    float4 TexColor = input.Color * FontAtlas.Sample(Sampler0, input.TexCoords);
    
    float3 MSD = FontAtlas.Sample(Sampler0, input.TexCoords).rgb;
    
    float SD = Median(MSD.r, MSD.g, MSD.b);
    float ScreenPXDistance = ScreenPXRange(input) * (SD - 0.5);
    float Opacity = clamp(ScreenPXDistance + 0.5f, 0.0f, 1.0f);
    if(Opacity == 0.0f)
    {
        discard;
    }
    float4 BGColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
    output.Color = lerp(BGColor, input.Color, Opacity);
    
    output.EntityID = input.EntityID;
    
	return output;
}