cbuffer cbPerFrame
{
	float sceneW; 
	float sceneH;
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
	float3	position	: POSITION;
	float2	size    	: SIZE;
	float   angle   	: PI;
	float3  color		: FORECOLOR;
	float4  backcolor   : BACKCOLOR;
};

struct VS_OUT
{
	float4	pos   		: SV_POSITION;
	float2	size  		: TEXCOORD0;
	float   angle 		: PI;
	float3  color		: FORECOLOR;
	float4  backcolor   : BACKCOLOR;
};

struct GS_OUT
{
	float4 posH    		: SV_POSITION;
	float2 texcoord 	: TEXCOORD0;
	float3 color		: FORECOLOR;
	float4 backcolor   	: BACKCOLOR;
};
 
VS_OUT VS(VS_IN vIn)
{
	VS_OUT vOut;
	
	vOut.pos= float4(vIn.position.xy,0.0,1.0);		 
	vOut.size = vIn.size;
	vOut.angle = vIn.angle;
	vOut.backcolor = vIn.backcolor;
	vOut.color = vIn.color;
	return vOut;
}


[maxvertexcount (6)]
void gs_main(point VS_OUT input[1], inout TriangleStream<GS_OUT> triStream)
{
	float x = input[0].angle*3.14159/180;
	float2x2 mat = {cos(x), -sin(x), sin(x), cos(x)};

	float4x4 proj;
	proj[0]=float4(2/sceneW,0,0,0);
	proj[1]=float4(0,2/sceneH,0,0);
	proj[2]=float4(0,0,1,0);
	proj[3]=float4(0,0,0,1);

	GS_OUT out5;
	out5.posH=float4(float3(input[0].pos.xy-mul(float2(-input[0].size.x,0), mat),input[0].pos.z),1);
	out5.posH=mul(out5.posH,proj);
	out5.texcoord = float2(1,1);
	out5.color = input[0].color;
	out5.backcolor = input[0].backcolor;
	triStream.Append( out5 );

	out5.posH=float4(float3(input[0].pos.xy-mul(float2(-input[0].size.x,input[0].size.y), mat),input[0].pos.z),1);
	out5.posH=mul(out5.posH,proj);
	out5.texcoord = float2(1,0);
	out5.color = input[0].color;
	out5.backcolor = input[0].backcolor;
	triStream.Append( out5 );

	out5.posH=float4(float3(input[0].pos.xy-mul(float2( 0,0), mat),input[0].pos.z),1);
	out5.posH=mul(out5.posH,proj);
	out5.texcoord = float2(0,1);
	out5.color = input[0].color;
	out5.backcolor = input[0].backcolor;
	triStream.Append( out5 );

	out5.posH=float4(float3(input[0].pos.xy-mul(float2(-input[0].size.x,input[0].size.y), mat),input[0].pos.z),1);
	out5.posH=mul(out5.posH,proj);
	out5.texcoord = float2(1,0);
	out5.color = input[0].color;
	out5.backcolor = input[0].backcolor;
	triStream.Append( out5 );

	out5.posH=float4(float3(input[0].pos.xy-mul(float2( 0,0), mat),input[0].pos.z),1);
	out5.posH=mul(out5.posH,proj);
	out5.texcoord = float2(0,1);
	out5.color = input[0].color;
	out5.backcolor = input[0].backcolor;
	triStream.Append( out5 );

	out5.posH=float4(float3(input[0].pos.xy-mul(float2( 0,input[0].size.y), mat),input[0].pos.z),1);
	out5.posH=mul(out5.posH,proj);
	out5.texcoord = float2(0,0);
	out5.color = input[0].color;
	out5.backcolor = input[0].backcolor;
	triStream.Append( out5 );

	triStream.RestartStrip( );
}

float4 PS(GS_OUT pIn) : SV_Target
{
	float4 color=gMap.Sample( gTriLinearSam, pIn.texcoord );
	
	if(color.a == 1.0){
			color = float4(pIn.color.xyz,1.0);
	}else{
			color = pIn.backcolor;
	}
	
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