#include"pmdheader.hlsli"


Output main(float4 pos:POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD,min16uint2 boneno:BONE_NO,min16uint weight:WEIGHT)
{
	Output output;
	//output.svpos = pos;
	output.normal = normal;
	//���W�ɍs�����Z���ďo��
	output.svpos = mul(mat, pos);
	output.uv = uv;
	output.boneno = boneno;
	output.weight = weight;
	return output;
}