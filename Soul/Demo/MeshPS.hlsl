#include <Shared.fxh>

float4 main(VS_OUTPUT input) : SV_Target
{
    input.NormalW = normalize(input.NormalW);
    
    float4 color = baseColorTex.Sample(samLinear,input.Tex);

    float3 normalMapSample = normalTex.Sample(samLinear, input.Tex).rgb;
    float3 bumpedNormalW = NormalSampleToWorldSpace(normalMapSample, input.NormalW, input.TangentW);
    
    color = float4(bumpedNormalW,1.f);

    return color;
}