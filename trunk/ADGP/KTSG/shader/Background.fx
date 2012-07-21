cbuffer cbPerFrame
{
	float sceneW; 
	float sceneH;
	float3 cLookAt;
	float3 cPolarCoord;
};
 
Texture2D gMap;
SamplerState gTriLinearSam
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_IN
{
	float3	position: POSITION;
	float2	size    : SIZE;
	float   width   : WIDTH;
	float   angle   : PI;
};

struct VS_OUT
{
	float4	pos   : SV_POSITION;
	float2	size  : TEXCOORD0;
	float   width : WIDTH;
	float   angle : PI;
};

struct GS_OUT
{
	float4 posH : SV_POSITION;
	float2 texcoord : TEXCOORD0;
};
 
VS_OUT VS(VS_IN vIn)
{
	VS_OUT vOut;
	
	float thita = cPolarCoord.y *3.14159/180;
	float alpha = cPolarCoord.z *3.14159/180;
	
	vIn.position= float4(vIn.position.xy-cLookAt.xy,vIn.position.z,1.0);
	float offset = (cLookAt.x - sceneW) * (vIn.width - vIn.size.x) / (vIn.width - sceneW);
	vIn.position.x += offset;
	vIn.position.xyz= (vIn.position.xyz)/float3(sceneW,sceneH,3000);
	
	vOut.pos =float4(vIn.position,1.0) ;
	
	vOut.size = vIn.size;
	vOut.angle = vIn.angle;
	return vOut;
}


[maxvertexcount (6)]
void gs_main(point VS_OUT input[1], inout TriangleStream<GS_OUT> triStream)
{
	float thita = -cPolarCoord.y *3.14159/180;
	float alpha = -cPolarCoord.z *3.14159/180;
	
	float x = input[0].angle*3.14159/180;
	float3x3 mat;
	mat[0]=float3(	1 	,  0 		,  0      );
	mat[1]=float3(	0	,  cos(x) 	,  sin(x) );
	mat[2]=float3(   0 	,  -sin(x)  ,  cos(x) );
	
	float3x3 view;
	view[0]=float3(cos(thita) 	, -sin(thita) * -sin(alpha) , -sin(thita) * cos(alpha) );
	view[1]=float3(	0			,  cos(alpha) 				,  sin(alpha)	           );
	view[2]=float3(sin(thita) 	,  cos(thita) * -sin(alpha) ,  cos(thita) * cos(alpha) );
	
	float3 size = {1/sceneW,1/sceneH,3000};
	
	GS_OUT out5;
	out5.posH=float4(mul(float3(input[0].pos.xyz-mul(float3(-input[0].size.x/2,-input[0].size.y,0),mat)*size),view),1);
	out5.texcoord = float2(0,-1);
	triStream.Append( out5 );
	out5.posH=float4(mul(float3(input[0].pos.xyz-mul(float3(-input[0].size.x/2,0,0), mat)*size),view),1);
	out5.texcoord = float2(0,0);
	out5.posH.z = 0;
	triStream.Append( out5 );
	out5.posH=float4(mul(float3(input[0].pos.xyz-mul(float3( input[0].size.x/2,-input[0].size.y,0), mat)*size),view),1);
	out5.texcoord = float2(-1,-1);
	out5.posH.z = 0;
	triStream.Append( out5 );
	out5.posH=float4(mul(float3(input[0].pos.xyz-mul(float3(-input[0].size.x/2,0,0), mat)*size),view),1);
	out5.texcoord = float2(0,0);
	out5.posH.z = 0;
	triStream.Append( out5 );
	out5.posH=float4(mul(float3(input[0].pos.xyz-mul(float3( input[0].size.x/2,-input[0].size.y,0), mat)*size),view),1);
	out5.texcoord = float2(-1,-1);
	out5.posH.z = 0;
	triStream.Append( out5 );
	out5.posH=float4(mul(float3(input[0].pos.xyz-mul(float3( input[0].size.x/2,0,0), mat)*size),view),1);
	out5.texcoord = float2(-1,0);
	out5.posH.z = 0;
	triStream.Append( out5 );
	
	triStream.RestartStrip( );
}

float4 PS(GS_OUT pIn) : SV_Target
{
	float4 color=gMap.Sample( gTriLinearSam, pIn.texcoord );
	if (color.a<0.5)
		discard;
	return color;
}

RasterizerState NoCull
{
	CullMode = None;
};

DepthStencilState LessEqualDSS
{
	// Make sure the depth function is LESS_EQUAL and not just LESS.  
	// Otherwise, the normalized depth values at z = 1 (NDC) will 
	// fail the depth test if the depth buffer was cleared to 1.
	DepthFunc = LESS_EQUAL;
};

technique11 PointTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( CompileShader( gs_5_0, gs_main() ) );
		SetPixelShader( CompileShader( ps_5_0, PS() ) );
		SetRasterizerState(NoCull);
		SetDepthStencilState(LessEqualDSS, 0);
	}
}