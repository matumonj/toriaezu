#include"Shadow.hlsli"

float4 main(PS_INPUT input) :SV_TARGET{
	float color = tex0.Sample(samp0,input.UV);
return float4(color, color, color, 1.0f);
}