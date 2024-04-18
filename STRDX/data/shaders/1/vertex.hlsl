struct OUTPUT
{
    float4 pos : SV_POSITION;
};

OUTPUT main(float4 pos : POSITION)
{
    OUTPUT output;
    output.pos = pos;
    return output;
}