#include "StdGame.h"
#include "FireShaderClass.h"
#include <cstdarg>

FireShaderClass::FireShaderClass() : EffectShaderClass(),m_frameTime(0),m_scrollSpeeds(0),m_scales(0),
	m_distortion1(0),m_distortion2(0),m_distortion3(0),m_distortionScale(0),m_distortionBias(0),
	m_fireTexture(0),m_noiseTexture(0),m_alphaTexture(0)
{

}

void FireShaderClass::Render()
{
	UINT offset = 0;
	UINT stride2 = sizeof(Vertex);
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_deviceContext->IASetInputLayout(m_layout);
	m_deviceContext->IASetVertexBuffers(0, 1, &m_Buffer, &stride2, &offset);
	m_PTech->GetPassByIndex(0)->Apply(0, m_deviceContext);


	for (DrawVertexGroups::iterator it = m_dvg.begin();it != m_dvg.end();++it)
	{
		m_alphaTexture->SetResource(it->texture->texture);
		m_PTech->GetPassByIndex(0)->Apply(0, m_deviceContext);
		m_deviceContext->Draw(it->VertexCount, it->StartVertexLocation);
	}
}

void FireShaderClass::Update( float dt )
{
	m_frameTime->SetFloat(dt);
}

void FireShaderClass::SetEffectVariableByName()
{
	m_fireTexture = m_Effect->GetVariableByName("fireTexture")->AsShaderResource();
	m_noiseTexture = m_Effect->GetVariableByName("noiseTexture")->AsShaderResource();
	m_alphaTexture = m_Effect->GetVariableByName("alphaTexture")->AsShaderResource();
	m_frameTime = m_Effect->GetVariableByName("frameTime")->AsScalar();
	m_scrollSpeeds = m_Effect->GetVariableByName("scrollSpeeds");
	m_scales = m_Effect->GetVariableByName("scales");
	m_distortion1 = m_Effect->GetVariableByName("distortion1");
	m_distortion2 = m_Effect->GetVariableByName("distortion2");
	m_distortion3 = m_Effect->GetVariableByName("distortion3");
	m_distortionScale = m_Effect->GetVariableByName("distortionScale")->AsScalar();
	m_distortionBias = m_Effect->GetVariableByName("distortionBias")->AsScalar();
}

void FireShaderClass::CreateTexture()
{
	m_fire = Texture_Sptr(new Texture(L"Media\\fire01.dds"));
	m_noise = Texture_Sptr(new Texture(L"Media\\noise01.dds"));
	m_fireTexture->SetResource(m_fire->texture);
	m_noiseTexture->SetResource(m_noise->texture);
}
/*
void FireShaderClass::SetShaderParameters( D3DXVECTOR3 scrollSpeeds, D3DXVECTOR3 scales, D3DXVECTOR2 distortion1, D3DXVECTOR2 distortion2, D3DXVECTOR2 distortion3, float distortionScale, float distortionBias )
{
	m_scrollSpeeds->SetRawValue(scrollSpeeds,0,sizeof(float)*3);
	m_scales->SetRawValue(scales,0,sizeof(float)*3);
	m_distortion1->SetRawValue(distortion1,0,sizeof(float)*2);
	m_distortion2->SetRawValue(distortion2,0,sizeof(float)*2);
	m_distortion3->SetRawValue(distortion3,0,sizeof(float)*2);
	m_distortionScale->SetFloat(distortionScale);
	m_distortionBias->SetFloat(distortionBias);
}
*/
void FireShaderClass::SetShaderParameters(int i, ... )
{
	va_list num_list; 

	va_start(num_list, i); 

	m_scrollSpeeds->SetRawValue(va_arg(num_list, D3DXVECTOR3),0,sizeof(float)*3);
	m_scales->SetRawValue(va_arg(num_list, D3DXVECTOR3),0,sizeof(float)*3);
	m_distortion1->SetRawValue(va_arg(num_list, D3DXVECTOR2),0,sizeof(float)*2);
	m_distortion2->SetRawValue(va_arg(num_list, D3DXVECTOR2),0,sizeof(float)*2);
	m_distortion3->SetRawValue(va_arg(num_list, D3DXVECTOR2),0,sizeof(float)*2);
	m_distortionScale->SetFloat(va_arg(num_list, float));
	m_distortionBias->SetFloat(va_arg(num_list, float));

	va_end(num_list);
}
