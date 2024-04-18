struct OUTPUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXTURE;
};

OUTPUT main(float4 pos : POSITION, float2 tex : TEXTURE)
{
    OUTPUT output;
    output.pos = pos;
    output.tex = tex;
    return output;
}