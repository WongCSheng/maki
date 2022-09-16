#include <iostream>
#include <GLFW\glfw3.h>
#include "App.h"

using namespace std;

int main(int argc, char** argv)
{
	App::Instance().Start();
	App::Instance().Run();

	return 0;
}