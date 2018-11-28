float4 VS(in float4 p : POSITION) :SV_POSITION
{
	return p;
}

//POSITION은 float3를 넘겨도 float4로 받는다.