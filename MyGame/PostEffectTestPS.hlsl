#include"PostEffectTest.hlsli"
Texture2D<float4>tex:register(t0);

SamplerState smp:register(s0);
float4 main(Output input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp,input.uv);
    
    float offsetU = 3.5f / 1280.0f;
    float offsetV = 3.5f / 720.0f;
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

    //FˆÃ‚­‚È‚é‚â‚Â
    //return float4(1-texcolor.rgb, 1);
    //F–¾‚é‚­‚È‚é‚â‚Â –Ú‚ªI‚í‚é
    // return float4(texcolor.rgb*2, 1);
    //return tex.Sample(smp,input.uv) * color;
//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}