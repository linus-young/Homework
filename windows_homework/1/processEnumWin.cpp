#include <windows.h>
#include "processEnumWin.h"
#include <stdio.h>
#include <conio.h>
#include <tlhelp32.h> // �������պ�����ͷ�ļ�
int WINAPI WinMain(HINSTANCE hInstance,                  // ��ں���
				   HINSTANCE,
				   LPSTR           lpCmdLine,
				   int                   nCmdShow )
{
	MSG msg;
	if (!InitApplication(hInstance))       // Ӧ�ó�ʼ��
		return FALSE;

	if (!InitInstance(hInstance,nCmdShow)) // ʵ����ʼ��
		return FALSE;

	
	while (GetMessage(&msg, NULL, 0, 0))   // ��Ϣѭ��
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

BOOL InitApplication(HINSTANCE hInstance)   // Ӧ�ó�ʼ��
{
    WNDCLASS  wc;  // Data structure of the window class

    wc.style            = CS_HREDRAW|CS_VREDRAW;
    wc.lpfnWndProc      = (WNDPROC)MainWndProc;  // Name of the Window Function 
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = TEXT("My1stWClass");  // Name of the window class

    return RegisterClass(&wc);
}

//***************************************************************************************

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)  // ʵ����ʼ��
{
    HWND hWnd = CreateWindow(TEXT("My1stWClass"),     // Name of the window class
                                                         TEXT("My First Window"),  // Title of the window
                                                         WS_OVERLAPPEDWINDOW,
                                                         CW_USEDEFAULT,
                                                         CW_USEDEFAULT,
                                                         CW_USEDEFAULT,
                                                         CW_USEDEFAULT,
                                                         NULL,
                                                         NULL,
                                                         hInstance,
                                                         NULL                                        );
    if (!hWnd) return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

// ���ڹ��̺���
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	
	PAINTSTRUCT ps;
	HDC hdc;
	PROCESSENTRY32 pe32;

	// ��������Ϣ�浽������
	LPTSTR buffer=new TCHAR[1024];
	int xLocation = 0;
	int yLocation = 0;
	// ��ϵͳ�ڵ����н����Ŀ���
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// ��ʹ������ṹ֮ǰ�����������Ĵ�С
	pe32.dwSize = sizeof(pe32); 
	if(hProcessSnap == INVALID_HANDLE_VALUE){       
		//printf(" CreateToolhelp32Snapshot����ʧ�ܣ� \n");     
		return -1;    
	}
	// �������̿��գ�������ʾÿ�����̵���Ϣ
	BOOL bMore = Process32First(hProcessSnap, &pe32);
	LPTSTR title = TEXT("����ID    ģ����");
	switch (message) {

	case WM_PAINT:  // ���ڿͻ�����ˢ��

		hdc = BeginPaint (hWnd, &ps);
		
		for (int i = 0; i < 3; ++i)
		{
			TextOut(hdc,20+i*350,10,title,lstrlen(title));
		}
		while(bMore){
			wsprintf(buffer,L"%05u    %s",pe32.th32ProcessID,pe32.szExeFile);
			if( xLocation < 1000){ //ÿ�����3��������Ϣ
				TextOut(hdc,20+xLocation,30+yLocation,buffer,lstrlen(buffer));
				xLocation += 350;
			}
			else{
				yLocation += 20;
				TextOut(hdc,20,30+yLocation,buffer,lstrlen(buffer));
				xLocation = 350;
			}
			bMore = Process32Next(hProcessSnap, &pe32);
			
		}
		EndPaint (hWnd, &ps);
		CloseHandle(hProcessSnap); // ���snapshot����
		getch();
		return 0;

	case WM_DESTROY: // ���ڹر�

		PostQuitMessage(0);

		return 0;

	default:  // ȱʡ��Ϣ�Ĵ���

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

}