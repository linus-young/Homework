#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );

TCHAR szAppName[] = TEXT("lab2") ;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   PSTR szCmdLine, int iCmdShow)
{
	HACCEL   hAccel ;
	HWND     hwnd ;
	MSG      msg ;
	int		 numberOfAccelerator;
	ACCEL	 arrayAccel[ 20 ];
	WNDCLASS wndclass ;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (hInstance, MAKEINTRESOURCE (IDI_ICON1)) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = (LPCTSTR)IDR_MENU1 ;
	wndclass.lpszClassName = szAppName ;

	if (!RegisterClass (&wndclass))
		return 0 ;

	hwnd = CreateWindow (szAppName, TEXT ("lab2"),
						 WS_OVERLAPPEDWINDOW,
						 CW_USEDEFAULT, CW_USEDEFAULT,
						 CW_USEDEFAULT, CW_USEDEFAULT,
						 NULL, NULL, hInstance, NULL) ;

	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;

	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	
	// Ϊfile�˵�������̬���ټ�
	numberOfAccelerator = CopyAcceleratorTable(hAccel, NULL, 0);
	CopyAcceleratorTable( hAccel, arrayAccel, numberOfAccelerator );
	arrayAccel [ numberOfAccelerator ].cmd	 = IDM_APP_EXIT;
	arrayAccel [ numberOfAccelerator ].fVirt = FCONTROL | FSHIFT | FVIRTKEY;
	arrayAccel [ numberOfAccelerator ].key   = VK_DELETE ;
	++numberOfAccelerator;
	DestroyAcceleratorTable(hAccel);
	hAccel = CreateAcceleratorTable( arrayAccel, numberOfAccelerator );

	while (GetMessage (&msg, NULL, 0, 0))
	{
		if(!TranslateAccelerator (hwnd, hAccel, &msg))
		{
			TranslateMessage (&msg) ;
			DispatchMessage (&msg) ;
		}
	}
	DestroyAcceleratorTable(hAccel);
	return msg.wParam ;
}




LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR iconStr[] = { TEXT("��ǰʹ�õ�ͼ���ǣ�ͼ��1"), 
						  TEXT("��ǰʹ�õ�ͼ���ǣ�ͼ��2"),
						  TEXT("��ǰʹ�õ�ͼ���ǣ�ͼ��3") }; 
	LPCTSTR show[] = { TEXT("��ʾ1"),TEXT("��ʾ2"),TEXT("��ʾ3"),TEXT("��ʾ4") };
	static int iconSet[] = { IDI_ICON1, IDI_ICON2, IDI_ICON3 };
	PAINTSTRUCT ps;
	HDC hdc;
	static HINSTANCE hInstance;
	HMENU hSubMenu ; //File�˵�

	//��õ�ǰ��ͼ�꣬�Ա���icon3ʱ�һ��ĸ�show��
	//ͬʱ���Ա���ѡ����ѡ����ͼ��ʱ�Ե����Ի���
	static DWORD iconMenuId ; 
	int messageId = LOWORD( wParam ) ;
	//messageId��������command��Ϣ�е�loword(wParam),��֤���ټ���������

	HMENU      hMenu ;

	switch (message)
	{
	//������create�Ͳ�Ҫ����initmenu������ͬ�Ľ����˵�������ᵼ���Ӳ˵�������
	case WM_CREATE : 
		hInstance = ((LPCREATESTRUCT) lParam)->hInstance; // ���������Ӧ�ó����ʵ�����
		hMenu = GetMenu(hwnd);
		// ��̬����file�˵�
		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu,MF_STRING,IDM_APP_EXIT,TEXT("&Exit\tCtrl+Shift+Delete"));
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_POPUP , (UINT)hSubMenu,TEXT("&File"));
		iconMenuId = ID_ICON_ONE;
		CheckMenuRadioItem(hMenu, ID_ICON_ONE,  ID_ICON_THREE, 
			ID_ICON_ONE, MF_BYCOMMAND);  //Ĭ��ѡ��ͼ��1
		return 0 ;

	case WM_PAINT:
		hMenu = GetMenu (hwnd) ;
		hdc = BeginPaint(hwnd, &ps);
		if( iconMenuId != ID_ICON_THREE )//��ͼ�겻��3ʱ������ʾ�ĸ�show
		{
			for( messageId = ID_SHOW_ONE; messageId <= ID_SHOW_FOUR; messageId++ )
			{
				if( GetMenuState(hMenu,messageId,MF_BYCOMMAND) & MF_CHECKED )
					TextOut(hdc, (messageId - ID_SHOW_ONE)*60+150,200,
						show[messageId - ID_SHOW_ONE],lstrlen(show[messageId - ID_SHOW_ONE]));
			}
		}

		for (messageId = ID_ICON_ONE; messageId <= ID_ICON_THREE; messageId++ )
		{
			if( GetMenuState(hMenu, messageId, MF_BYCOMMAND) & MF_CHECKED ){
				TextOut(hdc,100, 100, iconStr[messageId - ID_ICON_ONE], 
					lstrlen(iconStr[messageId - ID_ICON_ONE]));
			}
		}
		
		EndPaint (hwnd, &ps);
		return 0;

	case WM_COMMAND:
		hMenu = GetMenu (hwnd) ;

		switch (messageId)
		{
		case IDM_APP_EXIT:
			SendMessage (hwnd, WM_CLOSE, 0, 0) ;
			return 0 ;
			
		case ID_ICON_ONE:  //��Ҫ��ʾ�������������ʾ���Է���غϲ��⼸��case��
		case ID_ICON_TWO:  //ֻ�贫��messageId��������
		case ID_ICON_THREE:
			
			if( (messageId != iconMenuId) && (MessageBox(hwnd,TEXT("ȷ��Ҫ�޸���"),
				TEXT("Confirmation"),MB_YESNO|MB_ICONQUESTION) == IDYES)){

					CheckMenuRadioItem(hMenu, ID_ICON_ONE,  ID_ICON_THREE, 
						messageId, MF_BYCOMMAND);
					SetClassLong(hwnd,GCL_HICON,(long)LoadIcon(hInstance,
						MAKEINTRESOURCE( iconSet[messageId - ID_ICON_ONE])));
					iconMenuId = messageId ; // which made icon3 do not show 1,2,3,4
					if( messageId == ID_ICON_THREE )
					{
						EnableMenuItem(hMenu,ID_SHOW_ONE,MF_GRAYED);
						EnableMenuItem(hMenu,ID_SHOW_TWO,MF_GRAYED);
						EnableMenuItem(hMenu,ID_SHOW_THREE,MF_GRAYED);
						EnableMenuItem(hMenu,ID_SHOW_FOUR,MF_GRAYED);
					}
					else
					{
						EnableMenuItem(hMenu,ID_SHOW_ONE,MF_ENABLED);
						EnableMenuItem(hMenu,ID_SHOW_TWO,MF_ENABLED);
						EnableMenuItem(hMenu,ID_SHOW_THREE,MF_ENABLED);
						EnableMenuItem(hMenu,ID_SHOW_FOUR,MF_ENABLED);
					}
					InvalidateRect (hwnd, NULL, TRUE);
			}
			return 0;

		case ID_SHOW_ONE:
		case ID_SHOW_TWO:
		case ID_SHOW_THREE:
		case ID_SHOW_FOUR:
			// ʹ���ĸ�show����ѡ����ʾ���
			if (GetMenuState(hMenu,messageId,MF_BYCOMMAND) & MF_CHECKED)
				CheckMenuItem(hMenu,messageId,MF_UNCHECKED);
			else
				CheckMenuItem(hMenu,messageId,MF_CHECKED);
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case IDM_APP_ABOUT:
			MessageBox(hwnd,
			 TEXT("�ڶ����ϻ���ϰ\nͼ�ꡢ�˵������ټ�����Ϣ��\n\nѧ�ţ�10112130261\n������������"),
			 TEXT("lab2"),MB_ICONINFORMATION);
			return 0;
		}
	case WM_DESTROY:
		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
