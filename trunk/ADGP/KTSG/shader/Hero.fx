cbuffer cbPerFrame
{
	float width;
	float height;
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
	float2	size: SIZE;
	float	angle : PI;
	float4	picpos : PICPOS; // x, y, w, h
};

struct VS_OUT
{
	float4	pos   : SV_POSITION;
	float2	size  : TEXCOORD0;
	float	angle : ANGLE;
	float4	picpos : PICPOSITION; // x, y, w, h
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
	
	float3x3 view;
	view[0]=float3(cos(-thita) 	, -sin(-thita) * -sin(-alpha) , -sin(-thita) * cos(-alpha) );
	view[1]=float3(0			,  cos(-alpha) 			  	  ,  sin(-alpha)	           );
	view[2]=float3(sin(-thita) 	,  cos(-thita) * -sin(-alpha) ,  cos(-thita) * cos(-alpha) );
	
	vIn.position.xyz=mul(float3(vIn.position.xyz),view);
	vIn.position.z += cPolarCoord.x;
	
	float zDepth = 3000;
	vIn.position.z /= zDepth;
	vIn.position.xy= (vIn.position.xy) / float2(width*(1+cPolarCoord.x/zDepth)/(1-vIn.position.z),height*(1+cPolarCoord.x/zDepth)/(1-vIn.position.z));
	vIn.position.y -= 0.9; 
	vOut.pos =float4(vIn.position.xyz,1.0) ;
	
	
	vOut.size = vIn.size;
	vOut.angle = vIn.angle;
	vOut.picpos = vIn.picpos;
	return vOut;
}


[maxvertexcount (6)]
void gs_main(point VS_OUT input[1], inout TriangleStream<GS_OUT> triStream)
{
	float zDepth = 3000;
	float x = input[0].angle*3.14159/180;
	float2x2 mat = {cos(x), -sin(x), sin(x), cos(x)};
	float2 size = {(1-input[0].pos.z)/(width*(1+cPolarCoord.x/zDepth)),(1-input[0].pos.z)/(height*(1+cPolarCoord.x/zDepth))};
	float2 texsize = {1/input[0].picpos.z, 1/input[0].picpos.w};

	GS_OUT out5;
	out5.posH=float4(float3(input[0].pos.xy-mul(float2(-input[0].size.x,-2*input[0].size.y), mat)*size,input[0].pos.z),1);
	out5.texcoord = float2( texsize.x*(input[0].picpos.x), texsize.y*(input[0].picpos.y-1));
	triStream.Append( out5 );
	out5.posH=float4(float3(input[0].pos.xy-mul(float2(-input[0].size.x,0), mat)*size,input[0].pos.z),1);
	out5.texcoord = float2( texsize.x*(input[0].picpos.x), texsize.y*(input[0].picpos.y));
	triStream.Append( out5 );
	out5.posH=float4(float3(input[0].pos.xy-mul(float2( input[0].size.x,-2*input[0].size.y), mat)*size,input[0].pos.z),1);
	out5.texcoord = float2( texsize.x*(input[0].picpos.x-1), texsize.y*(input[0].picpos.y-1));
	triStream.Append( out5 );
	out5.posH=float4(float3(input[0].pos.xy-mul(float2(-input[0].size.x,0), mat)*size,input[0].pos.z),1);
	out5.texcoord = float2( texsize.x*(input[0].picpos.x), texsize.y*(input[0].picpos.y));
	triStream.Append( out5 );
	out5.posH=float4(float3(input[0].pos.xy-mul(float2( input[0].size.x,-2*input[0].size.y), mat)*size,input[0].pos.z),1);
	out5.texcoord = float2( texsize.x*(input[0].picpos.x-1), texsize.y*(input[0].picpos.y-1));
	triStream.Append( out5 );
	out5.posH=float4(float3(input[0].pos.xy-mul(float2( input[0].size.x,0), mat)*size,input[0].pos.z),1);
	out5.texcoord = float2( texsize.x*(input[0].picpos.x-1), texsize.y*(input[0].picpos.y));
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