struct PS_INPUT
{
    float2 UV : TEXCOORD0;
    float4 Color : COLOR0;
    float TexID : TEXID;
    int EntityID : ENTITYID;

};

SamplerState Sampler0 : register(s0);
Texture2D Texture[128] : register(t0);

PS_INPUT SimplePixelShader(PS_INPUT input) : SV_Target

{
    PS_INPUT output;
    int ID = input.TexID;
    output.EntityID = input.EntityID;
    switch (ID)
    {
        
        case 0:
            output.Color = input.Color * Texture[0].Sample(Sampler0, input.UV);
            break;
        case 1:
            output.Color = input.Color * Texture[1].Sample(Sampler0, input.UV);
            break;
        case 2:
            output.Color = input.Color * Texture[2].Sample(Sampler0, input.UV);
            break;
        case 3:
            output.Color = input.Color * Texture[3].Sample(Sampler0, input.UV);
            break;
        case 4:
            output.Color = input.Color * Texture[4].Sample(Sampler0, input.UV);
            break;
        case 5:
            output.Color = input.Color * Texture[5].Sample(Sampler0, input.UV);
            break;
        case 6:
            output.Color = input.Color * Texture[6].Sample(Sampler0, input.UV);
            break;
        case 7:
            output.Color = input.Color * Texture[7].Sample(Sampler0, input.UV);
            break;
        case 8:
            output.Color = input.Color * Texture[8].Sample(Sampler0, input.UV);
            break;
        case 9:
            output.Color = input.Color * Texture[9].Sample(Sampler0, input.UV);
            break;
        case 10:
            output.Color = input.Color * Texture[10].Sample(Sampler0, input.UV);
            break;
        case 11:
            output.Color = input.Color * Texture[11].Sample(Sampler0, input.UV);
            break;
        case 12:
            output.Color = input.Color * Texture[12].Sample(Sampler0, input.UV);
            break;
        case 13:
            output.Color = input.Color * Texture[13].Sample(Sampler0, input.UV);
            break;
        case 14:
            output.Color = input.Color * Texture[14].Sample(Sampler0, input.UV);
            break;
        case 15:
            output.Color = input.Color * Texture[15].Sample(Sampler0, input.UV);
            break;
        case 16:
            output.Color = input.Color * Texture[16].Sample(Sampler0, input.UV);
            break;
        case 17:
            output.Color = input.Color * Texture[17].Sample(Sampler0, input.UV);
            break;
        case 18:
            output.Color = input.Color * Texture[18].Sample(Sampler0, input.UV);
            break;
        case 19:
            output.Color = input.Color * Texture[19].Sample(Sampler0, input.UV);
            break;
        case 20:
            output.Color = input.Color * Texture[20].Sample(Sampler0, input.UV);
            break;
        case 21:
            output.Color = input.Color * Texture[21].Sample(Sampler0, input.UV);
            break;
        case 22:
            output.Color = input.Color * Texture[22].Sample(Sampler0, input.UV);
            break;
        case 23:
            output.Color = input.Color * Texture[23].Sample(Sampler0, input.UV);
            break;
        case 24:
            output.Color = input.Color * Texture[24].Sample(Sampler0, input.UV);
            break;
        case 25:
            output.Color = input.Color * Texture[25].Sample(Sampler0, input.UV);
            break;
        case 26:
            output.Color = input.Color * Texture[26].Sample(Sampler0, input.UV);
            break;
        case 27:
            output.Color = input.Color * Texture[27].Sample(Sampler0, input.UV);
            break;
        case 28:
            output.Color = input.Color * Texture[28].Sample(Sampler0, input.UV);
            break;
        case 29:
            output.Color = input.Color * Texture[29].Sample(Sampler0, input.UV);
            break;
        case 30:
            output.Color = input.Color * Texture[30].Sample(Sampler0, input.UV);
            break;
        case 31:
            output.Color = input.Color * Texture[31].Sample(Sampler0, input.UV);
            break;
        case 32:
            output.Color = input.Color * Texture[32].Sample(Sampler0, input.UV);
            break;
        case 33:
            output.Color = input.Color * Texture[33].Sample(Sampler0, input.UV);
            break;
        case 34:
            output.Color = input.Color * Texture[34].Sample(Sampler0, input.UV);
            break;
        case 35:
            output.Color = input.Color * Texture[35].Sample(Sampler0, input.UV);
            break;
        case 36:
            output.Color = input.Color * Texture[36].Sample(Sampler0, input.UV);
            break;
        case 37:
            output.Color = input.Color * Texture[37].Sample(Sampler0, input.UV);
            break;
        case 38:
            output.Color = input.Color * Texture[38].Sample(Sampler0, input.UV);
            break;
        case 39:
            output.Color = input.Color * Texture[39].Sample(Sampler0, input.UV);
            break;
        case 40:
            output.Color = input.Color * Texture[40].Sample(Sampler0, input.UV);
            break;
        case 41:
            output.Color = input.Color * Texture[41].Sample(Sampler0, input.UV);
            break;
        case 42:
            output.Color = input.Color * Texture[42].Sample(Sampler0, input.UV);
            break;
        case 43:
            output.Color = input.Color * Texture[43].Sample(Sampler0, input.UV);
            break;
        case 44:
            output.Color = input.Color * Texture[44].Sample(Sampler0, input.UV);
            break;
        case 45:
            output.Color = input.Color * Texture[45].Sample(Sampler0, input.UV);
            break;
        case 46:
            output.Color = input.Color * Texture[46].Sample(Sampler0, input.UV);
            break;
        case 47:
            output.Color = input.Color * Texture[47].Sample(Sampler0, input.UV);
            break;
        case 48:
            output.Color = input.Color * Texture[48].Sample(Sampler0, input.UV);
            break;
        case 49:
            output.Color = input.Color * Texture[49].Sample(Sampler0, input.UV);
            break;
        case 50:
            output.Color = input.Color * Texture[50].Sample(Sampler0, input.UV);
            break;
        case 51:
            output.Color = input.Color * Texture[51].Sample(Sampler0, input.UV);
            break;
        case 52:
            output.Color = input.Color * Texture[52].Sample(Sampler0, input.UV);
            break;
        case 53:
            output.Color = input.Color * Texture[53].Sample(Sampler0, input.UV);
            break;
        case 54:
            output.Color = input.Color * Texture[54].Sample(Sampler0, input.UV);
            break;
        case 55:
            output.Color = input.Color * Texture[55].Sample(Sampler0, input.UV);
            break;
        case 56:
            output.Color = input.Color * Texture[56].Sample(Sampler0, input.UV);
            break;
        case 57:
            output.Color = input.Color * Texture[57].Sample(Sampler0, input.UV);
            break;
        case 58:
            output.Color = input.Color * Texture[58].Sample(Sampler0, input.UV);
            break;
        case 59:
            output.Color = input.Color * Texture[59].Sample(Sampler0, input.UV);
            break;
        case 60:
            output.Color = input.Color * Texture[60].Sample(Sampler0, input.UV);
            break;
        case 61:
            output.Color = input.Color * Texture[61].Sample(Sampler0, input.UV);
            break;
        case 62:
            output.Color = input.Color * Texture[62].Sample(Sampler0, input.UV);
            break;
        case 63:
            output.Color = input.Color * Texture[63].Sample(Sampler0, input.UV);
            break;
        case 64:
            output.Color = input.Color * Texture[64].Sample(Sampler0, input.UV);
            break;
        case 65:
            output.Color = input.Color * Texture[65].Sample(Sampler0, input.UV);
            break;
        case 66:
            output.Color = input.Color * Texture[66].Sample(Sampler0, input.UV);
            break;
        case 67:
            output.Color = input.Color * Texture[67].Sample(Sampler0, input.UV);
            break;
        case 68:
            output.Color = input.Color * Texture[68].Sample(Sampler0, input.UV);
            break;
        case 69:
            output.Color = input.Color * Texture[69].Sample(Sampler0, input.UV);
            break;
        case 70:
            output.Color = input.Color * Texture[70].Sample(Sampler0, input.UV);
            break;
        case 71:
            output.Color = input.Color * Texture[71].Sample(Sampler0, input.UV);
            break;
        case 72:
            output.Color = input.Color * Texture[72].Sample(Sampler0, input.UV);
            break;
        case 73:
            output.Color = input.Color * Texture[73].Sample(Sampler0, input.UV);
            break;
        case 74:
            output.Color = input.Color * Texture[74].Sample(Sampler0, input.UV);
            break;
        case 75:
            output.Color = input.Color * Texture[75].Sample(Sampler0, input.UV);
            break;
        case 76:
            output.Color = input.Color * Texture[76].Sample(Sampler0, input.UV);
            break;
        case 77:
            output.Color = input.Color * Texture[77].Sample(Sampler0, input.UV);
            break;
        case 78:
            output.Color = input.Color * Texture[78].Sample(Sampler0, input.UV);
            break;
        case 79:
            output.Color = input.Color * Texture[79].Sample(Sampler0, input.UV);
            break;
        case 80:
            output.Color = input.Color * Texture[80].Sample(Sampler0, input.UV);
            break;
        case 81:
            output.Color = input.Color * Texture[81].Sample(Sampler0, input.UV);
            break;
        case 82:
            output.Color = input.Color * Texture[82].Sample(Sampler0, input.UV);
            break;
        case 83:
            output.Color = input.Color * Texture[83].Sample(Sampler0, input.UV);
            break;
        case 84:
            output.Color = input.Color * Texture[84].Sample(Sampler0, input.UV);
            break;
        case 85:
            output.Color = input.Color * Texture[85].Sample(Sampler0, input.UV);
            break;
        case 86:
            output.Color = input.Color * Texture[86].Sample(Sampler0, input.UV);
            break;
        case 87:
            output.Color = input.Color * Texture[87].Sample(Sampler0, input.UV);
            break;
        case 88:
            output.Color = input.Color * Texture[88].Sample(Sampler0, input.UV);
            break;
        case 89:
            output.Color = input.Color * Texture[89].Sample(Sampler0, input.UV);
            break;
        case 90:
            output.Color = input.Color * Texture[90].Sample(Sampler0, input.UV);
            break;
        case 91:
            output.Color = input.Color * Texture[91].Sample(Sampler0, input.UV);
            break;
        case 92:
            output.Color = input.Color * Texture[92].Sample(Sampler0, input.UV);
            break;
        case 93:
            output.Color = input.Color * Texture[93].Sample(Sampler0, input.UV);
            break;
        case 94:
            output.Color = input.Color * Texture[94].Sample(Sampler0, input.UV);
            break;
        case 95:
            output.Color = input.Color * Texture[95].Sample(Sampler0, input.UV);
            break;
        case 96:
            output.Color = input.Color * Texture[96].Sample(Sampler0, input.UV);
            break;
        case 97:
            output.Color = input.Color * Texture[97].Sample(Sampler0, input.UV);
            break;
        case 98:
            output.Color = input.Color * Texture[98].Sample(Sampler0, input.UV);
            break;
        case 99:
            output.Color = input.Color * Texture[99].Sample(Sampler0, input.UV);
            break;
        case 100:
            output.Color = input.Color * Texture[100].Sample(Sampler0, input.UV);
            break;
        case 101:
            output.Color = input.Color * Texture[101].Sample(Sampler0, input.UV);
            break;
        case 102:
            output.Color = input.Color * Texture[102].Sample(Sampler0, input.UV);
            break;
        case 103:
            output.Color = input.Color * Texture[103].Sample(Sampler0, input.UV);
            break;
        case 104:
            output.Color = input.Color * Texture[104].Sample(Sampler0, input.UV);
            break;
        case 105:
            output.Color = input.Color * Texture[105].Sample(Sampler0, input.UV);
            break;
        case 106:
            output.Color = input.Color * Texture[106].Sample(Sampler0, input.UV);
            break;
        case 107:
            output.Color = input.Color * Texture[107].Sample(Sampler0, input.UV);
            break;
        case 108:
            output.Color = input.Color * Texture[108].Sample(Sampler0, input.UV);
            break;
        case 109:
            output.Color = input.Color * Texture[109].Sample(Sampler0, input.UV);
            break;
        case 110:
            output.Color = input.Color * Texture[110].Sample(Sampler0, input.UV);
            break;
        case 111:
            output.Color = input.Color * Texture[111].Sample(Sampler0, input.UV);
            break;
        case 112:
            output.Color = input.Color * Texture[112].Sample(Sampler0, input.UV);
            break;
        case 113:
            output.Color = input.Color * Texture[113].Sample(Sampler0, input.UV);
            break;
        case 114:
            output.Color = input.Color * Texture[114].Sample(Sampler0, input.UV);
            break;
        case 115:
            output.Color = input.Color * Texture[115].Sample(Sampler0, input.UV);
            break;
        case 116:
            output.Color = input.Color * Texture[116].Sample(Sampler0, input.UV);
            break;
        case 117:
            output.Color = input.Color * Texture[117].Sample(Sampler0, input.UV);
            break;
        case 118:
            output.Color = input.Color * Texture[118].Sample(Sampler0, input.UV);
            break;
        case 119:
            output.Color = input.Color * Texture[119].Sample(Sampler0, input.UV);
            break;
        case 120:
            output.Color = input.Color * Texture[120].Sample(Sampler0, input.UV);
            break;
        case 121:
            output.Color = input.Color * Texture[121].Sample(Sampler0, input.UV);
            break;
        case 122:
            output.Color = input.Color * Texture[122].Sample(Sampler0, input.UV);
            break;
        case 123:
            output.Color = input.Color * Texture[123].Sample(Sampler0, input.UV);
            break;
        case 124:
            output.Color = input.Color * Texture[124].Sample(Sampler0, input.UV);
            break;
        case 125:
            output.Color = input.Color * Texture[125].Sample(Sampler0, input.UV);
            break;
        case 126:
            output.Color = input.Color * Texture[126].Sample(Sampler0, input.UV);
            break;
        case 127:
            output.Color = input.Color * Texture[127].Sample(Sampler0, input.UV);
            break;
    }
    return output;
}