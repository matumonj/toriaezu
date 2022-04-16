#include"Shadow.hlsli"
PS_INPUT main(VS_INPUT input) {
	PS_INPUT output;

	float4 Pos = float4(input.Position, 1.0f);
	output.Position = mul(Pos, WVP);
	output.UV.x = input.UV.x;
	output.UV.y = 1.0f - input.UV.y;

	return output;
}