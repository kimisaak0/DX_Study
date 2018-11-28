struct VS_OUTPUT
{
    float4 p : SV_POSITION;
};

[maxvertexcount(9)]
void GS( triangle VS_OUTPUT input[3], inout TriangleStream<VS_OUTPUT> TriStream )
{    
    VS_OUTPUT output;
    // 페이스의 중점을 구한다.
    float3 centerPos = (input[0].p.xyz + input[1].p.xyz + input[2].p.xyz)/3.0;
    
    // 정점 당 계산된 중점을 사용하여 페이스를 추가한다.
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