#define WIN32_LEAN_AND_MEAN
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "USER32")
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")

#define KEYDOWN(k) ((k)&0x80)

// This is a **very** minimal hotcorner app, written in C. Maybe its not the
// optimal way to do this, but it works for me.
//
// Zero state is stored anywhere, no registry keys or configuration files.
//
// - If you want to configure something, edit the code.
// - If you want to uninstall it, just delete it.
//
// Tavis Ormandy <taviso@cmpxchg8b.com> December, 2016
//
// https://github.com/taviso/hotcorner
//

// If the mouse enters this rectangle, activate the hot corner function.
// There are some hints about changing corners here
//      https://github.com/taviso/hotcorner/issues/7#issuecomment-269367351
static const RECT kHotCorner_topleft = {
    .top = -20,
    .left = -20,
    .right = +20,
    .bottom = +20,
};

static RECT kHotCorner_downleft;

static RECT kHotCorner_downRight;

// Input to inject when corner activated (Win+Tab by default).
static const INPUT kCornerInput_topleft[] = {
    {INPUT_KEYBOARD, .ki = {VK_LWIN, .dwFlags = 0}},
    {INPUT_KEYBOARD, .ki = {VK_TAB, .dwFlags = 0}},
    {INPUT_KEYBOARD, .ki = {VK_TAB, .dwFlags = KEYEVENTF_KEYUP}},
    {INPUT_KEYBOARD, .ki = {VK_LWIN, .dwFlags = KEYEVENTF_KEYUP}},
};

static const INPUT kCornerInput_downleft[] = {
    {INPUT_KEYBOARD, .ki = {VK_LCONTROL, .dwFlags = 0}},
    {INPUT_KEYBOARD, .ki = {VK_LWIN, .dwFlags = 0}},
    {INPUT_KEYBOARD, .ki = {VK_LEFT, .dwFlags = 0}},
    {INPUT_KEYBOARD, .ki = {VK_LCONTROL, .dwFlags = KEYEVENTF_KEYUP}},
    {INPUT_KEYBOARD, .ki = {VK_LWIN, .dwFlags = KEYEVENTF_KEYUP}},
    {INPUT_KEYBOARD, .ki = {VK_LEFT, .dwFlags = KEYEVENTF_KEYUP}},
};

static const INPUT kCornerInput_downRight[] = {
    {INPUT_KEYBOARD, .ki = {VK_LCONTROL, .dwFlags = 0}},
    {INPUT_KEYBOARD, .ki = {VK_LWIN, .dwFlags = 0}},
    {INPUT_KEYBOARD, .ki = {VK_RIGHT, .dwFlags = 0}},
    {INPUT_KEYBOARD, .ki = {VK_LCONTROL, .dwFlags = KEYEVENTF_KEYUP}},
    {INPUT_KEYBOARD, .ki = {VK_LWIN, .dwFlags = KEYEVENTF_KEYUP}},
    {INPUT_KEYBOARD, .ki = {VK_RIGHT, .dwFlags = KEYEVENTF_KEYUP}},
};

// activeHotCorner will be kCornerInput_topleft or kCornerInput_downleft
static INPUT **activekCornerInput;

// How long cursor has to linger in the kHotCorner RECT to trigger input.
static const DWORD kHotDelay = 300;

// You can exit the application using the hot key CTRL+ALT+C by default, if it
// interferes with some application you're using (e.g. a full screen game).
static const DWORD kHotKeyModifiers = MOD_CONTROL | MOD_ALT;
static const DWORD kHotKey = 'C';

static HANDLE CornerThread = INVALID_HANDLE_VALUE;

