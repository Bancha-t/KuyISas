#ifndef WINDOWPROJOS_H
#define WINDOWPROJOS_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <iomanip>

#ifdef _WIN32
#include <conio.h>

#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

class WindowMainProjOS;

class WindowProJOS
{
public:
	WindowProJOS();
	virtual ~WindowProJOS();
	void Logout();
private:
	vector<string> HandleInput(string);
	void Commandinput();
	void Commandsystem(vector<string>);
	void HelpLogin();
	void LoginLOGO();
	string LoginFuncUser();
	void LoginFuncPassword(string);
	bool ChackPassword(string,string);
	void loginsuccess();
	void clearScreen();
	string hashPassword(const string&);
};

#endif // WINDOWPROJOS_H