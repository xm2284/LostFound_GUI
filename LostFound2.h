
// LostFound2.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CLostFound2App_7047:
// 有关此类的实现，请参阅 LostFound2.cpp
//

class CLostFound2App_7047 : public CWinApp
{
public:
	CLostFound2App_7047();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CLostFound2App_7047 theApp;
