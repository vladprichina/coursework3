#include "stdafx.h"
#include "Header.h"
#include "Objects/BaseObject.h"
#include "Objects/Folder.h"
#include "Objects/File.h"
#include "Objects/Link.h"
#include "TestOS.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

spFolder m_pMainStage = nullptr;
spFolder m_pCurrentDirectory = nullptr;
spBaseObject m_pPressedObject = nullptr;
spBaseObject m_pCopyButton = nullptr;
HWND h_MainWnd, h_PathWnd, h_InfoWnd;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Delete(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Rename(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddFile(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddFolder(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddLink(HWND, UINT, WPARAM, LPARAM);


bool LoadData()
{
	// TODO
	return false;
}

void SaveData()
{
	// TODO
}

void SetPressed(spBaseObject pPress)
{
	m_pPressedObject = pPress;

	wstring srNewText = L"Info:\n";
	if (m_pPressedObject)
	{
		srNewText += L" Name: " + m_pPressedObject->GetExtName() + L"\n";
		srNewText += L" Size: " + to_wstring(m_pPressedObject->GetSize()) + L" KB\n";
		srNewText += L" Creation time: " + m_pPressedObject->GetTimeCreate()+ L"\n";
		srNewText += L" Mofication time: " + m_pPressedObject->GetTimeModify() + L"\n";
		SetWindowText(h_InfoWnd, srNewText.c_str());
	}

	SetWindowText(h_InfoWnd, srNewText.c_str());

}

void DefaultInit()
{
	spFolder pFolder1( new Folder(L"Music", L"iconFolder1"));
	spFolder pFolder2( new Folder(L"Pictures", L"iconFolder2"));
	spFolder pFolder3( new Folder(L"Documents", L"iconFolder3"));
	spFolder pFolder4( new Folder(L"World", L"iconFolder4"));
	spFolder pFolder5( new Folder(L"Night", L"iconFolder5"));
	
	m_pMainStage->AddChild(pFolder1);
	m_pMainStage->AddChild(pFolder2);
	m_pMainStage->AddChild(pFolder3);
	pFolder2->AddChild(pFolder4);
	pFolder4->AddChild(pFolder5);

	spFile pFile1(new File(L"Night1", L"iconFile1", L"png", 135.f));
	spFile pFile2(new File(L"Night2", L"iconFile2", L"jpg", 164.f));
	spFile pFile3(new File(L"Night3", L"iconFile3", L"png", 152.f));
	spFile pFile4(new File(L"Forest", L"iconFile4", L"jpg", 173.f));
	spFile pFile5(new File(L"Ocean", L"iconFile5", L"png", 115.f));

	pFolder4->AddChild(pFile1);
	pFolder4->AddChild(pFile2);
	pFolder4->AddChild(pFile3);
	pFolder3->AddChild(pFile4);
	pFolder3->AddChild(pFile5);

	m_pCurrentDirectory = pFolder5;
}

void CreatePathButtons(HINSTANCE hInstance)
{
	// очищаем меню
	for ( HWND Btn : m_vButtons )
		DestroyWindow(Btn);
	m_vButtons.clear();

	// очищаем выделенный элемент
	m_pPressedObject = nullptr;

	// загружаем новые кнопки из текущей директории
	int nDeltaW = 150, nDeltaH = 20, nIndexW = -1, nIndexH = 0, nIndex = 0;

	for (spBaseObject pObj : m_pCurrentDirectory->m_vChilds)
	{
		std::wstring srFullName = pObj->GetExtName();

		++nIndexW;
		int nXPos = 30 + (nDeltaW * nIndexW);
		int nYPos = 150 + (nDeltaW * nIndexH);
		
		if (nXPos > 1200)
		{
			nIndexW = 0;
			++nIndexH;
			nXPos = 30 + (nDeltaW * nIndexW);
			nYPos = 150 + (nDeltaW * nIndexH);
		}

		int nIndexBtn = (eBaseObject + nIndex);
		HWND hBtn1 = CreateWindow(L"BUTTON", srFullName.c_str(), BS_NOTIFY | WS_VISIBLE | WS_CHILD  | BS_LEFT | BS_AUTORADIOBUTTON | BS_PUSHLIKE, nXPos, nYPos, 120, 20, h_MainWnd, (HMENU)nIndexBtn, hInstance, NULL);

		++nIndex;
		m_vButtons.push_back(hBtn1);
	}

	std::wstring srPath = L"Current path: ";
	srPath += m_pCurrentDirectory->GetPath();
	SetWindowText(h_PathWnd, srPath.c_str());
}


void CreateButtons(HINSTANCE hInstance)
{
	HANDLE hBitmap1 = LoadImageW(NULL, L"Resource/back.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap2 = LoadImageW(NULL, L"Resource/rename.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap3 = LoadImageW(NULL, L"Resource/home.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap4 = LoadImageW(NULL, L"Resource/file.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap5 = LoadImageW(NULL, L"Resource/link.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap6 = LoadImageW(NULL, L"Resource/folder.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap7 = LoadImageW(NULL, L"Resource/delete.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap8 = LoadImageW(NULL, L"Resource/move.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE hBitmap9 = LoadImageW(NULL, L"Resource/move2.bmp", IMAGE_BITMAP, 50, 50, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);

	HWND hBtn1 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 0, 0, 50, 50, h_MainWnd, (HMENU)eBackButton, hInstance, NULL);
	HWND hBtn3 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 52, 0, 50, 50, h_MainWnd, (HMENU)eHomeButton, hInstance, NULL);
	HWND hBtn2 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 200, 0, 50, 50, h_MainWnd, (HMENU)eRenameButton, hInstance, NULL);
	HWND hBtn4 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 252, 0, 50, 50, h_MainWnd, (HMENU)eCreateFileButton, hInstance, NULL);
	HWND hBtn5 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 304, 0, 50, 50, h_MainWnd, (HMENU)eCreateLinkButton, hInstance, NULL);
	HWND hBtn6 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 356, 0, 50, 50, h_MainWnd, (HMENU)eCreateFolderButton, hInstance, NULL);
	HWND hBtn7 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 512, 0, 50, 50, h_MainWnd, (HMENU)eDeleteButton, hInstance, NULL);
	HWND hBtn8 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 408, 0, 50, 50, h_MainWnd, (HMENU)eCopyButton, hInstance, NULL);
	HWND hBtn9 = CreateWindow(L"BUTTON", L"", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 460, 0, 50, 50, h_MainWnd, (HMENU)eInsertButton, hInstance, NULL);
	h_PathWnd = CreateWindow(L"STATIC", L"Current path:", BS_TEXT | WS_VISIBLE | WS_CHILD  | BS_LEFT , 0, 90, 1280, 20, h_MainWnd, (HMENU)ePathButton, hInstance, NULL);
	h_InfoWnd  = CreateWindow(L"STATIC", L"Info:", BS_TEXT | WS_VISIBLE | WS_CHILD | BS_LEFT, 660, 0, 300, 80, h_MainWnd, (HMENU)eInfoText, hInstance, NULL);

	SendMessageW(hBtn1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap1);
	SendMessageW(hBtn2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);
	SendMessageW(hBtn3, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap3);
	SendMessageW(hBtn4, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap4);
	SendMessageW(hBtn5, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap5);
	SendMessageW(hBtn6, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap6);
	SendMessageW(hBtn7, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap7);
	SendMessageW(hBtn8, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap8);
	SendMessageW(hBtn9, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap9);

	EnableWindow(hBtn9, FALSE);
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
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

	spFolder pMain (new Folder(L"MainFolder", L"iconMain"));
	m_pMainStage = pMain;

	if (!LoadData())
		DefaultInit();

	CreateButtons(hInstance);
	CreatePathButtons(hInstance);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTOS));
    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	SaveData();

    return (int) msg.wParam;
}


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


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			int wmId2 = HIWORD(wParam);

			if (wmId >= eBaseObject)
			{
				// открываем папку
				if (wmId2 == BN_DBLCLK || wmId2 == BN_CLICKED)
				{
					int nIndexObj = wmId - eBaseObject;
					spBaseObject pCurClick = nullptr;
					if (m_pCurrentDirectory->m_vChilds.size() >= nIndexObj + 1)
						pCurClick = *std::next(m_pCurrentDirectory->m_vChilds.begin(), nIndexObj);

					// открываем папку
					if (pCurClick && wmId2 == BN_DBLCLK)
					{
						if (spBaseObject pCur = pCurClick->IsOpen())
						{
							m_pCurrentDirectory = (Folder*)pCur.get();
							CreatePathButtons(hInst);
							SetPressed(nullptr);
						}
					}

					// выделяем элемент
					if (pCurClick && wmId2 == BN_CLICKED)
					{
						HWND curentHWND = GetDlgItem(h_MainWnd, wmId); // по id получаем hwnd
						SendMessage(curentHWND, BM_SETCHECK, BST_CHECKED, 0);
						SetPressed(pCurClick);
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
			case eDeleteButton:
			{
				if (!m_pPressedObject)
					break;
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DELETE), hWnd, Delete);
			}
			break;
			case eRenameButton:
			{
				if (!m_pPressedObject)
					break;
				DialogBox(hInst, MAKEINTRESOURCE(IDD_RENAME), hWnd, Rename);
			}
			break;
			case eCopyButton:
			{
				if (!m_pPressedObject)
					break;
				
				HWND hInsert = GetDlgItem(h_MainWnd, eInsertButton); // по id получаем hwnd
				EnableWindow(hInsert, TRUE);
				m_pCopyButton = m_pPressedObject;
			}
			break;
			case eInsertButton:
			{
				if (!m_pCopyButton)
					break;

				if (!m_pCurrentDirectory->GetChild(m_pCopyButton->GetName(), m_pCopyButton->GetAddName()))
				{
					m_pCopyButton->DeleteThis();
					m_pCurrentDirectory->AddChild(m_pCopyButton);
					m_pCopyButton = nullptr;

					HWND hInsert = GetDlgItem(h_MainWnd, eInsertButton); // по id получаем hwnd
					EnableWindow(hInsert, FALSE);
					CreatePathButtons(hInst);
				}
			}
			break;
			case eCreateFileButton:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ADD_FILE), hWnd, AddFile);
			}
			break;
			case eCreateFolderButton:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ADD_FOLDER), hWnd, AddFolder);
			}
			break;
			case eCreateLinkButton:
			{
				if( !m_pPressedObject )
					break;

				DialogBox(hInst, MAKEINTRESOURCE(IDD_CREATE_LINK), hWnd, AddLink);
			}
			break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_LBUTTONDOWN:
	{
		for (HWND Btn : m_vButtons)
			SendMessage(Btn, BM_SETCHECK, BST_UNCHECKED, 0);
		SetPressed(nullptr);
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


INT_PTR CALLBACK Delete(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			if (LOWORD(wParam) == IDOK)
			{
				if (m_pPressedObject && m_pPressedObject != m_pMainStage )
					m_pPressedObject->DeleteThis();
				
				SetPressed(nullptr);
				CreatePathButtons(hInst);
			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Rename(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			if (LOWORD(wParam) == IDOK)
			{
				HWND editHWND = GetDlgItem(hDlg, RenameBtn); // по id получаем hwnd

				int len = GetWindowTextLength(editHWND) + 1;
				vector<wchar_t> buf(len);
				GetWindowText(editHWND, &buf[0], len);

				std::wstring srNewName = &buf[0];

				// проверка на наличие такого же элемента в директории
				if (!m_pCurrentDirectory->GetChild(srNewName, m_pPressedObject->GetAddName()))
				{
					m_pPressedObject->SetName(srNewName);
					m_pPressedObject->SetModifyTime();
					CreatePathButtons(hInst);
				}
				else
					return (INT_PTR)TRUE;
			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AddFile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			if (LOWORD(wParam) == IDOK)
			{
				HWND editName = GetDlgItem(hDlg, EnterFileNameBtn); // по id получаем hwnd
				HWND editFormat = GetDlgItem(hDlg, EnterFileFormatBtn); // по id получаем hwnd

				int len = GetWindowTextLength(editName) + 1;
				vector<wchar_t> buf(len);
				GetWindowText(editName, &buf[0], len);
				std::wstring srNewName = &buf[0];

				len = GetWindowTextLength(editFormat) + 1;
				vector<wchar_t> buf2(len);
				GetWindowText(editFormat, &buf2[0], len);
				std::wstring srNewFormat = &buf2[0];

				float fSize = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 500.f));	// размер файла случайный

				bool bTestLink = srNewFormat == typeHLink || srNewFormat == typeSLink; // нельзя создавать ссылки с помощью расширения
				if (!m_pCurrentDirectory->GetChild(srNewName, srNewFormat) || bTestLink)
				{
					spFile pFile(new File(srNewName, L"def_icon", srNewFormat, fSize));
					m_pCurrentDirectory->AddChild(pFile);
					CreatePathButtons(hInst);
				}
				else
					return (INT_PTR)TRUE;
			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AddFolder(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			if (LOWORD(wParam) == IDOK)
			{
				HWND editName = GetDlgItem(hDlg, CreateFolderBtn); // по id получаем hwnd

				int len = GetWindowTextLength(editName) + 1;
				vector<wchar_t> buf(len);
				GetWindowText(editName, &buf[0], len);
				std::wstring srNewName = &buf[0];
				std::wstring srExt;

				if (!m_pCurrentDirectory->GetChild(srNewName, srExt))
				{
					spFolder pFolder(new Folder(srNewName, L"def_icon"));
					m_pCurrentDirectory->AddChild(pFolder);
					CreatePathButtons(hInst);
				}
				else
					return (INT_PTR)TRUE;
			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AddLink(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			if (LOWORD(wParam) == IDOK)
			{
				eTypeLink eType = eTypeLink::eSymbol;
				if (IsDlgButtonChecked(hDlg, HardLinkBtn) == BST_CHECKED)
					eType = eHard;
					
				wstring srExt = m_pPressedObject->GetAddName();
				srExt += eType == eSymbol ? typeSLink : typeHLink;
				
				if (!m_pCurrentDirectory->GetChild(m_pPressedObject->GetName(), srExt))
				{
					spLink pLink(new Link(m_pPressedObject->GetName(), eType, m_pPressedObject));
					SetPressed(nullptr);
					m_pCurrentDirectory->AddChild(pLink);
					CreatePathButtons(hInst);
				}
				else
					return (INT_PTR)TRUE;
			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
