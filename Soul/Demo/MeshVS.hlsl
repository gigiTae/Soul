#include <Shared.fxh>

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    output.PosW = mul(float4(input.PosL,1.0f), World).xyz;
    output.NormalW = mul(input.NormalL, (float3x3)WorldInverseTranspose);
    output.TangentW = mul(input.Tangent, (float3x3)World);

    output.PosH = mul(float4(input.PosL, 1.f), World);
    output.PosH = mul(output.PosH, View );
    output.PosH = mul(output.PosH, Projection);
    output.Tex = input.Tex;
    
    return output;
}