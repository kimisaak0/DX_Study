cbuffer cb0
{
	float4x4  g_matWorld : packoffset(c0);
	matrix  g_matView : packoffset(c4);
	matrix  g_matProj : packoffset(c8);

	float  g_fTimer : packoffset(c12.x);
	float  y : packoffset(c12.y);
	float  z : packoffset(c12.z);
	float  w : packoffset(c12.w);

	float4 g_Color : packoffset(c13);
};
Texture2D     g_txDiffuse : register(t0);
SamplerState  g_samLinear : register(s0);
SamplerState  g_samPoint : register(s0);

struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};


float4 PS(VS_OUTPUT v) : SV_Target
{
	float4 vTexColor = g_txDiffuse.Sample(g_samLinear, v.t);
	return vTexColor * v.c;
}
float4 PSLine(VS_OUTPUT v) : SV_Target
{
	return v.c;
}
float4 PSColor(VS_OUTPUT v) : SV_Target
{
	return g_Color;
}

float4 PSsky(VS_OUTPUT v) : SV_Target
{
	return g_txDiffuse.Sample(g_samPoint, v.t);
}
