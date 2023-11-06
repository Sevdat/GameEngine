//Readme: This project is licensed under the terms of the MIT license.
//Author: Pardcode

#include "AppWindow.h"
#include <Windows.h>

struct vec3 { float x, y, z; };

struct vertex { 
    vec3 position; 
    vec3 position1;
    vec3 color;
    vec3 color1;
};

__declspec(align(16))
struct constant {
    unsigned int m_time;
};

AppWindow::AppWindow() {
}

AppWindow::~AppWindow() {

}

void AppWindow::onCreate()
{
	//Window::onCreate();  
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(
		this->m_hwnd,
		rc.right - rc.left,
		rc.bottom - rc.top
	);

	vertex list[] = {
			/*    position,          position1,     color  color1 */
 /* POS 1 */ {-0.5f,-0.5f,0.0f, -0.32f,-0.11f,0.0f, 0,0,0, 0,1,0 },
 /* POS 2 */ {-0.5f,0.5f,0.0f,  -0.11f,0.78f,0.0f,  1,1,0, 0,1,1 },
 /* POS 3 */ { 0.5f,-0.5f,0.0f,  0.75f,-0.73f,0.0f, 0,0,1, 1,0,0 },
 /* POS 4 */ { 0.5f,0.5f,0.0f,   0.88f,0.77f,0.0f,  1,1,1, 0,0,1 }
	};

    m_vb = GraphicsEngine::get()->createVertexBuffer();
    UINT size_list = ARRAYSIZE(list);
   // GraphicsEngine::get()->createShaders();
    void* shader_byte_code = nullptr;
    size_t size_shader = 0;
    GraphicsEngine::get()->compileVertexShader(
        L"VertexShader.hlsl", "vsmain", &shader_byte_code,
        &size_shader
    );
    m_vs = GraphicsEngine::get()->createVertexShader(
        shader_byte_code, size_shader
    );
    m_vb->load(list, sizeof(vertex), size_list,
        shader_byte_code, size_shader
    );
    GraphicsEngine::get()->releaseCompiledShader();
    GraphicsEngine::get()->compilePixelShader(
        L"PixelShader.hlsl", "psmain", &shader_byte_code,
        &size_shader
    );
    m_ps = GraphicsEngine::get()->createPixelShader(
    shader_byte_code, size_shader
    );
    //   GraphicsEngine::get()->getShaderBufferAndSize(
    //       &shader_byte_code, &size_shader
    //   );
    GraphicsEngine::get()->releaseCompiledShader(); 

    constant cc;
    cc.m_time = 0;
    m_cb = GraphicsEngine::get()->createConstantBuffer();
    m_cb->load(&cc, sizeof(constant));


}

void AppWindow::onUpdate()
{
    //Window::onUpdate();  //dif
    //Clear the render target
    GraphicsEngine::get()->getImmidiateDeviceContext()->
        clearRenderTargetColor(this->m_swap_chain,
            0, 0.3f, 0.4f, 1
        );
    //Set viewport of the render target in which we have to draw
    RECT rc = this->getClientWindowRect();
    GraphicsEngine::get()->getImmidiateDeviceContext()->
        setViewportSize(
            rc.right - rc.left,
            rc.bottom - rc.top
        );

    constant cc;
    cc.m_time = ::GetTickCount();

    m_cb->update(GraphicsEngine::get()->
        getImmidiateDeviceContext(), &cc);

    GraphicsEngine::get()->getImmidiateDeviceContext()->
        setConstantBuffer(m_vs, m_cb);
    GraphicsEngine::get()->getImmidiateDeviceContext()->
        setConstantBuffer(m_ps, m_cb);

    //Set default shader in the graphics pipeline to be able to draw
 //   GraphicsEngine::get()->setShaders();
    GraphicsEngine::get()->getImmidiateDeviceContext()->
        setVertexShader(m_vs);
    GraphicsEngine::get()->getImmidiateDeviceContext()->
        setPixelShader(m_ps);

    //Set the vertices of the triangle to draw
    GraphicsEngine::get()->getImmidiateDeviceContext()->
        setVertexBuffer(m_vb);
    //Finally draw the triangle
    GraphicsEngine::get()->getImmidiateDeviceContext()->
        drawTriangleStrip(m_vb->getSizeVertexList(), 0);

    m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
    m_vb->release();
	m_swap_chain->release();
    m_vs->release();
    m_ps->release();
	GraphicsEngine::get()->release();

}



