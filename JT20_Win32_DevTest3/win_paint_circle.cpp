#include <windows.h>
#pragma comment(lib, "d2d1")

#include "win_paint_circle.h"

//[1] Recalculate drawing layout when the size of the window changes.
void CircleWindow::CalculateLayout()
{
	if (pRenderTarget != NULL)
	{
		//render target as bound.
		D2D1_SIZE_F size = pRenderTarget->GetSize();
		const float x = size.width /2;
		const float y = size.height /2;
		//fit in one dimension
		const float radius = min(x*0.8f, y*0.8f);
		ellipse = D2D1::Ellipse(D2D1::Point2(x, y), radius, radius);
	}
}

//[2] (A resource is an object that the program uses for drawing)
HRESULT CircleWindow::CreateGraphicsResources()
{
	HRESULT hr = S_OK; //Like a boolean type more specific for win32

	//[2.1]-----If the render target is not created, then create:
	if (pRenderTarget == NULL)
	{
		//[2.1.1]-----Get the window range:
		RECT rectangleU;
		GetClientRect(m_hwnd, &rectangleU);
		//[2.1.2]-----transit into direct2D-1's sizeU type
		D2D1_SIZE_U size = D2D1::SizeU(rectangleU.right, rectangleU.bottom);

		//[2.1.3]-----the drawing factor -> Create the render target
		hr = pFactory->CreateHwndRenderTarget
		(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&pRenderTarget
		);

		//[2.2]-----if the r.t. is created successfully, Create the [drawing resources]
		if (SUCCEEDED(hr)) //for `hresult`s -> `succeeded()/failed()`fucntions to get boolean
		{
			//[2.2.1]-----ColorF(r,g,b,a) -> (remapped/normalised values)
			const D2D1_COLOR_F color = geometry;
			//[2.2.2]-----pass in the resource(brush this case) pointer, assign info to it.
			hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

			//[2.3]-----Execute function[1]^^^^^
			if (SUCCEEDED(hr)) { CalculateLayout(); }

		}
	}
	return hr;
}


/* NOTE:
	All handles are COM based, so using the safe-release function!
	The SafeRelase() is placed in base_window_CORE.h*/
//[3] Discharge the resource
void CircleWindow::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
	SafeRelease(&pBrush);
}


//[4] Painting
void CircleWindow::OnPaint()
{
	//[4.1]Ready the tools, calling its own function[3]^^^^
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr))
	{
		//[4.2]Create a new instance of PaintStruct
		PAINTSTRUCT pStruc;
		BeginPaint(m_hwnd, &pStruc);
		//[4.3]begin draw
		pRenderTarget->BeginDraw();

		//[4.4.1] Prepare Background, `Clear` method fills the entire render target with a solid color
		//pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Chocolate)); <= Casting Color Enums 
		pRenderTarget->Clear(background);
		//[4.4.2] Drawing the ellipse using pBrush resource
		pRenderTarget->FillEllipse(ellipse, pBrush);

		//[4.5]Ending drawing
		hr = pRenderTarget->EndDraw();
		if (FAILED(hr)||hr == D2DERR_RECREATE_TARGET) 
		{
			DiscardGraphicsResources();
		}
		EndPaint(m_hwnd,&pStruc);//Exiting Paint Struc
	}

}


//[5] Resizing window
void CircleWindow::Resize()
{
	if (pRenderTarget != NULL) 
	{
		//same process:[2.2.1~2]
		RECT rec;
		GetClientRect(m_hwnd, &rec);
		D2D1_SIZE_U size = D2D1::SizeU(rec.right, rec.bottom);

		pRenderTarget->Resize(size);
		CalculateLayout();
		InvalidateRect(m_hwnd, NULL, FALSE);
		/*[IvalidateRect] => Asking to redraw/update window
		The `InvalidateRect` function adds a rectangle to the 
		specified window's update region. The update region 
		represents the portion of the window's client area 
		that must be redrawn.*/
	}
}



//____________________[WINDOW CLASS FUCNTIONS]_____________________
//[**W2]Handle Messages
LRESULT CircleWindow::HandleMessage(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage) 
	{
	case WM_CREATE:

		//Validating [create a single-threaded d2d1 factory]
		//WM_CREATE is called, Create Factory, pass to pFactory ptp
		HRESULT hr;
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
		if (FAILED(hr)) 
		{
			MessageBox(m_hwnd, L"Direct2D Create Factory failed!", ClassName(), MB_OK);
			return -1;
		}
		return 0;

	case WM_DESTROY:
		DiscardGraphicsResources(); //---------[3]
		SafeRelease(&pFactory);     //----release COM resource
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		OnPaint(); //-------[4]
		return 0;

	case WM_SIZE:
		Resize(); //-------[5]
		return 0;
	}
	return DefWindowProc(m_hwnd, uMessage, wParam, lParam);
}