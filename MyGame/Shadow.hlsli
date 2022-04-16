cbuffer cbTansMatrix:register(b0) {
	float4x4 WVP;
}
Texture2D<float>tex0 : register(t0);
SamplerState samp0:register(s0);

struct VS_INPUT {
	float3 Position:POSITION;
	float3 Normal:NORMAL;
	float2 UV:TEXCOORD;
};
struct PS_INPUT {
	float4 Position:SV_POSITION;
	float2 UV:TEXCOORD;
};