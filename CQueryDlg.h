#pragma once
#include "afxdialogex.h"
#include "resource.h"

class CQueryDlg_7047 : public CDialogEx
{
	DECLARE_DYNAMIC(CQueryDlg_7047)

public:
	CQueryDlg_7047(CWnd* pParent = nullptr);
	virtual ~CQueryDlg_7047();
	enum { IDD = IDD_QUERY_DLG };

	CString m_keyword_7047;
	int m_type_7047;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
