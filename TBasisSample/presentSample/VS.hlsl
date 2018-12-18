//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 p : SV_POSITION;
};

VS_OUTPUT VS(float4 p : POSITION)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = p;
	return output;
}


