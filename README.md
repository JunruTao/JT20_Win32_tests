# JT20 Win32 tests
***
## 6/29/2020 Starting with Win32 API
Have tried different options creating a GUI for windows, now I found win32(Although very complicated) is very baisc and powerfull.
Having studied through few tutorials from youtube and udemy.com, now there are a very basic window application done from the scratch.
It was quite hard at the begining and I struggled with Unicode variable type such as `LPCWSTR` , `LRESULT`, however as long as being 
patient reading throught the Win32 API documents, it is very easy to get started with the code.

### 8:01 PM BST - [Update]
Enbedding win-OpenGL context/GLEW into Win32 Desktop Program. 
* Status: `SUCCESS`
***
### 7/1/2020 Learning COM in Win32, File Browser
Update with new Project:
  * Learning Using COM handling objects
  * Create menus and Open up file explorer dialog
  * using win32 smartpointers
  * planning on encapsulate windows

Next task experimenting with graphics in Win32
* Status: `SUCCESS`
***
## 7/2/2020 Windows Base as Template
Update with new Project:
  * Encapsulation of base_window as a template
  * window main object is derive from a type of `BaseWindow`
  * Seprate `win_main` from `main.cpp`, created header/cpp 

  #### 5:16 PM BST Update on PJ-Dev3
  * New Window Class, draw circle.
  * Using Direct2D library to draw a circle procedurally.
  * Add `DeclareDPIAware.manifest` to adapt different DPI rendertargets. 