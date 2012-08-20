
/////////////
// GLOBALS //
/////////////
Texture2D fireTexture;
Texture2D noiseTexture;
Texture2D alphaTexture;
SamplerState SampleType;
SamplerState SampleType2;


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


SamplerState gTriLinearSam
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_IN
{
	float2	position: POSITION;
	float4	picpos : PICPOS; // x, y, w, h
};

struct VS_OUT
{
	float2	pos   : POSITION;
	float4	picpos : PICPOS; // x, y, w, h
};

struct GS_OUT
{
    float4 posH : SV_POSITION;
    float2 texcoord : TEXCOORD0;
	float2 texCoords1 : TEXCOORD1;
	float2 texCoords2 : TEXCOORD2;
	float2 texCoords3 : TEXCOORD3;
	float2 texX : TEXCOORD5;//0 left 1 right
	float2 texY : TEXCOORD6;//0 top 1 bottom
};
VS_OUT VS(VS_IN vIn)
{
	VS_OUT vOut;
	

	vOut.pos = float2(vIn.position.xy);
	vOut.picpos = vIn.picpos;
	return vOut;
}
GS_OUT calculate(float2 pos,float2 tex,float2 texX,float2 texY)
{
	GS_OUT output;
	output.posH = float4(pos,1,1);
	
	
	
	//davis 80*80
	//output.posH = mul(output.posH, worldMatrix);
    //output.posH = mul(output.posH, viewMatrix);
    //output.posH = mul(output.posH, projectionMatrix);
	// Store the texture coordinates for the pixel shader.
	output.texcoord = tex;
	//output.texcoord+=float2(-0.015,);
    // Compute texture coordinates for first noise texture using the first scale and upward scrolling speed values.
	output.texCoords1 = (tex * scales.x);
	output.texCoords1.y = output.texCoords1.y + (frameTime * scrollSpeeds.x);
	

    // Compute texture coordinates for second noise texture using the second scale and upward scrolling speed values.
	output.texCoords2 = (tex * scales.y);
	output.texCoords2.y = output.texCoords2.y + (frameTime * scrollSpeeds.y);
	
    // Compute texture coordinates for third noise texture using the third scale and upward scrolling speed values.
	output.texCoords3 = (tex * scales.z);
	output.texCoords3.y = output.texCoords3.y + (frameTime * scrollSpeeds.z);
	
	output.texX = texX;
	output.texY = texY;
	
    return output;
}

