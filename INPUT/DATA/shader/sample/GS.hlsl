struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR;
};



[maxvertexcount(9)]
void GS(triangle VS_OUTPUT input[3], inout TriangleStream<VS_OUTPUT> TriStream)
{
	VS_OUTPUT output;
	// ���̽��� ������ ���Ѵ�.
	float3 centerPos = (input[0].p.xyz + input[1].p.xyz + input[2].p.xyz) / 3.0;
	float4 centerColor = (input[0].c + input[1].c + input[2].c) / 4.0;
	// ���� �� ���� ������ ����Ͽ� ���̽��� �߰��Ѵ�.
	for (int i = 0; i<3; i++)
	{
		output.p = input[i].p;
		output.c = input[i].c;
		TriStream.Append(output);

		int iNext = (i + 1) % 3;
		output.p = input[iNext].p;
		output.c = input[iNext].c;
		TriStream.Append(output);

		output.p = float4(centerPos, 1);
		output.c = centerColor;
		TriStream.Append(output);


		TriStream.RestartStrip();
	}

	TriStream.RestartStrip();
}

//[maxvertexcount(9)]
//void GS(triangle VS_OUTPUT input[3], inout TriangleStream<VS_OUTPUT> TriStream)
//{
//	VS_OUTPUT output;
//
//	float3 a = (input[0].p + input[1].p) / 2.0;
//	float3 b = (input[1].p + input[2].p) / 2.0;
//	float3 c = (input[2].p + input[0].p) / 2.0;
//
//	//Ʈ���̾ޱ� ����Ʈ�� ������ ���� �ﰢ���� ������ ������ ���� �ﰢ���� ù��° �������� ����Ѵ�.
//
//	output.p = float4(c, 1);
//	output.c = float4(1, 1, 1, 1);
//	TriStream.Append(output);
//
//	output.p = input[0].p;
//	output.c = float4(1, 1, 1, 1);
//	TriStream.Append(output);
//
//	output.p = float4(a, 1);
//	output.c = float4(1, 1, 1, 1);
//	TriStream.Append(output);
//
//	output.p = input[1].p;
//	output.c = float4(1, 1, 1, 1);
//	TriStream.Append(output);
//
//	output.p = float4(b, 1);
//	output.c = float4(1, 1, 1, 1);
//	TriStream.Append(output);
//
//	output.p = input[2].p;
//	output.c = float4(1, 1, 1, 1);
//	TriStream.Append(output);
//
//	output.p = float4(c, 1);
//	output.c = float4(1, 1, 1, 1);
//	TriStream.Append(output);
//
//	output.p = float4(a, 1);
//	output.c = float4(1, 1, 1, 1);
//	TriStream.Append(output);
//
//	output.p = float4(b, 1);
//	output.c = float4(1, 1, 1, 1);
//	TriStream.Append(output);
//
//	TriStream.RestartStrip();
//}