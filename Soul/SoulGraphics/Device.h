#pragma once

namespace SoulGraphics
{
	class Device
	{
	public:
		Device();
		~Device();

		void Initialize(HWND hwnd, UINT width, UINT height);
		void Finalize();

		ID3D11Device* GetDevice()const { return _device; }
		ID3D11DeviceContext* GetDeviceContext()const { return _deviceContext; }
		IDXGISwapChain* GetSwapChain()const { return _swapChain; }

	private:
		ID3D11Device* _device;
		ID3D11DeviceContext* _deviceContext;
		IDXGISwapChain* _swapChain;
	};
}

