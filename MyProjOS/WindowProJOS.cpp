#include "WindowProJOS.h"
#include "WindowMainProjOS.h"

WindowProJOS::WindowProJOS()
{
    this->Commandinput();
}

WindowProJOS::~WindowProJOS()
{
}

void WindowProJOS::Commandinput()
{
    string input;
    cout << "user@ : ";
    getline(cin, input);
    vector<string> words = HandleInput(input);
    this->Commandsystem(words);
}

vector<string> WindowProJOS::HandleInput(string input)
{
    vector<string> words;
    string word = "";

    for (char c : input) {
        if (c == ' ') {
            words.push_back(word);
            word = "";
        }
        else {
            word += c;
        }
    }

    if (word != "") {
        words.push_back(word);
    }

    return words;
}

void WindowProJOS::Commandsystem(vector<string> words)
{
    if (words.empty()) {
        this->Commandinput();
        return;
    }

    if (words[0] == "login") {
        if (words.size() < 2) {
            cout << "Invalid login command. Please enter 'login -h' to proceed.\n";
            this->Commandinput();
            return;
        }
        if (words[1] == "-u" && words.size() < 3) {
            this->LoginFuncUser();
            return;
        }
        else if (words[1] == "-h" && words.size() < 3) {
            this->HelpLogin();
        }
    }

    else if (words[0] == "exit" && words.size() < 2) {
        exit(0);
    }

    else if (words[0] == "clear" && words.size() < 2) {
        this->clearScreen();
        this->Commandinput();
        return;
    }

    else {
        this->Commandinput();
        return;
    }
    this->Commandinput();
}

void WindowProJOS::HelpLogin()
{
    cout << "HELP FUNC LOGIN\n";
    cout << "-h to call the function\n";
    cout << "-u to login to user\n";
}

void WindowProJOS::LoginLOGO()
{
    cout << "------------------" << endl;
    cout << "|  _   _  o ._" << endl;
    cout << "| (_) (_| | | | " << endl;
    cout << "       _|      " << endl;
    cout << "------------------" << endl;
}

string WindowProJOS::LoginFuncUser()
{
    string user;
    this->clearScreen();
    this->LoginLOGO();
    cout << "Please enter your user: ";
    cin >> user;
    this->LoginFuncPassword(user);
    return user;
}

void WindowProJOS::LoginFuncPassword(string user)
{
    string password;
    cout << "Please enter your password: ";

#ifdef _WIN32
    while (true) {
        char ch = _getch();
        if (ch == '\r') break;
        if (ch == ' ') {
            this->clearScreen();
            cout << "*Receiving password incorrectly*\n";
            LoginLOGO();
            cout << "Please enter your user : " << user << endl;
            password.clear();
            cout << "Please enter password again: ";
            continue;
        }
        if (ch == '\b' && !password.empty()) {
            password.pop_back();
            cout << "\b \b";
        }
        else {
            password.push_back(ch);
            cout << "*";
        }
    }
#else
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch;
    while (true) {
        ch = getchar();
        if (ch == '\n') break;
        password.push_back(ch);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    cout << endl;
    this->ChackPassword(); 
}

void WindowProJOS::ChackPassword()
{
    this->clearScreen();
    WindowMainProjOS mainOS(this);
#ifdef _WIN32
    cin.ignore();
#else
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif // _WIN32
    mainOS.ChaOS();
    mainOS.getUserInput();
}

void WindowProJOS::Logout()
{
    this->clearScreen();
    this->Commandinput();
}

void WindowProJOS::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}