[maxvertexcount (6)]
void gs_main(point VS_OUT input[1], inout TriangleStream<GS_OUT> triStream)
{
	float2 texsize = float2(1.0f/input[0].picpos.z, 1.0f/input[0].picpos.w);
	float2 newTex;
	
	float2 offset = float2(-1,1);
	float2 viewport = float2(1024,1024);
	
	float2 size = float2(256.0f,-256.0f);
   
	float2 lt,ld,rt,rd;
	
	float2 texX,texY;
	
	//float2 texOffset = float2(texsize.x*(-0.25),texsize.y*(-0.5));
	float2 texOffset = float2((texsize.x/-2.0f),(texsize.y/-2.0f));
	lt = float2(-1,1);
	ld = float2(-1,-1);
	rt = float2(1,1);
	rd = float2(1,-1);
	/*
	
	lt = float2((input[0].pos.x-1)*size.x,(input[0].pos.y-1)*size.y)*2/(viewport)+offset ;
	ld= float2((input[0].pos.x-1)*size.x,(input[0].pos.y-1)*size.y+size.y)*2/(viewport)+offset  ;
	rt = float2((input[0].pos.x-1)*size.x+size.x,(input[0].pos.y-1)*size.y)*2/(viewport)+offset ;
	rd = float2((input[0].pos.x-1)*size.x+size.x,(input[0].pos.y-1)*size.y+size.y)*2/(viewport)+offset ;
	*/
	texX[0] = texsize.x*(input[0].picpos.x-1);
	texX[1] = texsize.x*(input[0].picpos.x);
	texY[0] = texsize.y*(input[0].picpos.y-1);
	texY[1] = texsize.y*(input[0].picpos.y);
	
	GS_OUT out5;
	
	//newTex = float2(1,0);
	newTex = float2( texX[1]+texsize.x, texY[0] );
	newTex += texOffset;
	out5 = calculate(rt,newTex,texX,texY);
	triStream.Append( out5 );
	
	//newTex = float2(1,1);
	newTex = float2( texX[1]+texsize.x, texY[1]+texsize.y );
	newTex += texOffset;
	out5 = calculate(rd,newTex,texX,texY);
	triStream.Append( out5 );
	
	//newTex = float2(0,0);
	newTex = float2( texX[0], texY[0] );
	newTex += texOffset;
	out5 = calculate(lt,newTex,texX,texY);
	triStream.Append( out5 );
	
	//newTex = float2(1,1);
	newTex = float2( texX[1]+texsize.x, texY[1]+texsize.y );
	newTex += texOffset;
	out5 = calculate(rd,newTex,texX,texY);
	triStream.Append( out5 );
	
	//newTex = float2(0,0);
	newTex = float2( texX[0], texY[0] );
	newTex += texOffset;
	out5 = calculate(lt,newTex,texX,texY);
	triStream.Append( out5 );
	
	//newTex = float2(0,1);
	newTex = float2( texX[0], texY[1]+texsize.y );
	newTex += texOffset;
	out5 = calculate(ld,newTex,texX,texY);
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
    noise1 = (noise1 - 0.5f) * 2.0f;
    noise2 = (noise2 - 0.5f) * 2.0f;
    noise3 = (noise3 - 0.5f) * 2.0f;

	// Distort the three noise x and y coordinates by the three different distortion x and y values.
	float2 t1,t2,t3;
	t1 = float2(0.0035f, 0.009f);
	t2 = float2(0.005f, 0.017f);
	t3 = float2(0.006f, 0.023f);
	noise1.xy = noise1.xy * t1.xy;//distortion1.xy;
	noise2.xy = noise2.xy * t2.xy;//distortion2.xy;
	noise3.xy = noise3.xy * t3.xy;//distortion3.xy;

	// Combine all three distorted noise results into a single noise result.
	finalNoise = noise1 + noise2 + noise3;
	/*finalNoise.x *= 0.5;
	finalNoise.y *= 0.05;*/
	// Perturb the input texture Y coordinates by the distortion scale and bias values.  
	// The perturbation gets stronger as you move up the texture which creates the flame flickering at the top effect.
	perturb = ((1.0f - pIn.texcoord.y) * distortionScale) + distortionBias;

	// Now create the perturbed and distorted texture sampling coordinates that will be used to sample the fire color texture.
	noiseCoords.xy = (finalNoise.xy * perturb) + pIn.texcoord.xy;

	//if (noiseCoords.y < pIn.texcoord.y)
		//discard;
	// Sample the color from the fire texture using the perturbed and distorted texture sampling coordinates.
	// Use the clamping sample state instead of the wrap sample state to prevent flames wrapping around.
    fireColor = fireTexture.Sample(SampleType2, noiseCoords.xy);

	// Sample the alpha value from the alpha texture using the perturbed and distorted texture sampling coordinates.
	// This will be used for transparency of the fire.
	// Use the clamping sample state instead of the wrap sample state to prevent flames wrapping around.
    alphaColor = alphaTexture.Sample(SampleType2, noiseCoords.xy);
	
	if( (!(noiseCoords.x >= pIn.texX[0] && noiseCoords.x <= pIn.texX[1])) ||
		(!(noiseCoords.y >= pIn.texY[0] && noiseCoords.y <= pIn.texY[1]))  )
	{
		alphaColor.r = 0.0f;
		alphaColor.g = 0.0f;
		alphaColor.b = 0.0f;
		alphaColor.a = 1.0f;
	}

	
	if(alphaColor.a == 0.0)
	{
		alphaColor.r = 0.0f;
		alphaColor.g = 0.0f;
		alphaColor.b = 0.0f;
		alphaColor.a = 1.0f;
	}
	// Set the alpha blending of the fire to the perturbed and distored alpha texture value.
	fireColor.a = alphaColor;
	//fireColor.a = (alphaColor.r + alphaColor.g + alphaColor.b + alphaColor.a)/4;
	noise2 = alphaTexture.Sample(SampleType, pIn.texcoord);
	//
	if( (!(pIn.texcoord.x >= pIn.texX[0] && pIn.texcoord.x <= pIn.texX[1])) ||
		(!(pIn.texcoord.y >= pIn.texY[0] && pIn.texcoord.y <= pIn.texY[1]))  )
	{
		noise2.r = 0.0f;
		noise2.g = 0.0f;
		noise2.b = 0.0f;
		noise2.a = 0.0f;
	}
	//
		fireColor.r = (noise2.r*(1-fireColor.a)+fireColor.r*fireColor.a);
		fireColor.g = (noise2.g*(1-fireColor.a)+fireColor.g*fireColor.a);
		fireColor.b = (noise2.b*(1-fireColor.a)+fireColor.b*fireColor.a);
	fireColor.a = max(noise2.a , fireColor.a);
	
    return fireColor;
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