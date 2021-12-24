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

		// Annotation : 그래픽 카드에 남기는 주석
		Microsoft::WRL::ComPtr<ID3DUserDefinedAnnotation> m_d3dAnnotation;

		Microsoft::WRL::ComPtr<ID3D11Texture2D>			  m_renderTarget;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			  m_depthStencil;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	  m_d3dRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	  m_d3dDepthStencilView;

		D3D11_VIEWPORT	  m_screenViewport;
		DXGI_FORMAT		  m_backBufferFormat;
		DXGI_FORMAT		  m_depthBufferFormat;
		UINT			  m_backBufferCount;
		D3D_FEATURE_LEVEL m_d3dFeatureLevel;

		HWND			  m_window;
		D3D_FEATURE_LEVEL m_d3dMinFeatureLevel;
		RECT			  m_outputSize;

		// Color Space : 
		DXGI_COLOR_SPACE_TYPE m_colorSpace;
		unsigned int		  m_options;

		// Interface
		IDeviceNotify*		  m_deviceNotify;

	public:
		static const unsigned int c_FlipPresent = 0x01;
		static const unsigned int c_AllowTearing = 0x2;
		static const unsigned int c_EnableHDR = 0x04;

	private:
		void CreateFactory();
		void GetHardwareAdapter(IDXGIAdapter1** ppAdapter);
		void UpdateColorSpace();

	public:
		DeviceResources(DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM,
			DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D32_FLOAT,
			UINT backBufferCount = 2,
			D3D_FEATURE_LEVEL minFeatureLevel = D3D_FEATURE_LEVEL_10_0,
			unsigned int flags = c_FlipPresent) noexcept;

		// ComPtr의 사용으로 소멸자를 생성하지 않음
		// 필요한 코드 정보만 제공하여 협업 효율 증대 효과
		~DeviceResources() = default;

		// DeviceResources&& -> R-vaule 참조
		DeviceResources(DeviceResources&&) = default;
		DeviceResources& operator =(DeviceResources&&) = default;

		DeviceResources(DeviceResources const&) = delete;
		DeviceResources& operator = (const DeviceResources&) = delete;
	public:
		void CreateDeviceResources();
		void CreateWindowSizeDependentResources();
		void SetWindow(HWND window, int width, int height) noexcept;
		bool WindowSizeChanged(int width, int height);
		void HandleDeviceLost();
		void RegisterDeviceNotify(IDeviceNotify* deviceNotify) noexcept
		{
			m_deviceNotify = deviceNotify;
		}

		void Present();

	public:
		RECT GetOutputSize() const noexcept { return m_outputSize; }

		// C++ 14
		// ID3DDeivce* GetD3DDevice() const noexcept { return m_d3dDevice.Get(); }
		auto GetD3DDevice() const noexcept { return m_d3dDevice.Get(); }
		auto GetD3DDeivceContext() const noexcept { return m_d3dDeviceContext.Get(); }
		auto GetSwapChain() const noexcept { return m_d3dSwapChain.Get(); }
		auto GetWindow() const noexcept { return m_window; }
		auto GetDeviceFeatureLevel() const noexcept{ return m_d3dFeatureLevel; }
		auto GetRenderTarget() const noexcept { return m_renderTarget.Get(); }
		auto GetDepthStencil() const noexcept { return m_depthStencil.Get(); }
		auto GetRenderTargetView() const noexcept { return m_d3dRenderTargetView.Get(); }
		auto GetDepthStencilView() const noexcept { return m_d3dDepthStencilView.Get(); }
		auto GetBackBufferFormat() const noexcept { return m_backBufferFormat; }
		auto GetDepthBufferFormant() const noexcept { return m_depthBufferFormat; }
		auto GetScreenViewport() const noexcept { return m_screenViewport; }
		auto GetColorSpace() const noexcept { return m_colorSpace; }
		auto GetDeviceOptions() const noexcept { return m_options; }

	public:
		void PIXBeginEvent(_In_z_ const wchar_t* name)
		{
			m_d3dAnnotation->BeginEvent(name);
		}
		void PIXEndEveint()
		{
			m_d3dAnnotation->EndEvent();
		}

		void PIXSetMarker(_In_z_ const wchar_t* name)
		{
			m_d3dAnnotation->SetMarker(name);
		}
	};
}