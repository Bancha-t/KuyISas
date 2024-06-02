#ifndef WINDOWMAINPROJOS_H
#define WINDOWMAINPROJOS_H

#define COLOR_RED     "\x1b[31m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class WindowProJOS;  

class WindowMainProjOS {
public:
    WindowMainProjOS(WindowProJOS* mainSystem);
    ~WindowMainProjOS();
    string getUserInput();
    void ChaOS();
private:
    string OSname = "user";
    WindowProJOS* mainSystem;
    vector<string> HandleInputMainOS(string);
    void Commandsystem(vector<string>);
    void ChackCallSystem(vector<string>, string);
};

#endif // WINDOWMAINPROJOS_H