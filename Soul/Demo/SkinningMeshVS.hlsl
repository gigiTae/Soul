#include <Shared.fxh>

VS_OUTPUT main(SKINNING_VS_INPUT input)
{
    VS_OUTPUT output;

    float w = 1.f - input.Weight.x - input.Weight.y - input.Weight.z;
    
    float4x4 matWorld = mul(input.Weight.x, bone[input.BoneIndices.x]);
    matWorld += mul(input.Weight.y, bone[input.BoneIndices.y]);
    matWorld += mul(input.Weight.z, bone[input.BoneIndices.z]);
    matWorld += mul(w, bone[input.BoneIndices.w]);

    output.PosW = mul(float4(input.PosL,1.0f), matWorld).xyz;
    output.NormalW = mul(input.NormalL, (float3x3)WorldInverseTranspose);
    output.TangentW = mul(input.Tangent, (float3x3)matWorld);

    output.PosH = mul(float4(input.PosL, 1.f), matWorld);
    output.PosH = mul(output.PosH, View );
    output.PosH = mul(output.PosH, Projection);
    output.Tex = input.Tex;
    
    return output;
}