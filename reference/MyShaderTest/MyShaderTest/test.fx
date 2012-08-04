
/////////////
// GLOBALS //
/////////////
Texture2D fireTexture;
Texture2D noiseTexture;
Texture2D alphaTexture;
SamplerState SampleType;
SamplerState SampleType2;

cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer NoiseBuffer
{
	float frameTime;
	float3 scrollSpeeds;
	float3 scales;
	float padding;
};
cbuffer DistortionBuffer
{
	float2 distortion1;
	float2 distortion2;
	float2 distortion3;
	float distortionScale;
	float distortionBias;
};
cbuffer cbPerFrame
{
	float width;
	float height;
	float3 cLookAt;
	float3 cPolarCoord;
};

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
	float4	picpos : PICPOS; // x, y, w, h
};

struct VS_OUT
{
	float4	pos   : SV_POSITION;
	float2	size  : TEXCOORD0;
	float4	picpos : PICPOS; // x, y, w, h
};

struct GS_OUT
{
    float4 posH : SV_POSITION;
    float2 texcoord : TEXCOORD0;
	float2 texCoords1 : TEXCOORD1;
	float2 texCoords2 : TEXCOORD2;
	float2 texCoords3 : TEXCOORD3;
};
 
VS_OUT VS(VS_IN vIn)
{
	VS_OUT vOut;
	

	vOut.pos =float4(vIn.position.xyz,1.0) ;
	vOut.size = vIn.size;
	vOut.picpos = vIn.picpos;
	return vOut;
}
GS_OUT calculate(float2 pos,float2 tex)
{
	GS_OUT output;
	output.posH = float4(pos,1,1);
	
	
	
	
	//output.posH = mul(output.posH, worldMatrix);
    //output.posH = mul(output.posH, viewMatrix);
    //output.posH = mul(output.posH, projectionMatrix);
	// Store the texture coordinates for the pixel shader.
	output.texcoord = tex;

    // Compute texture coordinates for first noise texture using the first scale and upward scrolling speed values.
	output.texCoords1 = (tex * scales.x);
	output.texCoords1.y = output.texCoords1.y + (frameTime * scrollSpeeds.x);

    // Compute texture coordinates for second noise texture using the second scale and upward scrolling speed values.
	output.texCoords2 = (tex * scales.y);
	output.texCoords2.y = output.texCoords2.y + (frameTime * scrollSpeeds.y);

    // Compute texture coordinates for third noise texture using the third scale and upward scrolling speed values.
	output.texCoords3 = (tex * scales.z);
	output.texCoords3.y = output.texCoords3.y + (frameTime * scrollSpeeds.z);
	
    return output;
}

[maxvertexcount (6)]
void gs_main(point VS_OUT input[1], inout TriangleStream<GS_OUT> triStream)
{
	float2 texsize = {1/input[0].picpos.z, 1/input[0].picpos.w};
	float2 newTex;

	float2 lt,ld,rt,rd;
	lt = float2(input[0].pos.x-(input[0].size.x)/2,input[0].pos.y+(input[0].size.y)/2);
	ld= float2(input[0].pos.x-(input[0].size.x)/2,input[0].pos.y-(input[0].size.y)/2);
	rt = float2(input[0].pos.x+(input[0].size.x)/2,input[0].pos.y+(input[0].size.y)/2);
	rd = float2(input[0].pos.x+(input[0].size.x)/2,input[0].pos.y-(input[0].size.y)/2);
	
	
	GS_OUT out5;
	
	newTex = float2(0,0);
	//newTex = float2( texsize.x*(input[0].picpos.x), texsize.y*(input[0].picpos.y-1));
	out5 = calculate(lt,newTex);
	/*out5.posH = float4(lt,1,1);
	out5.texcoord = float2(0,0);*/
	triStream.Append( out5 );
	
	newTex = float2(1,0);
	//newTex = float2( texsize.x*(input[0].picpos.x), texsize.y*(input[0].picpos.y));
	out5 = calculate(rt,newTex);
	/*out5.posH = float4(rt,1,1);
	out5.texcoord = float2(1,0);*/
	triStream.Append( out5 );
	
	newTex = float2(0,1);
	//newTex = float2( texsize.x*(input[0].picpos.x-1), texsize.y*(input[0].picpos.y-1));
	out5 = calculate(ld,newTex);
	/*out5.posH = float4(ld,1,1);
	out5.texcoord = float2(0,1);*/
	triStream.Append( out5 );
	
	newTex = float2(1,0);
	//newTex = float2( texsize.x*(input[0].picpos.x), texsize.y*(input[0].picpos.y));
	out5 = calculate(rt,newTex);
	/*out5.posH = float4(rt,1,1);
	out5.texcoord = float2(1,0);*/
	triStream.Append( out5 );
	
	newTex = float2(0,1);
	//newTex = float2( texsize.x*(input[0].picpos.x-1), texsize.y*(input[0].picpos.y-1));
	out5 = calculate(ld,newTex);
	/*out5.posH = float4(ld,1,1);
	out5.texcoord = float2(0,1);*/
	triStream.Append( out5 );
	
	newTex = float2(1,1);
	//newTex = float2( texsize.x*(input[0].picpos.x-1), texsize.y*(input[0].picpos.y));
	out5 = calculate(rd,newTex);
	/*out5.posH = float4(rd,1,1);
	out5.texcoord = float2(1,1);*/
	triStream.Append( out5 );
	
	triStream.RestartStrip( );
}

