//Readme: This project is licensed under the terms of the MIT license.
//Author: Parcode


#include "AppWindow.h"


int main() {
	AppWindow app;
	if (app.init()) {
		while (app.isRun()){
			app.broadcast();
		}
	
	}

	return 0;
}


