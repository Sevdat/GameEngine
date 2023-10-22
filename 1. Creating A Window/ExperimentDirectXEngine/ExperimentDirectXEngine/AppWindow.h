//Readme: This project is licensed under the terms of the MIT license.
//Author: Parcode


#pragma once
#include "Window.h"

class AppWindow: public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;
};

