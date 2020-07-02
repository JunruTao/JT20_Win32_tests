#pragma once
/*[Note]
Using a template window class, and so on all other window creations will be
based on this class as derived child.
*/

#include <Windows.h>

template <class DERIVED_TYPE>
class BaseWindow
{
public:
	//[1]Window Procedure Function: <HAVE TO BE STATIC>
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
	{
		/* [NOTES]------------------------------------------------------------------------------- //
		ref URL: https://docs.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-/
			(1) When Constructing a window, WM_NCCREATE and WM_CREATE will be passed to WndProc, via [last Param].

			(2)The WM_NCCREATE and WM_CREATE message are sent before the window becomes visible. That makes
			them a good place to initialize your UI—for example, to determine the initial layout of the window.

			(3) [last Parameter] is a `void*` pointer type, which [can be casted in to any value].
			## you can define a class/struct to hold this info. i.g.`struct StateInfo`

			(4)Then when using CreateWindowEx, pass a pointer pState to this structure(,lParam);
			##  lParam parameter of each message is a pointer to a CREATESTRUCT structure.
		/* [NOTES]------------------------------------------------------------------------------- */

		//[Derived Type] -> the Structure type holds that info;
		//[pThis] -> pointer from lParam, pass into CREATESTRUCT structure;
		DERIVED_TYPE* pThis = NULL;

		//[WM_NCCREATE] -> Sent prior to the WM_CREATE message when a window is first created
		if (uMessage == WM_NCCREATE)
		{
			/*(5)
			Here is how you extract the pointer to your data structure.
			First, get the CREATESTRUCT structure by casting the lParam parameter.*/
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			/*(6)
			The lpCreateParams member of the CREATESTRUCT structure is the original
			void pointer that you specified in CreateWindowEx. Get a pointer to your
			own data structure by casting lpCreateParams.*/
			pThis = (DERIVED_TYPE*)pCreate->lpCreateParams; // reinterpret_cast<DERIVED_TYPE*>
			/*(7)
			Next, call the SetWindowLongPtr function and pass in the pointer to your
			data structure.*/
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->m_hwnd = hwnd;
		}
		else
		{
			pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}

		if (pThis)
		{
			return pThis->HandleMessage(uMessage, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMessage, wParam, lParam);
		}


	}

	//[0]Constructor:
	BaseWindow() : m_hwnd(NULL) { }

	//[2] Create function
	BOOL Create(
		PCWSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExStyle = 0,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU hMenu = 0
	)
	{
		WNDCLASS wc = { 0 };

		wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = ClassName(); //smart!

		RegisterClass(&wc);

		m_hwnd = CreateWindowEx(
			dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
			nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
		);

		return (m_hwnd ? TRUE : FALSE);
	}

	HWND Window() const { return m_hwnd; }

protected:
	//[N] Virtual function and members
	virtual PCWSTR ClassName() const = 0; //*def pure virtual function
	virtual LRESULT HandleMessage(UINT uMessage, WPARAM wParam, LPARAM lParam) = 0; //*def pure virtual function

	//This window's handle
	HWND m_hwnd;

};


template <class T> 
void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}