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
    char* passInput = getpass("");
    password = passInput;
#endif

    cout << endl;
    string userhash = this->hashPassword(user);
    string passwordhash = this->hashPassword(password);
    this->ChackPassword(userhash, passwordhash);
    bool passwordinfile = ChackPassword(userhash, passwordhash);
    if (passwordinfile == true) {
        this->loginsuccess();
    }
    else {
        cin.ignore();
        this->clearScreen();
        this->Commandinput();
    }

}

bool WindowProJOS::ChackPassword(string username, string password)
{
    ifstream userPasswordFile("password.txt");
    string userPasswordLine;
    while (getline(userPasswordFile, userPasswordLine)) {
        istringstream iss(userPasswordLine);
        string storedUsername, storedPassword;

        if (iss >> storedUsername >> storedPassword) {
            if (storedUsername == username && storedPassword == password) {
                userPasswordFile.close();
                return true;
            }
        }
    }
    userPasswordFile.close();
    return false;
}

void WindowProJOS::loginsuccess()
{
    this->clearScreen();
    WindowMainProjOS mainOS(this);
#ifdef _WIN32
    cin.ignore();
#else
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

string WindowProJOS::hashPassword(const string& userpassword)
{
    hash<string> hasher;
    size_t hash = hasher(userpassword);
    return to_string(hash);
}
