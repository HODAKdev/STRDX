struct INPUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXTURE;
};

cbuffer ConstantBuffer : register(b0)
{
    float iTime;
    float2 iResolution;
    matrix iWorld;
    matrix iView;
    matrix iProjection;
}

Texture2D iTexture2D;
SamplerState iSamplerState;

float4 main(INPUT input) : SV_Target
{
    float4 color = iTexture2D.Sample(iSamplerState, input.tex);

    float2 fragCoord = input.pos.xy;
    float2 uv = fragCoord.xy / iResolution.xy;
    uv *= 1.0 - uv.yx;
    float vig = uv.x * uv.y * 15.0;
    vig = pow(vig, 0.1);
    return float4(color.x * vig, color.y * vig, color.z * vig, 1.0);
}