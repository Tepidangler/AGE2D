
#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexID;
layout(location = 4) in int a_EntityID;


layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
};


layout (location = 0) out VertexOutput Output;
layout(location = 2) out flat float v_TexID;
layout (location = 3) out flat int v_EntityID;

void main()
{
	Output.Color = a_Color;
	Output.TexCoord = a_TexCoord;
	v_TexID = a_TexID;
	v_EntityID = a_EntityID;

	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
};

layout (location = 0) in VertexOutput Input;
layout(location = 2) in flat float v_TexID;
layout (location = 3) in flat int v_EntityID;

layout (binding = 0) uniform sampler2D u_FontAtlas[32];

float ScreenPXRange()
{
	const float PxRange = 2.0;
	vec2 UnitRange = vec2(0.f);
	switch(int(v_TexID))
	{
		case  0: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[ 0],0));break;
		case  1: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[ 1],0));break;
		case  2: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[ 2],0));break;
		case  3: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[ 3],0));break;
		case  4: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[ 4],0));break;
		case  5: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[ 5],0));break;
		case  6: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[ 6],0));break;
		case  7: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[ 7],0));break;
		case  8: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[ 8],0));break;
		case  9: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[ 9],0));break;
		case 10: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[10],0));break;
		case 11: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[11],0));break;
		case 12: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[12],0));break;
		case 13: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[13],0));break;
		case 14: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[14],0));break;
		case 15: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[15],0));break;
		case 16: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[16],0));break;
		case 17: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[17],0));break;
		case 18: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[18],0));break;
		case 19: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[19],0));break;
		case 20: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[20],0));break;
		case 21: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[21],0));break;
		case 22: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[22],0));break;
		case 23: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[23],0));break;
		case 24: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[24],0));break;
		case 25: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[25],0));break;
		case 26: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[26],0));break;
		case 27: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[27],0));break;
		case 28: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[28],0));break;
		case 29: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[29],0));break;
		case 30: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[30],0));break;
		case 31: UnitRange = vec2(PxRange)/vec2(textureSize(u_FontAtlas[31],0));break;
	}
	vec2 ScreenTexSize = vec2(1.0)/fwidth(Input.TexCoord);
	return max(0.5*dot(UnitRange, ScreenTexSize), 1.0);
}

float Median(float R, float G, float B)
{
	return max(min(R,G), min(max(R,G), B));
}


