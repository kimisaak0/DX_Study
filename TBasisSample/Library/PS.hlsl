Texture2D  g_txTextureA : register(t0);
SamplerState  sample0 : register(s0);

struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 c : SV_TARGET;
};

PS_OUTPUT PS(VS_OUTPUT vIn)
{
	PS_OUTPUT vOut;
	vOut.c = g_txTextureA.Sample(sample0, vIn.t) * vIn.c;
	if (vOut.c.a == 0) {
		discard;
	}
	return vOut;
}