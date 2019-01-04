Texture2D  g_txTextureA : register(t0);
SamplerState  sample0 : register(s0);

struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float2 t : TEXCOORD0;
};
struct PS_OUTPUT
{
	float4 c : SV_TARGET;
};

PS_OUTPUT PS(VS_OUTPUT vIn)
{
	return  g_txTextureA.Sample(sample0, vIn.t);
}