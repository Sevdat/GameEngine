//Readme: This project is licensed under the terms of the MIT license.
//Author: Pardcode

#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h" 

//struct vec3 { float x, y, z; };

struct vertex { 
    Vector3D position; 
    Vector3D position1;
    Vector3D color;
    Vector3D color1;
};

__declspec(align(16))
struct constant {
    Matrix4x4 m_world;
    Matrix4x4 m_view;
    Matrix4x4 m_proj;
    unsigned int m_time;
};

AppWindow::AppWindow() {
}

void AppWindow::updateQuadPosition()
{
    constant cc;
    cc.m_time = ::GetTickCount();

    m_delta_pos += m_delta_time / 10.0f;

    if (m_delta_pos > 1.0f)  m_delta_pos = 0;

    Matrix4x4 temp;

   // cc.m_world.setTranslation(Vector3D::lerp(
   //     Vector3D(-2,-2,0), Vector3D(2, 2, 0), m_delta_pos));

    m_delta_scale += m_delta_time / 0.15f;

    cc.m_world.setTranslation(Vector3D::lerp(
        Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), 
        m_delta_pos
    ));

    temp.setScale(Vector3D::lerp(
        Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), 
        (sin(m_delta_scale) + 1.0f)/2.0f
    ));
    cc.m_world *= temp;

    cc.m_view.setIdentity();
    cc.m_proj.setOrthoLH(
        (
            this->getClientWindowRect().right -
            this->getClientWindowRect().left
            ) / 400.0f,
        (
            this->getClientWindowRect().bottom -
            this->getClientWindowRect().top
            ) / 400.0f,
        -4.0f, 4.0f
    );
    m_cb->update(GraphicsEngine::get()->
        getImmidiateDeviceContext(), &cc);
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
 /* POS 1 */ {
     Vector3D(-0.5f,-0.5f,0.0f),    /* position  */
     Vector3D(-0.32f,-0.11f,0.0f),  /* position1 */
     Vector3D(0,0,0),               /* color     */
     Vector3D(0,1,0)                /* color1    */
 },
 /* POS 2 */ {
     Vector3D(-0.5f,0.5f,0.0f),     /* position  */
     Vector3D(-0.11f,0.78f,0.0f),   /* position1 */
     Vector3D(1,1,0),               /* color     */
     Vector3D(0,1,1)                /* color1    */
 },
 /* POS 3 */ { 
     Vector3D(0.5f,-0.5f,0.0f),     /* position  */
     Vector3D(0.75f,-0.73f,0.0f),   /* position1 */
     Vector3D(0,0,1),               /* color     */
     Vector3D(1,0,0)                /* color1    */
 },
 /* POS 4 */ { 
     Vector3D(0.5f,0.5f,0.0f),       /* position  */
     Vector3D(0.88f,0.77f,0.0f),     /* position1 */
     Vector3D(1,1,1),                /* color     */
     Vector3D(0,0,1)                 /* color1    */
 }
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

    updateQuadPosition();
   // constant cc;
   // cc.m_time = ::GetTickCount();

   // m_cb->update(GraphicsEngine::get()->
   //     getImmidiateDeviceContext(), &cc);

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

    m_old_delta = m_new_delta;
    m_new_delta = ::GetTickCount();

    m_delta_time = (m_old_delta) ? (
        (m_new_delta - m_old_delta) / 1000.0f) : 0;

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



