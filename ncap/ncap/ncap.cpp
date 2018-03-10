#include <windows.h>
#include "CNCapApp.h"
#include "CPrevWnd.h"

int main(void) {

	srand(GetTickCount());

	CNCapApp app;
	app.SetParam((HINSTANCE)GetModuleHandle(0), 0, 0, 0);
	CPrevWnd::RegisterClass();

	if (app.Init()) {
		app.Run();
	}
	return 0;
}