void main()
{
	vec4 TexColor = Input.Color;
	vec3 MSD = vec3(0.f);

	switch(int(v_TexID))
	{
		case  0: TexColor *= texture(u_FontAtlas[ 0], Input.TexCoord); MSD = texture(u_FontAtlas[ 0], Input.TexCoord).rgb;break;
		case  1: TexColor *= texture(u_FontAtlas[ 1], Input.TexCoord); MSD = texture(u_FontAtlas[ 1], Input.TexCoord).rgb;break;
		case  2: TexColor *= texture(u_FontAtlas[ 2], Input.TexCoord); MSD = texture(u_FontAtlas[ 2], Input.TexCoord).rgb;break;
		case  3: TexColor *= texture(u_FontAtlas[ 3], Input.TexCoord); MSD = texture(u_FontAtlas[ 3], Input.TexCoord).rgb;break;
		case  4: TexColor *= texture(u_FontAtlas[ 4], Input.TexCoord); MSD = texture(u_FontAtlas[ 4], Input.TexCoord).rgb;break;
		case  5: TexColor *= texture(u_FontAtlas[ 5], Input.TexCoord); MSD = texture(u_FontAtlas[ 5], Input.TexCoord).rgb;break;
		case  6: TexColor *= texture(u_FontAtlas[ 6], Input.TexCoord); MSD = texture(u_FontAtlas[ 6], Input.TexCoord).rgb;break;
		case  7: TexColor *= texture(u_FontAtlas[ 7], Input.TexCoord); MSD = texture(u_FontAtlas[ 7], Input.TexCoord).rgb;break;
		case  8: TexColor *= texture(u_FontAtlas[ 8], Input.TexCoord); MSD = texture(u_FontAtlas[ 8], Input.TexCoord).rgb;break;
		case  9: TexColor *= texture(u_FontAtlas[ 9], Input.TexCoord); MSD = texture(u_FontAtlas[ 9], Input.TexCoord).rgb;break;
		case 10: TexColor *= texture(u_FontAtlas[10], Input.TexCoord); MSD = texture(u_FontAtlas[10], Input.TexCoord).rgb;break;
		case 11: TexColor *= texture(u_FontAtlas[11], Input.TexCoord); MSD = texture(u_FontAtlas[11], Input.TexCoord).rgb;break;
		case 12: TexColor *= texture(u_FontAtlas[12], Input.TexCoord); MSD = texture(u_FontAtlas[12], Input.TexCoord).rgb;break;
		case 13: TexColor *= texture(u_FontAtlas[13], Input.TexCoord); MSD = texture(u_FontAtlas[13], Input.TexCoord).rgb;break;
		case 14: TexColor *= texture(u_FontAtlas[14], Input.TexCoord); MSD = texture(u_FontAtlas[14], Input.TexCoord).rgb;break;
		case 15: TexColor *= texture(u_FontAtlas[15], Input.TexCoord); MSD = texture(u_FontAtlas[15], Input.TexCoord).rgb;break;
		case 16: TexColor *= texture(u_FontAtlas[16], Input.TexCoord); MSD = texture(u_FontAtlas[16], Input.TexCoord).rgb;break;
		case 17: TexColor *= texture(u_FontAtlas[17], Input.TexCoord); MSD = texture(u_FontAtlas[17], Input.TexCoord).rgb;break;
		case 18: TexColor *= texture(u_FontAtlas[18], Input.TexCoord); MSD = texture(u_FontAtlas[18], Input.TexCoord).rgb;break;
		case 19: TexColor *= texture(u_FontAtlas[19], Input.TexCoord); MSD = texture(u_FontAtlas[19], Input.TexCoord).rgb;break;
		case 20: TexColor *= texture(u_FontAtlas[20], Input.TexCoord); MSD = texture(u_FontAtlas[20], Input.TexCoord).rgb;break;
		case 21: TexColor *= texture(u_FontAtlas[21], Input.TexCoord); MSD = texture(u_FontAtlas[21], Input.TexCoord).rgb;break;
		case 22: TexColor *= texture(u_FontAtlas[22], Input.TexCoord); MSD = texture(u_FontAtlas[22], Input.TexCoord).rgb;break;
		case 23: TexColor *= texture(u_FontAtlas[23], Input.TexCoord); MSD = texture(u_FontAtlas[23], Input.TexCoord).rgb;break;
		case 24: TexColor *= texture(u_FontAtlas[24], Input.TexCoord); MSD = texture(u_FontAtlas[24], Input.TexCoord).rgb;break;
		case 25: TexColor *= texture(u_FontAtlas[25], Input.TexCoord); MSD = texture(u_FontAtlas[25], Input.TexCoord).rgb;break;
		case 26: TexColor *= texture(u_FontAtlas[26], Input.TexCoord); MSD = texture(u_FontAtlas[26], Input.TexCoord).rgb;break;
		case 27: TexColor *= texture(u_FontAtlas[27], Input.TexCoord); MSD = texture(u_FontAtlas[27], Input.TexCoord).rgb;break;
		case 28: TexColor *= texture(u_FontAtlas[28], Input.TexCoord); MSD = texture(u_FontAtlas[28], Input.TexCoord).rgb;break;
		case 29: TexColor *= texture(u_FontAtlas[29], Input.TexCoord); MSD = texture(u_FontAtlas[29], Input.TexCoord).rgb;break;
		case 30: TexColor *= texture(u_FontAtlas[30], Input.TexCoord); MSD = texture(u_FontAtlas[30], Input.TexCoord).rgb;break;
		case 31: TexColor *= texture(u_FontAtlas[31], Input.TexCoord); MSD = texture(u_FontAtlas[31], Input.TexCoord).rgb;break;
	}


	//vec3 MSD = texture(u_FontAtlas, Input.TexCoord).rgb;
	float SD = Median(MSD.r, MSD.g, MSD.b);
	float ScreenPXDistance = ScreenPXRange() *(SD - 0.5);
	float Opacity = clamp(ScreenPXDistance + 0.5, 0.0, 1.0);
		if(Opacity == 0.0)
		{
			discard;
		}
		vec4 BGColor = vec4(0.0);
	o_Color = mix(BGColor, Input.Color, Opacity);
		if(o_Color.a == 0.0)
		{
			discard;
		}


		o_EntityID = v_EntityID;
}