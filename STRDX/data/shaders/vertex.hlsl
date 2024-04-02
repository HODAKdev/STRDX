struct OUTPUT
{
    float4 Pos : SV_POSITION;
};

OUTPUT main(float4 Pos : POSITION)
{
    OUTPUT output;
    output.Pos = Pos;
    return output;
}