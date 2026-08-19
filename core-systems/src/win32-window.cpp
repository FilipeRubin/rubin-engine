#include "win32-window.h"
#include "input/win32-basic-input.h"
#include <logging/log-macros.h>
#include <Windows.h>

#ifdef ERROR
#undef ERROR
#endif

unsigned int Win32Window::s_instanceCount = 0U;
Win32WindowClass Win32Window::s_windowClass = Win32WindowClass();

Win32Window::Win32Window() :
    m_hwnd(NULL),
    m_shouldClose(false),
    m_basicInput(Win32BasicInput()),
    m_windowSizeCallback(nullptr),
    m_size(Dimensions()),
    m_frequency(0LL),
    m_clockStart(0LL)
{
}

void Win32Window::Finalize()
{
    LOG_INFO("Finalizing Win32 window.");
    DestroyWindow((HWND)m_hwnd);
    m_hwnd = nullptr;
    Decrement();
    m_shouldClose = false;
    m_frequency = 0LL;
}

void Win32Window::Process()
{
    m_basicInput.Update();
    MSG msg = {};
    while (PeekMessage(&msg, (HWND)m_hwnd, NULL, NULL, PM_REMOVE) != 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool Win32Window::ShouldClose() const
{
    return m_shouldClose;
}

bool Win32Window::IsInitialized() const
{
    return m_hwnd != nullptr;
}

bool Win32Window::TryInitialize(const WindowParameters& parameters)
{
    if (IsInitialized())
    {
        return true;
    }

    LARGE_INTEGER frequency;
    LARGE_INTEGER clockStart;
    if (QueryPerformanceFrequency(&frequency) == FALSE)
    {
        LOG_ERROR("Failed to query the performance-counter frequency for the window timer.");
        return false;
    }
    if (QueryPerformanceCounter(&clockStart) == FALSE)
    {
        LOG_ERROR("Failed to query the initial performance-counter value for the window timer.");
        return false;
    }
    m_frequency = frequency.QuadPart;
    m_clockStart = clockStart.QuadPart;

    if (not TryIncrement())
    {
        LOG_ERROR("Failed to prepare the Win32 window class.");
        return false;
    }
    
    HINSTANCE hInstance = (HINSTANCE)s_windowClass.GetInstanceHandle();

    SetProcessDPIAware();

    RECT windowRect = { 0, 0, parameters.width, parameters.height };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
    int width = windowRect.right - windowRect.left;
    int height = windowRect.bottom - windowRect.top;

    m_hwnd = CreateWindowEx(
        0,
        s_windowClass.GetWindowClassName(),
        parameters.title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        NULL,
        NULL,
        hInstance,
        NULL
    );
        
    if (m_hwnd == NULL)
    {
        LOG_ERROR("Failed to create the Win32 window. Error code: " + std::to_string(GetLastError()) + ".");
        Decrement();
        return false;
    }

    SetWindowLongPtr((HWND)m_hwnd, GWLP_USERDATA, (LONG_PTR)this);

    ShowWindow((HWND)m_hwnd, SW_SHOW);

    m_size = Dimensions(parameters.width, parameters.height);
    LOG_INFO("Win32 window initialized with size " + std::to_string(parameters.width) + "x" + std::to_string(parameters.height) + ".");

    return true;
}

IBasicInput& Win32Window::BasicInput()
{
    return static_cast<IBasicInput&>(m_basicInput);
}

Dimensions Win32Window::GetSize() const
{
    return m_size;
}

float Win32Window::GetAspectRatio() const
{
    return float(m_size.width) / float(m_size.height);
}

float Win32Window::GetTime() const
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return float(double(counter.QuadPart - m_clockStart) / double(m_frequency));
}

WindowSizeCallback Win32Window::GetWindowSizeCallback() const
{
    return m_windowSizeCallback;
}

void Win32Window::SetTitle(const wchar_t* title)
{
    SetWindowText((HWND)m_hwnd, title);
}

void Win32Window::SetWindowSizeCallback(WindowSizeCallback windowSizeCallback)
{
    m_windowSizeCallback = windowSizeCallback;
}

void Win32Window::Close()
{
    m_shouldClose = true;
}

const void* Win32Window::GetHandle() const
{
    return m_hwnd;
}

void Win32Window::UpdateSize(const Dimensions& size)
{
    m_size = size;
}

bool Win32Window::TryIncrement()
{
    if (s_instanceCount == 0U)
    {
        if (not s_windowClass.TryRegister(L"SFDWND"))
        {
            return false;
        }
    }
    s_instanceCount++;
    return true;
}

void Win32Window::Decrement()
{
    s_instanceCount--;
    if (s_instanceCount == 0U)
    {
        s_windowClass.Unregister();
    }
}
