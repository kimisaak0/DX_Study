struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR;
};

VS_OUTPUT VS(float3 p : POSITION, float4 c : COLOR)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = float4(p, 1.0f);
	output.c = c;
	return output;
}

//struct VS_OUTPUT
//{
//	float4 p : SV_POSITION;
//	float4 c : COLOR;
//};
//
//VS_OUTPUT VS(float3 p : POSITION, float4 c : COLOR)
//{
//	VS_OUTPUT output = (VS_OUTPUT)0;
//	output.p = float4(p, 1.0f);
//	output.c = c;
//	return output;
//}