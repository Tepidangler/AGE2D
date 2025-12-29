Texture2D Image;
float2 TexCoords;
SamplerState SampleState0;

bool horizontal;
float weight[5] = { 0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216 };

struct PS_INPUT
{
    float4 Color : COLOR0;
    float2 UV : TEXCOORD0;
    float TexID : TEXID;
};

float4 Blur() //Gaussian blur
{
    float4 FragColor;
    uint w;
    uint h;
    uint l;
    Image.GetDimensions(0, w, h, l);
    
    float2 tex_offset = 1.0 / uint2(w, h);
    
    float3 result = Image.Sample(SampleState0, TexCoords).rgb * weight[0];
    
    if(horizontal)
    {
        for (int i = 1; i < 5; ++i)
        {
            result += Image.Sample(SampleState0, TexCoords + float2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += Image.Sample(SampleState0, TexCoords - float2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
        

    }
    else
    {
        for (int i = 1; i < 5; ++i)
        {
            result += Image.Sample(SampleState0, TexCoords + float2(0.0,tex_offset.y * i)).rgb * weight[i];
            result += Image.Sample(SampleState0, TexCoords - float2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    FragColor = float4(result, 1.0);
    return FragColor;
}

float Exposure;

float4 Bloom(float4 Blur)
{
    const float gamma = 2.2;
    float3 hdrColor = Image.Sample(SampleState0, TexCoords).rgb;
    float3 bloomColor = Image.Sample(SampleState0, TexCoords).rgb;
    hdrColor += bloomColor;
    
    float3 result = float3(1.0) - exp(-hdrColor * Exposure);
    
    result = pow(result, float3(1.0 / gamma));
    
    return float4(result, 1.0);

}

PS_INPUT main() : SV_Target
{
    PS_INPUT output;
    
    output.Color = Bloom(Blur());
    
    return output;
    
}