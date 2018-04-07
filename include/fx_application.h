#ifndef __FX_APPLICATION_H__
#define __FX_APPLICATION_H__

#include <windows.h>
#include <string>
#include <vector>

class FXApplication
{
private:
	FXApplication()
	{
	}

	//
	//  函数: MyRegisterClass()
	//
	//  目的: 注册窗口类。
	//
	ATOM MyRegisterClass(HINSTANCE hInstance)
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FXTETRISWITHAI));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = m_szWindowClass.c_str();
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		return ::RegisterClassExW(&wcex);
	}

	//
	//   函数: InitInstance(HINSTANCE, int)
	//
	//   目的: 保存实例句柄并创建主窗口
	//
	//   注释: 
	//
	//        在此函数中，我们在全局变量中保存实例句柄并
	//        创建和显示主程序窗口。
	//
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
	{
		m_hInst = hInstance; // 将实例句柄存储在全局变量中

		HWND hWnd = ::CreateWindowW(m_szWindowClass.c_str(), m_szTitle.c_str(), WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

		if (!hWnd)
		{
			return FALSE;
		}

		::ShowWindow(hWnd, nCmdShow);
		::UpdateWindow(hWnd);

		return TRUE;
	}

	//
	//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
	//
	//  目的:    处理主窗口的消息。
	//
	//  WM_COMMAND  - 处理应用程序菜单
	//  WM_PAINT    - 绘制主窗口
	//  WM_DESTROY  - 发送退出消息并返回
	//
	//
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// 分析菜单选择: 
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(m_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
//             case IDM_EXIT:
//                 DestroyWindow(hWnd);
//                 break;
// 			case FX_IDM_RESET:
// 				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: 在此处添加使用 hdc 的任何绘图代码...
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}

	// “关于”框的消息处理程序。
	static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
		UNREFERENCED_PARAMETER(lParam);
		switch (message)
		{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
		}
		return (INT_PTR)FALSE;
	}

public:
	void init(const std::wstring szTitle, const std::wstring szWindowClass)
	{
		m_szTitle = szTitle;
		m_szWindowClass = szWindowClass;
	}

	int exec(_In_ HINSTANCE hInstance, _In_ int nCmdShow)
	{
		MyRegisterClass(hInstance);

		if (!InitInstance(hInstance, nCmdShow))
		{
			return FALSE;
		}

// 		ACCEL accels[] = 
// 		{
// 			{ FCONTROL | FVIRTKEY, 'R', FX_IDM_RESET},
// 		};
// 		int accelsize = sizeof(accels) / sizeof(accels[0]);
		m_hAccelTable = ::CreateAcceleratorTable(m_accels.data(), m_accels.size());
// 		CopyAcceleratorTable()

		MSG msg;
		while (::GetMessage(&msg, nullptr, 0, 0))
		{
			if (!::TranslateAccelerator(msg.hwnd, m_hAccelTable, &msg))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}

		::DestroyAcceleratorTable(m_hAccelTable);
		m_hAccelTable = nullptr;
		return (int)msg.wParam;
	}

	static FXApplication * inst()
	{
		static FXApplication instance;
		return &instance;
	}

private:
	std::wstring m_szTitle;
	std::wstring m_szWindowClass;
	std::vector<ACCEL> m_accels;

	static HINSTANCE	m_hInst;
	static HACCEL		m_hAccelTable;
};

HINSTANCE	FXApplication::m_hInst			= nullptr;
HACCEL		FXApplication::m_hAccelTable	= nullptr;

#endif // !__FX_APPLICATION_H__
