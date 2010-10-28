#include "includes.h"

int main(int argc, char** argv) {
	Application app;
	app.Initialize();
	app.Run();
	app.Terminate();

	return 0;
}
