#pragma once
#include "afxdialogex.h"
#include "resource.h"

class CFoundItemDlg_7047 : public CDialogEx
{
	DECLARE_DYNAMIC(CFoundItemDlg_7047)

public:
	CFoundItemDlg_7047(CWnd* pParent = nullptr);
	virtual ~CFoundItemDlg_7047();
	enum { IDD = IDD_FOUND_ITEM_DLG };

	CString m_name_7047;
	int m_category_7047;
	CString m_description_7047;
	CString m_location_7047;
	CString m_date_7047;
	CString m_personName_7047;
	CString m_phone_7047;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
