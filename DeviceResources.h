#pragma once

namespace DX
{
	// Pure virtual function : 선언만 있고 정의가 없는 함수
	// Abstract class : 하나 이상의 순수 가상함수를 가진 클래스
	// Interface : 모든 함수가 순수 가상함수로 이루어진 구조체 (MS 전용)

	interface IDeviceNotify
	{
		virtual void OnDeviceLost() = 0;
		virtual void OnDeviceRestored() = 0;

	protected:
		~IDeviceNotify() = default;
	};

	class DeviceResources
	{
	private:
		Microsoft::WRL::ComPtr<IDXGIFactory2>			  m_dxgiFactory;
		Microsoft::WRL::ComPtr<ID3D11Device1>			  m_d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext1>	  m_d3dDeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain1>			  m_d3dSwapChain;
		Microsoft::WRL::ComPtr<ID3DUserDefinedAnnotation> m_d3dAnnotation;

		Microsoft::WRL::ComPtr<ID3D11Texture2D>			  m_renderTarget;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			  m_depthStencil;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	  m_d3dRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	  m_d3dDepthStencilView;

		D3D11_VIEWPORT	m_screenViewport;
		DXGI_FORMAT		m_backBufferFormat;
		DXGI_FORMAT		m_depthBufferFormat;
		UINT			m_backBufferCount;

		HWND			  m_window;
		D3D_FEATURE_LEVEL m_d3dFeatureLevel;
		RECT			  m_outputSize;

		DXGI_COLOR_SPACE_TYPE m_colorSpace;
		unsigned int		  m_options;

		IDeviceNotify*		  m_deviceNotify;
	};
}