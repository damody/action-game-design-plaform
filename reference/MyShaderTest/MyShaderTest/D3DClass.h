#ifndef _D3DCLASS_H
#define _D3DCLASS_H

#include<d3d11.h>
#include<d3dx11.h>
#include<DxErr.h>
#include <d3dx10math.h>

class D3DClass
{
    public:
        D3DClass();
        ~D3DClass();

        bool Initialize( HWND hwnd );
        void Shutdown( );

		void BeginScene(float, float, float, float);
		void EndScene();

		//
		void SetRenderToBackBuffer();
		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();
		IDXGISwapChain* GetSwapChain();
		ID3D11RenderTargetView* GetBackBufferTarget();
		void GetProjectionMatrix(D3DXMATRIX&);
		void GetWorldMatrix(D3DXMATRIX&);
		void GetOrthoMatrix(D3DXMATRIX&);

		void TEST(int w,int h,ID3D11RenderTargetView* rtv);

	private:
		void SetMatrix(int ,int ,float ,float);
    private:
        HWND hwnd_;

        D3D_DRIVER_TYPE driverType_;
        D3D_FEATURE_LEVEL featureLevel_;

        ID3D11Device* d3dDevice_;
        ID3D11DeviceContext* d3dContext_;
        IDXGISwapChain* swapChain_;
		ID3D11RenderTargetView* backBufferTarget_;

		//
		D3DXMATRIX m_projectionMatrix;
		D3DXMATRIX m_worldMatrix;
		D3DXMATRIX m_orthoMatrix;
		//

        
};

#endif