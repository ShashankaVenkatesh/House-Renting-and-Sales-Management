#include <windows.h>

// Name of the window class
const char g_szClassName[] = "myWindowClass";

// Step 4: the Window Procedure
// THE BRAIN OF THE PROGRAM
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    // WNDCLASSEX is the Windows class C structure
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    // Step 1: Registering the Window Class
    
    // Assigning values to all the attributes of the window class
    
    // Size of the structure - set to the size of it
    wc.cbSize        = sizeof(WNDCLASSEX);

    // style of the class (NOT Window) - usually set to 0
    wc.style         = 0;

    // Pointer to the window procedure for this window class.
    wc.lpfnWndProc   = WndProc;

    // Amount of extra data allocated for this class in memory. Usually 0.
    wc.cbClsExtra    = 0;

    // Amount of extra data allocated in memory per window of this type. Usually 0.
    wc.cbWndExtra    = 0;

    // Handle to application instance (that we got in the first parameter of WinMain()).
    wc.hInstance     = hInstance;

    // Large (usually 32x32) icon shown when the user presses Alt+Tab.
    // Set to the application itself here
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    
    // The symbol the pointer changes to over the window
    // IDC_ARROW is the regular mouse pointer
    // IDC_HAND is the Hand pointer
    // and so on..
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);

    // Setting the color of the window
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    // Name of a menu resource to use for the windows with this class.
    wc.lpszMenuName  = NULL;

    // Name to identify the class with.
    wc.lpszClassName = g_szClassName;

    // Small (usually 16x16) icon to show in the taskbar and in the top left corner of the window.
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Title",
        WS_OVERLAPPEDWINDOW,
        // Top corner X,Y Values, and Window dimesions
        175, 125, 1000, 500,
        // Parent window handle, menu handle, app instance handle (got as a parameter of main) and creation data (always NULL)
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    // THE HEART OF THE PROGRAM
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}