#include "pch.h"
#include "CFoundItemDlg.h"

IMPLEMENT_DYNAMIC(CFoundItemDlg_7047, CDialogEx)

CFoundItemDlg_7047::CFoundItemDlg_7047(CWnd* pParent)
	: CDialogEx(IDD_FOUND_ITEM_DLG, pParent), m_category_7047(0)
{
}

CFoundItemDlg_7047::~CFoundItemDlg_7047()
{
}

void CFoundItemDlg_7047::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name_7047);
	DDV_MaxChars(pDX, m_name_7047, 39);
	DDX_CBIndex(pDX, IDC_COMBO_CATEGORY, m_category_7047);
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_description_7047);
	DDV_MaxChars(pDX, m_description_7047, 199);
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_location_7047);
	DDV_MaxChars(pDX, m_location_7047, 59);
	DDX_Text(pDX, IDC_EDIT_DATE, m_date_7047);
	DDV_MaxChars(pDX, m_date_7047, 8);
	DDX_Text(pDX, IDC_EDIT_PERSON, m_personName_7047);
	DDV_MaxChars(pDX, m_personName_7047, 19);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_phone_7047);
	DDV_MaxChars(pDX, m_phone_7047, 19);
}

BEGIN_MESSAGE_MAP(CFoundItemDlg_7047, CDialogEx)
END_MESSAGE_MAP()

BOOL CFoundItemDlg_7047::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 丢失和捡到使用同一套类别，匹配时类别相同是必要条件。
	CComboBox* categoryBox = (CComboBox*)GetDlgItem(IDC_COMBO_CATEGORY);
	categoryBox->ResetContent();
	categoryBox->AddString(L"电子产品");
	categoryBox->AddString(L"证件卡片");
	categoryBox->AddString(L"书籍文具");
	categoryBox->AddString(L"衣物饰品");
	categoryBox->AddString(L"生活用品");
	categoryBox->AddString(L"运动器材");
	categoryBox->AddString(L"其他");
	UpdateData(FALSE);
	return TRUE;
}
