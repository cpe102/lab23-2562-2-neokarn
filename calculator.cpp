#include <windows.h>

#include<windows.h>
#include<iostream>
#include<cstdlib>

HWND textfield, b1,b2,b3,b4, TextBox1,TextBox2;

using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

		case WM_CREATE:
        textfield = CreateWindow("STATIC",
                                "Please input two numbers",WS_VISIBLE | WS_CHILD | WS_BORDER,
                                20,20,200,25,
                                hwnd,NULL,NULL,NULL);
        TextBox1 = CreateWindow("EDIT",
                                "",WS_BORDER|WS_CHILD|WS_VISIBLE,
                                20,60,200,25,
                                hwnd,NULL,NULL,NULL);
        TextBox2 = CreateWindow("EDIT",
                                "",WS_BORDER|WS_CHILD|WS_VISIBLE,
                                20,90,200,25,
                                hwnd,NULL,NULL,NULL);
		b1 = CreateWindow("BUTTON"," + ",WS_VISIBLE | WS_CHILD | WS_BORDER,
                                30,130,40,25,hwnd,(HMENU) 1,NULL,NULL);
        b2 = CreateWindow("BUTTON"," - ",WS_VISIBLE | WS_CHILD | WS_BORDER,
                                80,130,40,25,hwnd,(HMENU) 2,NULL,NULL);
        b3 = CreateWindow("BUTTON"," * ",WS_VISIBLE | WS_CHILD | WS_BORDER,
                                130,130,40,25,hwnd,(HMENU) 3,NULL,NULL);
        b4 = CreateWindow("BUTTON"," / ",WS_VISIBLE | WS_CHILD | WS_BORDER,
                                180,130,40,25,hwnd,(HMENU) 4,NULL,NULL);
		case WM_COMMAND:

            double x;
            char num1[20],num2[20];
            GetWindowText(TextBox1,num1,20);
            GetWindowText(TextBox2,num2,20);
            
            switch (LOWORD(wParam))
            {
            case 1:
                x=atof(num1)+atof(num2);
                sprintf(num1,"%f",x);
                ::MessageBox(hwnd,num1,"result",MB_OK);
                break;
            case 2:
                x=atof(num1)-atof(num2);
                sprintf(num1,"%f",x);
                ::MessageBox(hwnd,num1,"result",MB_OK);
                break;
            case 3:
                x=atof(num1)*atof(num2);
                sprintf(num1,"%f",x);
                ::MessageBox(hwnd,num1,"result",MB_OK);
                break;
            case 4:
                x=atof(num1)/atof(num2);
                sprintf(num1,"%f",x);
                ::MessageBox(hwnd,num1,"result",MB_OK);
                break;
            default:
                break;
            }

        break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
	
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+9);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}



