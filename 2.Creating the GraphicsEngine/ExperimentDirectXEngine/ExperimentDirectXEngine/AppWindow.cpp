//Readme: This project is licensed under the terms of the MIT license.
//Author: Parcode

#include "AppWindow.h"


AppWindow::AppWindow() {
}

AppWindow::~AppWindow() {

}

void AppWindow::onCreate()
{
	//Window::onCreate();
	GraphicsEngine::get()->init();
}

void AppWindow::onUpdate()
{
	//Window::onUpdate();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	GraphicsEngine::get()->release();
}



