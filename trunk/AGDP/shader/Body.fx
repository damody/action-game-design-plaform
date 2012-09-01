cbuffer cbPerFrame
{
	float sceneW;
	float sceneH;
	float3 cLookAt;
	float3 cPolarCoord;
};


struct VS_IN
{
    float3 position	 : POSITION;
	float2 body 	 : BODY;
	float  angle	 : PI;
	float  faceside  : FACE;
	float2 center	 : CENTER; 
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
};

VS_OUT VS_Main(VS_IN vIn) : SV_POSITION
{
    VS_OUT vOut;
    
	float thita = cPolarCoord.y *3.14159/180;
	float alpha = cPolarCoord.z *3.14159/180;
	
	vIn.position= float4(vIn.position.xyz-cLookAt.xyz,1.0);		 
	
	float3x3 view;
	view[0]=float3(cos(-thita) 	, -sin(-thita) * -sin(-alpha) , -sin(-thita) * cos(-alpha) );
	view[1]=float3(0			,  cos(-alpha) 			  	  ,  sin(-alpha)	            );
	view[2]=float3(sin(-thita) 	,  cos(-thita) * -sin(-alpha) ,  cos(-thita) * cos(-alpha) );
	
	//vIn.position = float4(mul(float3(vIn.position.xyz),view),1.0) ;
	vIn.position = float4(vIn.position.x-vIn.faceside*vIn.center.x,vIn.position.y+vIn.center.y,vIn.position.z,1.0);
	
	float x = vIn.angle*3.14159/180;
	float2x2 mat = {cos(x), -sin(x), sin(x), cos(x)};
	
	//vOut.pos = float4(float2(mul(float2(vIn.position.xy+vIn.body.xy),mat)),vIn.position.z,1.0);
	
	vOut.pos = float4(vIn.position.x+vIn.faceside*vIn.body.x,vIn.position.y+vIn.body.y,vIn.position.z,1.0);

	vOut.pos = float4(mul(vOut.pos.xyz,view),1.0);
	float offset =0.1/tan(3.14159/6);
	float4x4 proj;
	proj[0]=float4(1/(sceneW+(cPolarCoord.x+vOut.pos.z)*offset*sceneW/sceneH),0,0,0);
	proj[1]=float4(0,1/(sceneH+(cPolarCoord.x+vOut.pos.z)*offset),0,0);
	proj[2]=float4(0,0,1/30000.0,0);
	proj[3]=float4(0,0.0,0.1,1);
	
	vOut.pos = float4(mul(vOut.pos,proj));
	
	
	return vOut;
	
}


float4 PS_Main( float4 pos : SV_POSITION ) : SV_TARGET
{
    return float4( 1.0f, 1.0f, 1.0f, 0.5f );
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