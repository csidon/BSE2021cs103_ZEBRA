#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <Windows.h>

using namespace std;

//function prototype
BOOL initConsole();
void makePretty();

int main()
{

	initConsole();
	cout << "123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x123456789x";
	makePretty();

}

void makePretty()
{
	cout << "\n   +";
	for (int i = 0; i < 62; i++)
	{
		cout << "-";
	}
	cout << "+   \n";
}

BOOL initConsole()
{
	handle_t hStdin = GetStdHandle(STD_INPUT_HANDLE);
	handle_t hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT windowSize = { 0, 0, 69, 47 };

	// Change the console window size:
	SetConsoleWindowInfo(hStdout, TRUE, &windowSize);

	COORD c = { 70, 50 };
	return true;
}