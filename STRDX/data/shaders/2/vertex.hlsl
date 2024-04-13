struct OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
};

OUTPUT main(float4 Pos : POSITION, float2 Tex : TEXCOORD)
{
    OUTPUT output;
    output.Pos = Pos;
    output.Tex = Tex;
    return output;
}