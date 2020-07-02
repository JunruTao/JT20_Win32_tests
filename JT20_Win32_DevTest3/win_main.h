#ifndef WIN_MAIN_H
#define WIN_MAIN_H

#include "base_window_CORE.h"//Inclde Header here

class MainWindow : public BaseWindow<MainWindow>
{
public:
    PCWSTR  ClassName() const { return L"Sample Window Class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
