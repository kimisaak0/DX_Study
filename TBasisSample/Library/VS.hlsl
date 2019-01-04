struct VS_INPUT
{
	float3 p : POSITION;
	float2 t : TEXCOORD;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION;	 // Ω√∏‡∆Ω(¿«πÃ±∏¡∂)
	float2 t : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT vOut = (VS_OUTPUT)0;
	vOut.p = float4(vIn.p.x, vIn.p.y, vIn.p.z, 1.0f);
	vOut.t = vIn.t;
	return vOut;
}