#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "window.h"
#include "filehandling.h"


int main(int argc, char* argv[])
{
	Window window = Window();

	setWindowFromFile(fileParameters::FILE_NAME, window);

	addGameObjectsFromFile(fileParameters::FILE_NAME, window);

	window.Run();

	return 0;
}

