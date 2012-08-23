cbuffer cbPerFrame
{
	float  sceneW;
	float  sceneH;
};

struct VS_IN
{
	float2	position: POSITION;
	float4  color   : COLOR;
};

struct VS_OUT
{
	float4	pos   : SV_POSITION;
	float4  color : COLOR4;
};
 
VS_OUT VS_Main(VS_IN vIn)
{
	VS_OUT vOut;
	float w = 2 / sceneW;
	float h = -2 / sceneH;

	float4x4 proj;
	proj[0]=float4(w,0,0,0);
	proj[1]=float4(0,h,0,0);
	proj[2]=float4(0,0,1,0);
	proj[3]=float4(-1,1,0,1);
	
	vOut.pos= mul(float4(vIn.position.x,vIn.position.y,0.0,1.0),proj);
	vOut.color = vIn.color;
	return vOut;
}

float4 PS_Main( VS_OUT pIn ) : SV_TARGET
{
    return pIn.color;
}

technique11 PointTech
{
pass P0
{
SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
SetGeometryShader( NULL );
SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
}
}