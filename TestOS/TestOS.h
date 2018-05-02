#pragma once

#include "resource.h"

// init
void DefaultInit();							 // загрузка, если нет файла
bool LoadData();							 // загрузка из файла
void SaveData();							 // сохранение текущего состояния
void DefaultTest();							 // операции над тестовой конфигурацией для проверки всех действий
void CreateButtons(HINSTANCE hInstance);	 // создаем кнопки управления операциями
void CreatePathButtons(HINSTANCE hInstance); // создаем кнопки папок-файлов-ярлыков



extern spFolder			m_pMainStage;
extern spFolder			m_pCurrentDirectory;
extern spBaseObject		m_pPressedObject;
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
};