struct VS_INPUT
{
	float3 p : POS;
	float3 n : NOMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD;
};
struct VS_OUTPUT
{
	float4 p : POS0;	 // Ω√∏‡∆Ω(¿«πÃ±∏¡∂)
	float3 n : NOMAL0;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT vOut = (VS_OUTPUT)0;
	vOut.p = float4(vIn.p.x, vIn.p.y, vIn.p.z, 1.0f);
	vOut.n = vIn.n;
	vOut.t = vIn.t;
	vOut.c = vIn.c;
	return vOut;
}
