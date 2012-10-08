cbuffer cbPerFrame
{
	float sceneW;
	float sceneH;
};
 
Texture2D gMap;
Texture2D bMap;
SamplerState gTriLinearSam
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_IN
{
	float2	position	: POSITION;
	float2	size		: SIZE;
	float4	picpos 		: PICPOSITION; // x, y, w, h
};

struct VS_OUT
{
	float4	pos   : SV_POSITION;
	float2	size  : TEXCOORD0;
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
	
	vOut.pos= float4(vIn.position.xy,0.0,1.0);
	vOut.size = vIn.size;
	vOut.picpos = vIn.picpos;
	return vOut;
}


[maxvertexcount (6)]
void gs_main(point VS_OUT input[1], inout TriangleStream<GS_OUT> triStream)
{
	float2 texsize = {1/input[0].picpos.z, 1/input[0].picpos.w};

	float w = 2/sceneW;
	float h = 2/sceneH;

	float4x4 proj;
	proj[0]=float4(w,0,0,0);
	proj[1]=float4(0,h,0,0);
	proj[2]=float4(0,0,1,0);
	proj[3]=float4(-1,1,0,1);

	GS_OUT out5;
	out5.posH=float4(input[0].pos.xy-float2(-input[0].size.x,0),0,1);
	out5.posH=mul(out5.posH,proj);
//	out5.texcoord=(1,1);
 	out5.texcoord = float2( texsize.x*(input[0].picpos.x), texsize.y*(input[0].picpos.y-1));
	triStream.Append( out5 );

	out5.posH=float4(input[0].pos.xy-float2(-input[0].size.x,input[0].size.y),0,1);
	out5.posH=mul(out5.posH,proj);
//	out5.texcoord=(1,0);
 	 out5.texcoord = float2( texsize.x*(input[0].picpos.x), texsize.y*(input[0].picpos.y));
	triStream.Append( out5 );

	out5.posH=float4(input[0].pos.xy-float2( 0,0),0,1);
	out5.posH=mul(out5.posH,proj);
	out5.texcoord = float2( texsize.x*(input[0].picpos.x-1), texsize.y*(input[0].picpos.y-1));
//	out5.texcoord=(0,1);
	triStream.Append( out5 );

	out5.posH=float4(input[0].pos.xy-float2(-input[0].size.x,input[0].size.y),0,1);
	out5.posH=mul(out5.posH,proj);
	out5.texcoord = float2( texsize.x*(input[0].picpos.x), texsize.y*(input[0].picpos.y));
//	out5.texcoord=(1,0);
	triStream.Append( out5 );

	out5.posH=float4(input[0].pos.xy-float2( 0,0),0,1);
	out5.posH=mul(out5.posH,proj);
	out5.texcoord = float2( texsize.x*(input[0].picpos.x-1), texsize.y*(input[0].picpos.y-1));
//	out5.texcoord=(0,1);
	triStream.Append( out5 );

	out5.posH=float4(input[0].pos.xy-float2( 0,input[0].size.y),0,1);
	out5.posH=mul(out5.posH,proj);
	out5.texcoord = float2( texsize.x*(input[0].picpos.x-1), texsize.y*(input[0].picpos.y));
//	out5.texcoord=(0,0);
	triStream.Append( out5 );

	triStream.RestartStrip( );
}

float4 PS(GS_OUT pIn) : SV_Target
{
	float4 picture=gMap.Sample( gTriLinearSam, pIn.texcoord );
	float4 background=bMap.Sample( gTriLinearSam, pIn.texcoord );
	return float4(picture.xyz * picture.w + background.xyz * (1-picture.w),1.0);
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