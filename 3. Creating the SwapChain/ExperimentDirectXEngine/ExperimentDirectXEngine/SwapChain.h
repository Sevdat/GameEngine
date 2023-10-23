//Readme: This project is licensed under the terms of the MIT license.
//Author: Parcode

#pragma once
#include <d3d11.h>

class SwapChain
{
public:
	SwapChain();

	//initilize SwapChain for a window
	bool init(HWND hwnd, UINT width, UINT height);

	//release all resources for that window
	bool release();

	~SwapChain();

private:
	IDXGISwapChain* m_swap_chain;
};

