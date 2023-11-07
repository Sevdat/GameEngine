//Readme: This project is licensed under the terms of the MIT license.
//Author: Pardcode


#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow: public Window
{
public:
	AppWindow();

    void updateQuadPosition();

	~AppWindow();

	// Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;
private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
    VertexShader* m_vs;
    PixelShader* m_ps;
    ConstantBuffer* m_cb;
private:
    float m_old_delta;
    float m_new_delta;
    float m_delta_time;

    float m_delta_pos;
    float m_delta_scale;

};