float4 PS(GS_OUT pIn) : SV_Target
{
	float4 noise1;
	float4 noise2;
	float4 noise3;
	float4 finalNoise;
	float perturb;
	float2 noiseCoords;
	float4 fireColor;
	float4 alphaColor;


	// Sample the same noise texture using the three different texture coordinates to get three different noise scales.
	
	
    noise1 = noiseTexture.Sample(SampleType, pIn.texCoords1);
	float temp = (noise1[0] + noise1[1] + noise1[2]) / 3;
	if (temp < 0.75) temp*=1.33;
	if (temp < 0.5) temp*=2;
	noise1[0] = temp;
	noise1[1] = temp;
	noise1[2] = temp;
    noise2 = noiseTexture.Sample(SampleType, pIn.texCoords2);
	noise3 = noiseTexture.Sample(SampleType, pIn.texCoords3);

	// Move the noise from the (0, 1) range to the (-1, +1) range.
    noise1 = (noise1 - 0.5f) * 1.0f;
    noise2 = (noise2 - 0.5f) * 1.0f;
    noise3 = (noise3 - 0.5f) * 0.3f;

	// Distort the three noise x and y coordinates by the three different distortion x and y values.
	noise1.xy = noise1.xy * distortion1.xy;
	noise2.xy = noise2.xy * distortion2.xy;
	noise3.xy = noise3.xy * distortion3.xy;

	// Combine all three distorted noise results into a single noise result.
	finalNoise = noise1 + noise2 + noise3;

	// Perturb the input texture Y coordinates by the distortion scale and bias values.  
	// The perturbation gets stronger as you move up the texture which creates the flame flickering at the top effect.
	perturb = ((1.0f - pIn.texcoord.y) * distortionScale) + distortionBias;

	// Now create the perturbed and distorted texture sampling coordinates that will be used to sample the fire color texture.
	noiseCoords.xy = (finalNoise.xy * perturb) + pIn.texcoord.xy;

	// Sample the color from the fire texture using the perturbed and distorted texture sampling coordinates.
	// Use the clamping sample state instead of the wrap sample state to prevent flames wrapping around.
    fireColor = fireTexture.Sample(SampleType2, noiseCoords.xy);

	// Sample the alpha value from the alpha texture using the perturbed and distorted texture sampling coordinates.
	// This will be used for transparency of the fire.
	// Use the clamping sample state instead of the wrap sample state to prevent flames wrapping around.
    alphaColor = alphaTexture.Sample(SampleType2, noiseCoords.xy);

	// Set the alpha blending of the fire to the perturbed and distored alpha texture value.
	fireColor.a = alphaColor;
	noise2 = alphaTexture.Sample(SampleType, pIn.texcoord);
		fireColor.r = (noise2.r*(1-fireColor.a)+fireColor.r*fireColor.a);
		fireColor.g = (noise2.g*(1-fireColor.a)+fireColor.g*fireColor.a);
		fireColor.b = (noise2.b*(1-fireColor.a)+fireColor.b*fireColor.a);
	fireColor.a = max(noise2.a , fireColor.a);
    return fireColor;

/*
	float4 color=alphaTexture.Sample( gTriLinearSam, pIn.texcoord );
	if (color.a<0.5)
		discard;
	return color;
	*/
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