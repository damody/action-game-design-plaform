--Shader 路徑
ShaderPath = "shader\\FireShaderScale.fx";
--Texture 最多5張
TexturePath =
{
	fireTexture,
	noiseTexture
};
TexturePath.fireTexture = "Media\\fire01.dds";
TexturePath.noiseTexture = "Media\\noise01.dds";
--Shader的參數
ShaderParameters =
{
	scrollSpeeds = {},
	scales = {},
	distortion1 = {},
	distortion2 = {},
	distortion3 = {},
	distortionScale = {},
	distortionBias = {}
};
ShaderParameters.scrollSpeeds =
{
	type = "float3",
	x = 1.0,
	y = 2.0,
	z = 5.0
};
ShaderParameters.scales =
{
	type = "float3",
	x = 20.0,
	y = 30.0,
	z = 40.0
};
ShaderParameters.distortion1 =
{
	type = "float2",
	x = 0.03,
	y = 0.07
};
ShaderParameters.distortion2 =
{
	type = "float2",
	x = 0.02,
	y = 0.05
};
ShaderParameters.distortion3 =
{
	type = "float2",
	x = 0.01,
	y = 0.1
};
ShaderParameters.distortionScale =
{
	type = "float",
	x = 1.2
};
ShaderParameters.distortionBias =
{
	type = "float",
	x = 1.2
};
