struct PS_INPUT
{
    float3 LocalPosition : LOCALPOSITON;
    float4 Color : COLOR0;
    float Thickness : THICKNESS;
    float Fade : FADE;
    int EntityID : ENTITYID;
    
};


PS_INPUT SimplePixelShader(PS_INPUT input) : SV_TARGET
{
    PS_INPUT Output;
    
    float Distance = 1.0f - length(input.LocalPosition);
    float Circle = smoothstep(0.0f, input.Fade, Distance);
    Circle *= smoothstep(input.Thickness + input.Fade, input.Thickness, Distance);
    
    if (Circle == 0.0f)
    {
        discard;
    }
    
    Output.Color = input.Color;
    Output.Color.w *= Circle;
    
    Output.EntityID = input.EntityID;
    
	return Output;
}