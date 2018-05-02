// TestOS.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Header.h"
#include "BaseObject.h"
#include "Folder.h"
#include "File.h"
#include "Link.h"
#include "TestOS.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

spFolder m_pMainStage = nullptr;
spFolder m_pCurrentDirectory = nullptr;

HWND h_MainWnd;

bool LoadData()
{

	return false;
}

void SaveData()
{

}

void DefaultInit()
{
	spFolder pFolder1( new Folder("Music", "iconFolder1"));
	spFolder pFolder2( new Folder("Pictures", "iconFolder2"));
	spFolder pFolder3( new Folder("Documents", "iconFolder3"));
	spFolder pFolder4( new Folder("World", "iconFolder4"));
	spFolder pFolder5( new Folder( "Night", "iconFolder5"));
	
	m_pMainStage->AddChild(pFolder1);
	m_pMainStage->AddChild(pFolder2);
	m_pMainStage->AddChild(pFolder3);
	pFolder2->AddChild(pFolder4);
	pFolder4->AddChild(pFolder5);

	spFile pFile1( new File("Night1", "iconFile1", ".png", 135.f));
	spFile pFile2( new File("Night2", "iconFile2", ".jpg", 164.f));
	spFile pFile3( new File("Night3", "iconFile3", ".png", 152.f));
	spFile pFile4( new File("Forest", "iconFile4", ".jpg", 173.f));
	spFile pFile5( new File("Ocean",  "iconFile5", ".png", 115.f));

	pFolder4->AddChild(pFile1);
	pFolder4->AddChild(pFile2);
	pFolder4->AddChild(pFile3);
	pFolder3->AddChild(pFile4);
	pFolder3->AddChild(pFile5);

	m_pCurrentDirectory = pFolder5;
}

void DefaultTest()
{
	
}

void CreatePathButtons(HINSTANCE hInstance)
{
	// очищаем меню
	for ( HWND Btn : m_vButtons )
		DestroyWindow(Btn);
	m_vButtons.clear();

	// загружаем новые кнопки из текущей директории
	int nDeltaW = 150, nDeltaH = 40, nIndexW = 0, nIndexH = 0, nIndex = 0;

	for (spBaseObject pObj : m_pCurrentDirectory->m_vChilds)
	{
		std::string srFullName = pObj->GetExtName();
		wstring srFullNameW(srFullName.begin(), srFullName.end());

		int nXPos = 30 + (nDeltaW * nIndexW);
		int nYPos = 150 + (nDeltaW * nIndexH);
		++nIndexW;

		if (nXPos > 1200)
		{
			nIndexW = 0;
			++nIndexH;
			nXPos = 30 + (nDeltaW * nIndexW);
			nYPos = 150 + (nDeltaW * nIndexH);
		}

		int nIndexBtn = (eBaseObject + nIndex);
		HWND hBtn1 = CreateWindow(L"BUTTON", srFullNameW.c_str(), BS_NOTIFY | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_LEFT , nXPos, nYPos, 120, 20, h_MainWnd, (HMENU)nIndexBtn, hInstance, NULL);

		++nIndex;
		m_vButtons.push_back(hBtn1);
	}
}


void CreateButtons(HINSTANCE hInstance)
{
	HANDLE hBitmap1 = LoadImageW(NULL, L"back.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap2 = LoadImageW(NULL, L"rename.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap3 = LoadImageW(NULL, L"home.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap4 = LoadImageW(NULL, L"file.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap5 = LoadImageW(NULL, L"link.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap6 = LoadImageW(NULL, L"folder.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap7 = LoadImageW(NULL, L"delete.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap8 = LoadImageW(NULL, L"move.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap9 = LoadImageW(NULL, L"move2.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);


	HWND hBtn1 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 0, 20, 50, 50, h_MainWnd, (HMENU)eBackButton, hInstance, NULL);
	HWND hBtn3 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 52, 20, 50, 50, h_MainWnd, (HMENU)eHomeButton, hInstance, NULL);

	HWND hBtn2 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 200, 20, 50, 50, h_MainWnd, (HMENU)eRenameButton, hInstance, NULL);
	HWND hBtn4 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 252, 20, 50, 50, h_MainWnd, (HMENU)eCreateFileButton, hInstance, NULL);
	HWND hBtn5 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 304, 20, 50, 50, h_MainWnd, (HMENU)eCreateLinkButton, hInstance, NULL);
	HWND hBtn6 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 356, 20, 50, 50, h_MainWnd, (HMENU)eCreateFolderButton, hInstance, NULL);
	HWND hBtn7 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 512, 20, 50, 50, h_MainWnd, (HMENU)eDeleteButton, hInstance, NULL);

	HWND hBtn8 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 408, 20, 50, 50, h_MainWnd, (HMENU)eCopyButton, hInstance, NULL);
	HWND hBtn9 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 460, 20, 50, 50, h_MainWnd, (HMENU)eInsertButton, hInstance, NULL);

	SendMessageW(hBtn1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap1);
	SendMessageW(hBtn2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);
	SendMessageW(hBtn3, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap3);
	SendMessageW(hBtn4, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap4);
	SendMessageW(hBtn5, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap5);
	SendMessageW(hBtn6, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap6);
	SendMessageW(hBtn7, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap7);
	SendMessageW(hBtn8, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap8);
	SendMessageW(hBtn9, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap9);
}

template<typename T>
static std::wstring toWString(T xType)
{
	std::wstringstream srStream;
	srStream << xType;

	std::wstring srOut = srStream.str();
	return srOut;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TESTOS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	spFolder pMain (new Folder("MainFolder", "iconMain"));
	m_pMainStage = pMain;

	if (!LoadData())
		DefaultInit();
	DefaultTest();

	
	HWND hBtn1 = CreateWindow(L"BUTTON", L"Текущий путь:", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_LEFT, 0, 0, 1280, 20, h_MainWnd, (HMENU)ePathButton, hInstance, NULL); 
	CreateButtons(hInstance);
	CreatePathButtons(hInstance);
	

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTOS));
    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
		// TODO - обновлять только при изменении m_pCurrentDirectory
		std::string srPath = "Current path: ";
		srPath += m_pCurrentDirectory->GetPath();
		std::wstring wstr(srPath.begin(), srPath.end());
		SetWindowText(hBtn1, wstr.c_str());


        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	SaveData();

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTOS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTOS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   h_MainWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!h_MainWnd)
   {
      return FALSE;
   }

   ShowWindow(h_MainWnd, nCmdShow);
   UpdateWindow(h_MainWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			int wmId2 = HIWORD(wParam);

			// открываем папку
			if (wmId2 == BN_DBLCLK && wmId >= eBaseObject)
			{
				int nIndexObj = wmId - eBaseObject;
				if (m_pCurrentDirectory->m_vChilds.size() >= nIndexObj + 1)
				{
					spBaseObject pCurClick = *std::next(m_pCurrentDirectory->m_vChilds.begin(), nIndexObj);
					if (pCurClick->IsOpen())
					{
						m_pCurrentDirectory = (Folder*)pCurClick.get();
						CreatePathButtons(hInst);
					}
				}
			}


            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case eBackButton:
			{
				if (m_pCurrentDirectory && m_pCurrentDirectory->GetParent())
					m_pCurrentDirectory = (Folder*)m_pCurrentDirectory->GetParent();

				CreatePathButtons(hInst);
			}
			break;
			case eHomeButton:
			{
				m_pCurrentDirectory = m_pMainStage;
				CreatePathButtons(hInst);
			}
			break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	
	
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
