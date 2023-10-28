//Readme: This project is licensed under the terms of the MIT license.
//Author: Parcode

#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;

class GraphicsEngine
{
public:
	GraphicsEngine();
	
	//initilize GraphicsEngine
	bool init();

	//release all resources
	bool release();

	~GraphicsEngine();

public:
	SwapChain* createSwapChain();
	DeviceContext* getImmidiateDeviceContext();
private:
	DeviceContext* m_imm_device_context;

public:
	static GraphicsEngine* get();

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
private:
	friend class SwapChain;


};

