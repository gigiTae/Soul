//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D baseColorTex : register(t0);
Texture2D normalTex : register(t1);

SamplerState samLinear : register(s0);

cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    matrix WorldInverseTranspose;   
}

cbuffer LightBuffer : register(b1)
{
    float4 lightDirection[2];
    float4 lightColor[2];
}

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float3 PosL : POSITION;
    float3 NormalL : NORMAL;
    float2 Tex : TEXCOORD0;
    float3 Tangent : TANGENT;
};

struct VS_OUTPUT
{
    float4 PosH : SV_POSITION;
    float3 PosW : POSITONN;
    float3 NormalW : NORMAL;
    float3 TangentW : TANGENT;
    float2 Tex : TEXCOORD0;
};

float3 NormalSampleToWorldSpace(float3 normalMapSample,
                                float3 unitNormalW,
                                float3 tangentW)
{
    // 각 성분을 [0,1] 에서 [-1,1]로 확장한다
    float3 normalT = 2.0f * normalMapSample - 1.0f;
    
    // 정규직교 기저를 구축한다.
    float3 N = unitNormalW;
    float3 T = normalize(tangentW - dot(tangentW, N) * N);
    float3 B = cross(N, T);
    
    float3x3 TBN = float3x3(T, B, N);
    
    // 접공간에서 세계공간으로 변환한다.
    float3 bumpedNormalW = mul(normalT, TBN);
   
    return bumpedNormalW;
}