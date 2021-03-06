#pragma once

#include "resource.h"

// init
void DefaultInit();								// загрузка, если нет файла
bool LoadData();								// загрузка из файла
void SaveData();								// сохранение текущего состояния
void CreateButtons(HINSTANCE hInstance);		// создаем кнопки управления операциями
void CreatePathButtons(HINSTANCE hInstance);	// создаем кнопки папок-файлов-ярлыков
void SetPressed(spBaseObject pPress);				

//btns
extern spFolder			m_pMainStage;			// корень файловой системы
extern spFolder			m_pCurrentDirectory;	// место где мы находимся
extern spBaseObject		m_pPressedObject;		// активная кнопка 
extern spBaseObject		m_pCopyButton;			// кнопка, которую будем перемещать
extern HWND				h_MainWnd;

std::vector<HWND>		m_vButtons;				// кнопки папок-файлов-ярлыков

enum eTypeButton
{
	ePathButton				= 100,
	eBackButton				= 200,
	eDeleteButton			= 300,
	eCreateFolderButton		= 400,
	eCreateFileButton		= 500,
	eCreateLinkButton		= 600,
	eRenameButton			= 700,
	eHomeButton				= 800,
	eCopyButton				= 900,
	eInsertButton			= 1000,
	eBaseObject				= 1100,
	eInfoText				= 1200,
};