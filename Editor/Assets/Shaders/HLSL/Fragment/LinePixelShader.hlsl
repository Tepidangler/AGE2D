struct PS_INPUT
{

    float4 Color : Color0;
    int EntityID : ENTITYID;
};


PS_INPUT SimplePixelShader(PS_INPUT input) : SV_TARGET
{
    PS_INPUT Output;
    
    Output.Color = input.Color;
    Output.EntityID = input.EntityID;
    
	return Output;
}