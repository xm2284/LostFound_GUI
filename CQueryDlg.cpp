#include "pch.h"
#include "CQueryDlg.h"

IMPLEMENT_DYNAMIC(CQueryDlg_7047, CDialogEx)

CQueryDlg_7047::CQueryDlg_7047(CWnd* pParent)
	: CDialogEx(IDD_QUERY_DLG, pParent), m_type_7047(0)
{
}

CQueryDlg_7047::~CQueryDlg_7047()
{
}

void CQueryDlg_7047::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_KEYWORD, m_keyword_7047);
	DDV_MaxChars(pDX, m_keyword_7047, 59);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_type_7047);
}

BEGIN_MESSAGE_MAP(CQueryDlg_7047, CDialogEx)
END_MESSAGE_MAP()

BOOL CQueryDlg_7047::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CComboBox* box = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	box->ResetContent();
	box->AddString(L"全部");
	box->AddString(L"丢失");
	box->AddString(L"捡到");
	UpdateData(FALSE);
	return TRUE;
}
