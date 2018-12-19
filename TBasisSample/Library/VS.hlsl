struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR;
};

VS_OUTPUT VS(float3 p : POSITION, float4 c : COLOR)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = float(p, 1);
	output.c = c;
	return output;
}