// This thread runs when the cursor enters the hot corner, and waits to see if the cursor stays in the corner.
// If the mouse leaves while we're waiting, the thread is just terminated.
static DWORD WINAPI CornerHotFunc_TopLeft(LPVOID lpParameter)
{
    BYTE KeyState[256];
    POINT Point;

    Sleep(kHotDelay);

    // Check if a mouse putton is pressed, maybe a drag operation?
    if (GetKeyState(VK_LBUTTON) < 0 || GetKeyState(VK_RBUTTON) < 0)
    {
        return 0;
    }

    // Check if any modifier keys are pressed.
    if (GetKeyboardState(KeyState))
    {
        if (KEYDOWN(KeyState[VK_SHIFT]) || KEYDOWN(KeyState[VK_CONTROL]) || KEYDOWN(KeyState[VK_MENU]) || KEYDOWN(KeyState[VK_LWIN]) || KEYDOWN(KeyState[VK_RWIN]))
        {
            return 0;
        }
    }

    // Verify the corner is still hot
    if (GetCursorPos(&Point) == FALSE)
    {
        return 1;
    }

    // Check co-ordinates.
    if (PtInRect(&kHotCorner_topleft, Point))
    {
#pragma warning(suppress : 4090)
        if (SendInput(_countof(kCornerInput_topleft), kCornerInput_topleft, sizeof(INPUT)) != _countof(kCornerInput_topleft))
        {
            return 1;
        }
    }
    return 0;
}

// This thread runs when the cursor enters the hot corner, and waits to see if the cursor stays in the corner.
// If the mouse leaves while we're waiting, the thread is just terminated.
static DWORD WINAPI CornerHotFunc_DownLeft(LPVOID lpParameter)
{
    BYTE KeyState[256];
    POINT Point;

    Sleep(10);

    // Check if a mouse putton is pressed, maybe a drag operation?
    if (GetKeyState(VK_LBUTTON) < 0 || GetKeyState(VK_RBUTTON) < 0)
    {
        return 0;
    }

    // Check if any modifier keys are pressed.
    if (GetKeyboardState(KeyState))
    {
        if (KEYDOWN(KeyState[VK_SHIFT]) || KEYDOWN(KeyState[VK_CONTROL]) || KEYDOWN(KeyState[VK_MENU]) || KEYDOWN(KeyState[VK_LWIN]) || KEYDOWN(KeyState[VK_RWIN]))
        {
            return 0;
        }
    }

    // Verify the corner is still hot
    if (GetCursorPos(&Point) == FALSE)
    {
        return 1;
    }

#pragma warning(suppress : 4090)
    if (SendInput(_countof(kCornerInput_downleft), kCornerInput_downleft, sizeof(INPUT)) != _countof(kCornerInput_downleft))
    {
        return 1;
    }

    return 0;
}

// This thread runs when the cursor enters the hot corner, and waits to see if the cursor stays in the corner.
// If the mouse leaves while we're waiting, the thread is just terminated.
static DWORD WINAPI CornerHotFunc_DownRight(LPVOID lpParameter)
{
    BYTE KeyState[256];
    POINT Point;

    Sleep(10);

    // Check if a mouse button is pressed, maybe a drag operation?
    if (GetKeyState(VK_LBUTTON) < 0 || GetKeyState(VK_RBUTTON) < 0)
    {
        return 0;
    }

    // Check if any modifier keys are pressed.
    if (GetKeyboardState(KeyState))
    {
        if (KEYDOWN(KeyState[VK_SHIFT]) || KEYDOWN(KeyState[VK_CONTROL]) || KEYDOWN(KeyState[VK_MENU]) || KEYDOWN(KeyState[VK_LWIN]) || KEYDOWN(KeyState[VK_RWIN]))
        {
            return 0;
        }
    }

    // Verify the corner is still hot
    if (GetCursorPos(&Point) == FALSE)
    {
        return 1;
    }

#pragma warning(suppress : 4090)
    if (SendInput(_countof(kCornerInput_downRight), kCornerInput_downRight, sizeof(INPUT)) != _countof(kCornerInput_downRight))
    {
        return 1;
    }

    return 0;
}

