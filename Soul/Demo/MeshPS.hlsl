#include <Shared.fxh>

float4 main(VS_OUTPUT input) : SV_Target
{
    input.NormalW = normalize(input.NormalW);
    
    float4 color = baseColorTex.Sample(samLinear,input.Tex);

    float3 normalMapSample = normalTex.Sample(samLinear, input.Tex).rgb;
    float3 bumpedNormalW = NormalSampleToWorldSpace(normalMapSample, input.NormalW, input.TangentW);
    
    //do NdotL lighting for 2 lights
    for (int i = 0; i < 2; i++)
    {
        color += saturate(dot((float3) lightDirection[i], bumpedNormalW) * lightColor[i]);
    }

    color.a = 1.f;
    
    return color;
}