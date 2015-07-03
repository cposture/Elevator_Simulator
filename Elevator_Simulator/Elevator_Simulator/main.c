#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL A_elevatorMove(int updown);

#define FLOORS_NUM    5
#define ELEVATOR_PASSENGER_MAXNUM 15
#define UP 0
#define DOWN 1
HWND            hwnd;
HWND            hwndFloor[FLOORS_NUM], hwndElevator[FLOORS_NUM], testButton;
HINSTANCE       hInstance;
static int      g_floor = 1,g_lock = 1;
static TCHAR    *floorLabel[] = { TEXT("第1层"), TEXT("第2层"), TEXT("第3层"), TEXT("第4层"), TEXT("第5层") };

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("Elevator_Simulator");
    MSG         msg;
    WNDCLASS     wndclass;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"),
            szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName,                  // window class name
        TEXT("Elevator_Simulator 数据结构-电梯模拟      By 陈家启 2015年6月"), // window caption
        WS_OVERLAPPEDWINDOW,        // window style
        CW_USEDEFAULT,              // initial x position
        CW_USEDEFAULT,              // initial y position
        CW_USEDEFAULT,              // initial x size
        CW_USEDEFAULT,              // initial y size
        NULL,                       // parent window handle
        NULL,                       // window menu handle
        hInstance,                  // program instance handle
        NULL);                     // creation parameters

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int i, cxClient, cyClient, cxFloor, cyFloor, wFloor, hFloor, cxElevator, cyElevator, wElevator, hElevator;
    static  int cyChar;

    switch (message)
    {
    case WM_CREATE:
        hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
        for (i = 0; i < FLOORS_NUM; i++)     //创建楼层静态文本，1，2...
        {
            hwndFloor[i] = CreateWindow(TEXT("static"), floorLabel[i],
                WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hwnd, (HMENU)(i),
                hInstance, NULL);
        }

        for (i = 0; i < FLOORS_NUM; i++)
        {
            hwndElevator[i] = CreateWindow(TEXT("static"), NULL,
                WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hwnd, (HMENU)(i + FLOORS_NUM),
                hInstance, NULL);
        }

        testButton = CreateWindow(TEXT("button"), TEXT("循环"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 0, 100, 100, hwnd, (HMENU)(FLOORS_NUM * 2), hInstance, NULL);
        cyChar = HIWORD(GetDialogBaseUnits());  //获取字体一个字符像素垂直平均基本单位
        return 0;
    case WM_SIZE:
        cxClient = LOWORD(lParam);  //窗口大小
        cyClient = HIWORD(lParam);
        cxFloor = 2 * cxClient / 14;//楼层标志位置
        cyFloor = 2 * cyChar;
        wFloor = cxClient / 14;
        hFloor = cxClient / 14;
        cxElevator = cxFloor + wFloor;
        cyElevator = 2 * cyChar;
        wElevator = ELEVATOR_PASSENGER_MAXNUM * 2 * cyChar ;
        hElevator = cxClient / 14;

        for (i = FLOORS_NUM -1; i >=0; i--)
        {
            MoveWindow(hwndFloor[i],       //MoveWindow更改hwndFloor的位置和大小
                cxFloor, cyFloor,
                wFloor, hFloor, TRUE);
            cyFloor += cxClient / 14;
        }
        for (i = FLOORS_NUM - 1; i >= 0; i--)    //电梯位置
        {
            MoveWindow(hwndElevator[i],
                cxFloor + wFloor, cyElevator,
                wElevator, hElevator, TRUE);
            cyElevator += cxClient / 14;
        }
        SetFocus(hwnd);
        return 0;
    case WM_COMMAND:
        switch (HIWORD(wParam))
        {
        case BN_CLICKED:
            A_elevatorMove(UP);
            break;
        }
    case    WM_CTLCOLORSTATIC:
        if (1 == g_lock)
            break;
        if (lParam == (LPARAM)hwndFloor[g_floor-1])
        {
            SetBkColor((HDC)wParam, RGB(0, 255, 0));
            return (LRESULT)CreateSolidBrush(RGB(0, 255, 0));
        }
        
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

/**
*	Name...........:    BOOL A_elevatorMove(int updown);
*	Description....:	A开头的函数表示图形界面操作函数，控制电梯上下移动的图形界面动画函数
*	Param..........:	updown: 0表示向上移动 1表示向下移动
*	Return.........:    TRUE:移动成功
                        FALSE:移动失败
*	Precondition...:    函数使用了全局变量g_floor和g_lock
*	Postcondition..:    移动成功时，根据updown的值g_floor加1或减1，同时g_lock置0；如果移动失败，不改变全局变量的值
**/
BOOL A_elevatorMove(int updown)
{
    RECT rect, wrect;
    POINT p;
    int h, w;

    if (updown != 0 && updown != 1)
        return FALSE;
    if (updown == 0 && g_floor >= FLOORS_NUM || updown == 1 && g_floor <= 1)
        return FALSE;
        
    GetWindowRect(hwndFloor[0], &rect);
    GetWindowRect(hwnd, &wrect);

    p.x = rect.left;
    p.y = rect.top;
    ScreenToClient(hwnd, &p);

    h = rect.bottom - rect.top;
    w = rect.right - rect.left;

    rect.bottom = p.y + h;
    rect.right = p.x + w;
    rect.top = p.y - (FLOORS_NUM - 1) * h;
    rect.left = p.x;

    if (0 == updown)
        g_floor++;
    else
        g_floor--;
    g_lock = 0;
    RedrawWindow(hwnd, &rect, NULL, RDW_INVALIDATE);
    return TRUE;
}