static LRESULT CALLBACK MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    MSLLHOOKSTRUCT *evt = (MSLLHOOKSTRUCT *)lParam;
    // If the mouse hasn't moved, we're done.
    if (wParam != WM_MOUSEMOVE)
        goto finish;

    // Check if the cursor is hot or cold.
    if (!(PtInRect(&kHotCorner_topleft, evt->pt) || PtInRect(&kHotCorner_downleft, evt->pt) || PtInRect(&kHotCorner_downRight, evt->pt)))
    {

        // The corner is cold, and was cold before.
        if (CornerThread == INVALID_HANDLE_VALUE)
            goto finish;

        // The corner is cold, but was previously hot.
        TerminateThread(CornerThread, 0);

        CloseHandle(CornerThread);

        // Reset state.
        CornerThread = INVALID_HANDLE_VALUE;

        goto finish;
    }

    // The corner is hot, check if it was already hot.
    if (CornerThread != INVALID_HANDLE_VALUE)
    {
        goto finish;
    }

    // Check if a mouse button is pressed, maybe a drag operation?
    if (GetKeyState(VK_LBUTTON) < 0 || GetKeyState(VK_RBUTTON) < 0)
    {
        goto finish;
    }

    // select activekCornerInput
    if (PtInRect(&kHotCorner_topleft, evt->pt))
    {
        // The corner is hot, and was previously cold. Here we start a thread to
        // monitor if the mouse lingers.
        printf("top left activated\n");
        CornerThread = CreateThread(NULL, 0, CornerHotFunc_TopLeft, NULL, 0, NULL);
    }
    else if (PtInRect(&kHotCorner_downleft, evt->pt))
    {
        // The corner is hot, and was previously cold. Here we start a thread to
        // monitor if the mouse lingers.
        printf("down left activated\n");
        CornerThread = CreateThread(NULL, 0, CornerHotFunc_DownLeft, NULL, 0, NULL);
    }
    else if (PtInRect(&kHotCorner_downRight, evt->pt))
    {
        // The corner is hot, and was previously cold. Here we start a thread to
        // monitor if the mouse lingers.
        printf("down right activated\n");
        CornerThread = CreateThread(NULL, 0, CornerHotFunc_DownRight, NULL, 0, NULL);
    }

finish:
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int getConfigY()
{
    FILE *fp;
    fp = fopen(".\\configy.txt", "r");
    if (fp == NULL)
    {
        return GetSystemMetrics(SM_CYSCREEN);
    }
    int screenY;
    fscanf(fp, "%d", &screenY);
    fclose(fp);
    if (screenY <= 0)
    {
        return GetSystemMetrics(SM_CYSCREEN);
    }
    return screenY;
}

int getConfigX()
{
    FILE *fp;
    fp = fopen(".\\configx.txt", "r");
    if (fp == NULL)
    {
        return GetSystemMetrics(SM_CXSCREEN);
    }
    int screenX;
    fscanf(fp, "%d", &screenX);
    printf("x = %d", screenX);
    fclose(fp);
    if (screenX <= 0)
    {
        printf("te %d", GetSystemMetrics(SM_CXSCREEN));
        return GetSystemMetrics(SM_CXSCREEN);
    }
    return screenX;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG Msg;
    HHOOK MouseHook;

    // get screen  size y

    kHotCorner_downleft.bottom = getConfigY();

    kHotCorner_downleft.top = kHotCorner_downleft.bottom - 20;
    kHotCorner_downleft.bottom += 20;
    kHotCorner_downleft.left = -20;
    kHotCorner_downleft.right = +20;

    // get screen  size x

    kHotCorner_downRight.bottom = getConfigY();

    kHotCorner_downRight.top = kHotCorner_downRight.bottom - 20;
    kHotCorner_downRight.bottom += 20;
    kHotCorner_downRight.left = getConfigX() - 20;
    kHotCorner_downRight.right = getConfigX() + 20;

    if (!(MouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookCallback, NULL, 0)))
        return 1;

    RegisterHotKey(NULL, 1, kHotKeyModifiers, kHotKey);

    while (GetMessage(&Msg, NULL, 0, 0))
    {
        if (Msg.message == WM_HOTKEY)
        {
            break;
        }
        DispatchMessage(&Msg);
    }

    UnhookWindowsHookEx(MouseHook);

    return Msg.wParam;
}
