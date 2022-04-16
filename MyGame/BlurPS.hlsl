#include"Blur.hlsli"

Texture2D<float4> sceneTexture : register(t0); // �V�[���e�N�X�`��
sampler Sampler : register(s0);

float4 main(PSInput In) : SV_Target0
{
    float4 color = sceneTexture.Sample(Sampler, In.uv);

    // step-1 ��e�N�Z��+�ߖT8�e�N�Z���̕��ς��v�Z����
    // 2.5�e�N�Z�������炷���߂�UV�l�����߂�
    float offsetU = 1.5f / 1280.0f;
    float offsetV = 1.5f / 720.0f;

    color += sceneTexture.Sample(Sampler, In.uv + float2(offsetU, 0.0f));

    color += sceneTexture.Sample(Sampler, In.uv + float2(-offsetU, 0.0f));

    color += sceneTexture.Sample(Sampler, In.uv + float2(0.0f, offsetV));

    color += sceneTexture.Sample(Sampler, In.uv + float2(0.0f, -offsetV));

    color += sceneTexture.Sample(Sampler, In.uv + float2(offsetU, offsetV));

    color += sceneTexture.Sample(Sampler, In.uv + float2(offsetU, -offsetV));

    color += sceneTexture.Sample(Sampler, In.uv + float2(-offsetU, offsetV));

    color += sceneTexture.Sample(Sampler, In.uv + float2(-offsetU, -offsetV));

    color /= 9.0f;
    float y = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
    color.r = y;
    color.g = y;
    color.b = y;
    return color;
}