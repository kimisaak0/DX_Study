struct VS_OUTPUT
{
    float4 p : SV_POSITION;
};

[maxvertexcount(9)]
void GS( triangle VS_OUTPUT input[3], inout TriangleStream<VS_OUTPUT> TriStream )
{    
    VS_OUTPUT output;
    // ���̽��� ������ ���Ѵ�.
    float3 centerPos = (input[0].p.xyz + input[1].p.xyz + input[2].p.xyz)/3.0;
    
    // ���� �� ���� ������ ����Ͽ� ���̽��� �߰��Ѵ�.
    for( int i=0; i<3; i++ )
    {
        output.p = input[i].p;       
        TriStream.Append( output );
        
        int iNext = (i+1)%3;
        output.p =  input[iNext].p;        
        TriStream.Append( output );    
            
        output.p =  float4(centerPos,1);      
        TriStream.Append( output );
		TriStream.RestartStrip();
    }
    
    TriStream.RestartStrip();
}