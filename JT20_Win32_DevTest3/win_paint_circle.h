#ifndef WIN_PAINT_CIRCLE_H
#define WIN_PAINT_CIRCLE_H

#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "base_window_CORE.h"

class CircleWindow : public BaseWindow<CircleWindow>
{
private:
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pBrush;
	D2D1_ELLIPSE ellipse;

	void    CalculateLayout();             //---------------[1]
	HRESULT CreateGraphicsResources();     //---------------[2]
	void    DiscardGraphicsResources();    //---------------[3]
	void    OnPaint();                     //---------------[4]
	void    Resize();                      //---------------[5]

	D2D1::ColorF background;
	D2D1::ColorF geometry;

public:
	//[**W1]------CONSTRUCTOT
	CircleWindow() :
		pFactory(NULL),
		pRenderTarget(NULL), 
		pBrush(NULL), 
		background({1.0f,0,1.0f,1.0f}),
		geometry({1.0f,0,0,1.0f}) {}

	//[**W2]------HANDLE MESSAGE(same with all windows, detailed down)
	LRESULT HandleMessage(UINT uMessage, WPARAM wParam, LPARAM lParam);

	//[6]------Getter Function(return the name to the CreateWindowEx)
	PCWSTR ClassName() const { return L"JT Draw Window Class"; }
};



#endif
