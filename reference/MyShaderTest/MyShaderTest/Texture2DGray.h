#ifndef _TEXTURE_2D_GRAY_H_
#define _TEXTURE_2D_GRAY_H_
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include "Dx11DemoBase.h"
class TextureGray : public Dx11DemoBase
{
    public:
		TextureGray();
		virtual ~TextureGray();
		//
		bool LoadShader();
		bool SetTexture(ID3D11ShaderResourceView*);
		//

		bool LoadContent( );
		void UnloadContent( );

		void Update( float dt );
		void Render( );

	private:
		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;
		ID3D11InputLayout* m_layout;
		ID3D11Buffer* vertexBuffer_;


		ID3D11ShaderResourceView* colorMap_;
		ID3D11SamplerState* colorMapSampler_;
};
#endif