
Texture2D gMap1;
Texture2D gMap2;
SamplerState gTriLinearSam
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_IN
{
	float4 position: POSITION;
	float2 size: TEXCOORD;
};

struct VS_OUT
{
	float4 pos   : SV_POSITION;
	float2 size  : TEXCOORD;
};
 
VS_OUT VS(VS_IN vIn)
{
	VS_OUT vOut;
	vOut.pos=vIn.position;
	vOut.size = vIn.size;
	return vOut;
}

float4 PS(VS_OUT pIn) : SV_Target
{
	float4 c1= gMap1.Sample(gTriLinearSam,pIn.size);
	float4 c2= gMap2.Sample(gTriLinearSam,pIn.size);
	return  c1;
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
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( NULL);
		SetPixelShader( CompileShader( ps_4_0, PS() ) );
		SetRasterizerState(NoCull);
		SetDepthStencilState(LessEqualDSS, 0);
	}
}
