#include"PostEffectTest.hlsli"
Texture2D<float4>tex:register(t0);

SamplerState smp:register(s0);
float4 main(Output input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp,input.uv);
    
    float offsetU = 5.0f / 1280.0f;
    float offsetV = 5.0f / 720.0f;
    //とりあえずのぼかし
    texcolor += tex.Sample(smp, input.uv + float2(offsetU, 0.0f));
    texcolor += tex.Sample(smp, input.uv + float2(-offsetU, 0.0f));
    texcolor += tex.Sample(smp, input.uv + float2(0.0f, offsetV));
    texcolor += tex.Sample(smp, input.uv + float2(0.0f, -offsetV));
    texcolor += tex.Sample(smp, input.uv + float2(offsetU, offsetV));
    texcolor += tex.Sample(smp, input.uv + float2(offsetU, -offsetV));
    texcolor += tex.Sample(smp, input.uv + float2(-offsetU, offsetV));
    texcolor += tex.Sample(smp, input.uv + float2(-offsetU, -offsetV));
    texcolor /= 9.0f;

    return float4(texcolor.rgb,1);

    //return float4(texcolor.rgb, 1);

    //色暗くなるやつ
    //return float4(1-texcolor.rgb, 1);
    //色明るくなるやつ 目が終わる
    // return float4(texcolor.rgb*2, 1);
    //return tex.Sample(smp,input.uv) * color;
//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}