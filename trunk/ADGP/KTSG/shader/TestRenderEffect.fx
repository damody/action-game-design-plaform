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
	

	
	vOut.pos =float4(vIn.position,1.0);
	vOut.size = vIn.size;
	vOut.angle = vIn.angle;
	vOut.picpos = vIn.picpos;
	return vOut;
}


[maxvertexcount (6)]
void gs_main(point VS_OUT input[1], inout TriangleStream<GS_OUT> triStream)
{
	float2 lt,ld,rt,rd;
	lt = float2(input[0].pos.x-(input[0].size.x)/2,input[0].pos.y+(input[0].size.y)/2);
	ld= float2(input[0].pos.x-(input[0].size.x)/2,input[0].pos.y-(input[0].size.y)/2);
	rt = float2(input[0].pos.x+(input[0].size.x)/2,input[0].pos.y+(input[0].size.y)/2);
	rd = float2(input[0].pos.x+(input[0].size.x)/2,input[0].pos.y-(input[0].size.y)/2);
	//lt = float2(input[0].x
	
	
	GS_OUT out5;
	out5.posH = float4(lt,1,1);
	out5.texcoord = float2(0,0);
	triStream.Append( out5 );
	
	out5.posH = float4(rt,1,1);
	out5.texcoord = float2(1,0);
	triStream.Append( out5 );
	
	out5.posH = float4(ld,1,1);
	out5.texcoord = float2(0,1);
	triStream.Append( out5 );
	
	out5.posH = float4(rt,1,1);
	out5.texcoord = float2(1,0);
	triStream.Append( out5 );
	
	out5.posH = float4(ld,1,1);
	out5.texcoord = float2(0,1);
	triStream.Append( out5 );
	
	out5.posH = float4(rd,1,1);
	out5.texcoord = float2(1,1);
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