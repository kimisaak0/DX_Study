//struct VS_OUTPUT
//{
//	float4 p : SV_POSITION;
//	float4 c : COLOR;
//};
//
//float4 PS(VS_OUTPUT p : SV_POSITION) : SV_Target
//{
//	return float4(1.0f, 1.0f, 1.0f, 1.0f);
//}


float4 PS(in float4 p : SV_POSITION) : SV_Target
{
	return float4(1.0f, 1.0f, 0.0f, 1.0f);    // Yellow, with Alpha = 1
}