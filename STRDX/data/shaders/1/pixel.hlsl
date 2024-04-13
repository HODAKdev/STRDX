struct INPUT
{
    float4 Pos : SV_POSITION;
};

cbuffer ConstantBuffer : register( b0 )
{
    float iTime;
    float2 iResolution;
    matrix iWorld;
    matrix iView;
    matrix iProjection;
}

static float2 scrollDir;
static float2 sunrot;
static float spec;

float wave(inout float2 wavPos, int iters, float t)
{
    float wav = 0.0f;
    float2 wavDir = float2(1.0f, 0.0f);
    float wavWeight = 1.0f;
    wavPos += (scrollDir * (t * 1.5f));
    wavPos *= 1.10000002384185791015625f;
    float wavFreq = 0.60000002384185791015625f;
    float wavTime = 1.39999997615814208984375f * t;
    for (int i = 0; i < iters; i++)
    {
        wavDir = mul(float2x2(float2(0.3530193865299224853515625f, 0.935616016387939453125f), float2(-0.935616016387939453125f, 0.3530193865299224853515625f)), wavDir);
        float x = (dot(wavDir, wavPos) * wavFreq) + wavTime;
        float wave_1 = exp(sin(x) - 1.0f) * wavWeight;
        wav += wave_1;
        wavFreq *= 1.2000000476837158203125f;
        wavTime *= 1.0950000286102294921875f;
        wavPos -= (((wavDir * wave_1) * 0.89999997615814208984375f) * cos(x));
        wavWeight *= 0.800000011920928955078125f;
    }
    float wavSum = (-(pow(0.800000011920928955078125f, float(iters)) - 1.0f)) * 2.5f;
    return wav / wavSum;
}
float map(inout float3 p)
{
    float a = 0.0f;
    int steps = 9;
    float2 param = p.xz;
    int param_1 = steps;
    float param_2 = iTime;
    float _281 = wave(param, param_1, param_2);
    p.y -= _281;
    a = p.y;
    return a;
}
float3 pal(float t, float3 a, float3 b, float3 c, float3 d)
{
    return a + (b * cos(((c * t) + d) * 6.283185482025146484375f));
}
float3 spc(float n, float bright)
{
    float param = n;
    float3 param_1 = bright.xxx;
    float3 param_2 = 0.5f.xxx;
    float3 param_3 = 1.0f.xxx;
    float3 param_4 = float3(0.0f, 0.3300000131130218505859375f, 0.670000016689300537109375f);
    return pal(param, param_1, param_2, param_3, param_4);
}
float3 sky(inout float3 rd)
{
    float px = 1.5f / min(iResolution.x, iResolution.y);
    float3 rdo = rd;
    float rad = 0.07500000298023223876953125f;
    float3 col = 0.0f.xxx;
    float2 _355 = mul(float2x2(float2(cos(sunrot.y), sin(sunrot.y)), float2(-sin(sunrot.y), cos(sunrot.y))), rd.yz);
    rd = float3(rd.x, _355.x, _355.y);
    float2 _376 = mul(float2x2(float2(cos(sunrot.x), sin(sunrot.x)), float2(-sin(sunrot.x), cos(sunrot.x))), rd.xz);
    rd = float3(_376.x, rd.y, _376.y);
    float sFade = 2.5f / min(iResolution.x, iResolution.y);
    float zFade = (rd.z * 0.5f) + 0.5f;
    float param = spec - 0.100000001490116119384765625f;
    float param_1 = 0.60000002384185791015625f;
    float3 sc = spc(param, param_1) * 0.85000002384185791015625f;
    float a = length(rd.xy);
    float3 sun = ((sc * smoothstep((a - px) - sFade, (a + px) + sFade, rad)) * zFade) * 2.0f;
    col += sun;
    col += ((sc * (rad / (rad + pow(a, 1.7000000476837158203125f)))) * zFade);
    float param_2 = spec + 0.100000001490116119384765625f;
    float param_3 = 0.800000011920928955078125f;
    col += (lerp(col, spc(param_2, param_3), clamp(1.0f - length(col), 0.0f, 1.0f).xxx) * 0.20000000298023223876953125f);
    float e = 0.0f;
    float3 p = rdo;
    float2 _462 = p.xz * 0.4000000059604644775390625f;
    p = float3(_462.x, p.y, _462.y);
    p.x += (iTime * 0.007000000216066837310791015625f);
    for (float s = 200.0f; s > 10.0f; s *= 0.800000011920928955078125f)
    {
        float2 _496 = mul(float2x2(float2(cos(s), sin(s)), float2(-sin(s), cos(s))), p.xz);
        p = float3(_496.x, p.y, _496.y);
        p += s.xxx;
        e += abs(dot(sin((p * s) + (iTime * 0.0199999995529651641845703125f).xxx) / s.xxx, 1.64999997615814208984375f.xxx));
    }
    e *= smoothstep(0.5f, 0.4000000059604644775390625f, e - 0.0949999988079071044921875f);
    col += (((1.0f.xxx - (sun * 3.75f)) * ((e * smoothstep(-0.0199999995529651641845703125f, 0.300000011920928955078125f, rdo.y)) * 0.800000011920928955078125f)) * lerp(sc, 1.0f.xxx, 0.4000000059604644775390625f.xxx));
    return col;
}
float2 wavedx(inout float2 wavPos, int iters, float t)
{
    float2 dx = 0.0f.xx;
    float2 wavDir = float2(1.0f, 0.0f);
    float wavWeight = 1.0f;
    wavPos += (scrollDir * (t * 1.5f));
    wavPos *= 1.10000002384185791015625f;
    float wavFreq = 0.60000002384185791015625f;
    float wavTime = 1.39999997615814208984375f * t;
    for (int i = 0; i < iters; i++)
    {
        wavDir = mul(float2x2(float2(0.3530193865299224853515625f, 0.935616016387939453125f), float2(-0.935616016387939453125f, 0.3530193865299224853515625f)), wavDir);
        float x = (dot(wavDir, wavPos) * wavFreq) + wavTime;
        float result = exp(sin(x) - 1.0f) * cos(x);
        result *= wavWeight;
        dx += ((wavDir * result) / pow(wavWeight, 0.64999997615814208984375f).xx);
        wavFreq *= 1.2000000476837158203125f;
        wavTime *= 1.0950000286102294921875f;
        wavPos -= ((wavDir * result) * 0.89999997615814208984375f);
        wavWeight *= 0.800000011920928955078125f;
    }
    float wavSum = (-(pow(0.800000011920928955078125f, float(iters)) - 1.0f)) * 2.5f;
    return dx / pow(wavSum, 0.3499999940395355224609375f).xx;
}
float3 norm(float3 p)
{
    float2 param = p.xz;
    int param_1 = 20;
    float param_2 = iTime;
    float2 _258 = wavedx(param, param_1, param_2);
    float2 wav = -_258;
    return normalize(float3(wav.x, 1.0f, wav.y));
}
void render(inout float4 fragColor, float2 fragCoord)
{
    float2 uv = (fragCoord - (iResolution * 0.5f)) / min(iResolution.y, iResolution.x).xx;
    float3 col = 0.0f.xxx;
    float3 ro = float3(0.0f, 2.474999904632568359375f, -3.2999999523162841796875f);
    float3 lk = float3(0.0f, 2.0f, 0.0f);
    float3 f = normalize(lk - ro);
    float3 r = normalize(cross(float3(0.0f, 1.0f, 0.0f), f));
    float3 rd = normalize(((f * 0.89999997615814208984375f) + (r * uv.x)) + (cross(f, r) * uv.y));
    float dO = 0.0f;
    bool hit = false;
    float d = 0.0f;
    float3 p = ro;
    float tPln = (-(ro.y - 1.86000001430511474609375f)) / rd.y;
    if ((tPln > 0.0f) || true)
    {
        if (false)
        {
            dO += tPln;
        }
        for (float i = 0.0f; i < 80.0f; i += 1.0f)
        {
            p = ro + (rd * dO);
            float3 param = p;
            float _640 = map(param);
            d = _640;
            dO += d;
            if ((abs(d) < 0.004999999888241291046142578125f) || (i > 78.0f))
            {
                hit = true;
                break;
            }
            if (dO > 35.0f)
            {
                dO = 35.0f;
                break;
            }
        }
    }
    float3 param_1 = rd;
    float3 _666 = sky(param_1);
    float3 skyrd = _666;
    if (hit)
    {
        float3 param_2 = p;
        float3 n = norm(param_2);
        float3 rfl = reflect(rd, n);
        rfl.y = abs(rfl.y);
        float3 rf = refract(rd, n, 0.75187969207763671875f);
        float3 sd = float3(0.0f, 0.2873478829860687255859375f, -0.95782625675201416015625f);
        float fres = clamp(pow(1.0f - max(0.0f, dot(-n, rd)), 5.0f), 0.0f, 1.0f);
        float3 sunDir = float3(0.0f, 0.1500000059604644775390625f, 1.0f);
        float2 _726 = mul(float2x2(float2(cos(-sunrot.x), sin(-sunrot.x)), float2(-sin(-sunrot.x), cos(-sunrot.x))), sunDir.xz);
        sunDir = float3(_726.x, sunDir.y, _726.y);
        float3 param_3 = rfl;
        float3 _731 = sky(param_3);
        col += ((_731 * fres) * 0.89999997615814208984375f);
        float subRefract = pow(max(0.0f, dot(rf, sunDir)), 35.0f);
        float param_4 = spec - 0.100000001490116119384765625f;
        float param_5 = 0.5f;
        col += ((pow(spc(param_4, param_5), 2.2000000476837158203125f.xxx) * subRefract) * 2.5f);
        float3 rd2 = rd;
        float2 _776 = mul(float2x2(float2(cos(sunrot.x), sin(sunrot.x)), float2(-sin(sunrot.x), cos(sunrot.x))), rd2.xz);
        rd2 = float3(_776.x, rd2.y, _776.y);
        float param_6 = spec - 0.100000001490116119384765625f;
        float param_7 = 0.4000000059604644775390625f;
        float3 waterCol = min((((clamp(spc(param_6, param_7), 0.0f.xxx, 1.0f.xxx) * 0.0500000007450580596923828125f) * pow(min(p.y + 0.5f, 1.7999999523162841796875f), 4.0f)) * length(skyrd)) * ((rd2.z * 0.300000011920928955078125f) + 0.699999988079071044921875f), 1.0f.xxx);
        float param_8 = spec - 0.100000001490116119384765625f;
        float param_9 = 0.4000000059604644775390625f;
        waterCol = clamp(spc(param_8, param_9), 0.0f.xxx, 1.0f.xxx) * (((0.4000000059604644775390625f * pow(min((p.y * 0.699999988079071044921875f) + 0.89999997615814208984375f, 1.7999999523162841796875f), 4.0f)) * length(skyrd)) * ((rd2.z * 0.1500000059604644775390625f) + 0.85000002384185791015625f));
        col += (waterCol * 0.17000000178813934326171875f);
        col = lerp(col, skyrd, (dO / 35.0f).xxx);
    }
    else
    {
        col += skyrd;
    }
    col = clamp(col, 0.0f.xxx, 1.0f.xxx);
    col = pow(col, 0.87000000476837158203125f.xxx);
    col *= (1.0f - (0.800000011920928955078125f * pow(length(uv * float2(0.800000011920928955078125f, 1.0f)), 2.7000000476837158203125f)));
    fragColor = float4(col, 1.0f);
}
float4 main(INPUT input) : SV_Target
{
    float2 fragCoord = input.Pos.xy;
    fragCoord.y = iResolution.y - fragCoord.y;

    scrollDir = 1.0f.xx;
    sunrot = float2(-0.300000011920928955078125f, -0.25f);
    spec = 0.12999999523162841796875f;
    float2 uv = fragCoord.xy / iResolution.xy;
    float4 outColor = float4(0.5f.xxx + (cos(iTime.xxx + uv.yxy) * 0.5f), 1.0f);
    float px = 1.0f;
    float4 col = 0.0f.xxxx;
    float _898 = min(0.0f, iTime);
    float4 param;
    for (float i = _898; i < 1.0f; i += 1.0f)
    {
        float _908 = min(0.0f, iTime);
        for (float j = _908; j < 1.0f; j += 1.0f)
        {
            float2 coord = float2(fragCoord.x + (px * i), fragCoord.y + (px * j));
            float2 param_1 = coord;
            render(param, param_1);
            float4 col2 = param;
            float3 _941 = col.xyz + col2.xyz;
            col = float4(_941.x, _941.y, _941.z, col.w);
        }
    }
    col /= 1.0f.xxxx;
    outColor = float4(col);
    return outColor;
}