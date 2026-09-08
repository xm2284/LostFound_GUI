// LostFound2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "LostFound2.h"
#include "LostFound2Dlg.h"
#include "CLostItemDlg.h"
#include "CFoundItemDlg.h"
#include "CQueryDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static CString g_categoryNames[7] = {
	L"电子产品", L"证件卡片", L"书籍文具", L"衣物饰品",
	L"生活用品", L"运动器材", L"其他"
};

// 用于应用程序“关于”菜单项的 CAboutDlg_7047 对话框
class CAboutDlg_7047 : public CDialogEx
{
public:
	CAboutDlg_7047();
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
};

CAboutDlg_7047::CAboutDlg_7047() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg_7047::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg_7047, CDialogEx)
END_MESSAGE_MAP()

CLostFound2Dlg_7047::CLostFound2Dlg_7047(CWnd* pParent)
	: CDialogEx(IDD_LOSTFOUND2_DIALOG, pParent),
	m_matchCnt_7047(0), m_currentLostPos_7047(-1)
{
	m_hIcon_7047 = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLostFound2Dlg_7047::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOST, m_listLost_7047);
	DDX_Control(pDX, IDC_LIST_FOUND, m_listFound_7047);
	DDX_Control(pDX, IDC_EDIT_LOST_DETAIL, m_editLostDetail_7047);
	DDX_Control(pDX, IDC_EDIT_FOUND_DETAIL, m_editFoundDetail_7047);
}

BEGIN_MESSAGE_MAP(CLostFound2Dlg_7047, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD_LOST, &CLostFound2Dlg_7047::OnBnClickedAddLost_7047)
	ON_BN_CLICKED(IDC_BTN_MODIFY_LOST, &CLostFound2Dlg_7047::OnBnClickedModifyLost_7047)
	ON_BN_CLICKED(IDC_BTN_DELETE_LOST, &CLostFound2Dlg_7047::OnBnClickedDeleteLost_7047)
	ON_BN_CLICKED(IDC_BTN_MATCH, &CLostFound2Dlg_7047::OnBnClickedMatch_7047)
	ON_BN_CLICKED(IDC_BTN_ADD_FOUND, &CLostFound2Dlg_7047::OnBnClickedAddFound_7047)
	ON_BN_CLICKED(IDC_BTN_MODIFY_FOUND, &CLostFound2Dlg_7047::OnBnClickedModifyFound_7047)
	ON_BN_CLICKED(IDC_BTN_DELETE_FOUND, &CLostFound2Dlg_7047::OnBnClickedDeleteFound_7047)
	ON_BN_CLICKED(IDC_BTN_CLAIM, &CLostFound2Dlg_7047::OnBnClickedClaim_7047)
	ON_BN_CLICKED(IDC_BTN_QUERY, &CLostFound2Dlg_7047::OnBnClickedQuery_7047)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CLostFound2Dlg_7047::OnBnClickedClear_7047)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CLostFound2Dlg_7047::OnBnClickedRefresh_7047)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CLostFound2Dlg_7047::OnBnClickedExit_7047)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_LOST, &CLostFound2Dlg_7047::OnLvnItemchangedListLost_7047)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FOUND, &CLostFound2Dlg_7047::OnLvnItemchangedListFound_7047)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_LOST, &CLostFound2Dlg_7047::OnNMCustomdrawListLost_7047)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_FOUND, &CLostFound2Dlg_7047::OnNMCustomdrawListFound_7047)
END_MESSAGE_MAP()

BOOL CLostFound2Dlg_7047::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon_7047, TRUE);
	SetIcon(m_hIcon_7047, FALSE);

	addColumns_7047();
	adjustColumnWidths_7047();
	if (!m_book_7047.loadBook_7047())
		MessageBox(L"数据文件损坏或无法读取，已停止加载；原文件仍然保留。", L"数据提示", MB_OK | MB_ICONWARNING);
	showItems_7047();
	return TRUE;
}

void CLostFound2Dlg_7047::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg_7047 dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CLostFound2Dlg_7047::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND,
			reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon_7047);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CLostFound2Dlg_7047::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon_7047);
}

void CLostFound2Dlg_7047::addColumns_7047()
{
	CString lostTitles[6] = {
		L"编号", L"名称", L"类别", L"地点", L"日期", L"状态"
	};
	for (int i = 0; i < 6; i++)
		m_listLost_7047.InsertColumn(i, lostTitles[i], LVCFMT_LEFT, 80);

	CString foundTitles[7] = {
		L"编号", L"名称", L"类别", L"地点", L"日期", L"状态", L"匹配结果"
	};
	for (int i = 0; i < 7; i++)
		m_listFound_7047.InsertColumn(i, foundTitles[i], LVCFMT_LEFT, 80);

	m_listLost_7047.SetExtendedStyle(
		m_listLost_7047.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listFound_7047.SetExtendedStyle(
		m_listFound_7047.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void CLostFound2Dlg_7047::adjustColumnWidths_7047()
{
	CRect rect;
	m_listLost_7047.GetClientRect(&rect);
	int lostWidth = rect.Width() - GetSystemMetrics(SM_CXVSCROLL) - 4;
	int lostRatio[6] = { 8, 19, 17, 24, 17, 15 };
	int usedWidth = 0;
	for (int i = 0; i < 5; i++)
	{
		int width = lostWidth * lostRatio[i] / 100;
		m_listLost_7047.SetColumnWidth(i, width);
		usedWidth += width;
	}
	m_listLost_7047.SetColumnWidth(5, lostWidth - usedWidth);

	m_listFound_7047.GetClientRect(&rect);
	int foundWidth = rect.Width() - GetSystemMetrics(SM_CXVSCROLL) - 4;
	int foundRatio[7] = { 7, 17, 16, 20, 16, 12, 12 };
	usedWidth = 0;
	for (int i = 0; i < 6; i++)
	{
		int width = foundWidth * foundRatio[i] / 100;
		m_listFound_7047.SetColumnWidth(i, width);
		usedWidth += width;
	}
	m_listFound_7047.SetColumnWidth(6, foundWidth - usedWidth);
}

void CLostFound2Dlg_7047::insertLostRow_7047(int pos)
{
	Item_7047 item = m_book_7047.all_7047[pos];
	CString number;
	number.Format(L"%d", pos + 1);
	int row = m_listLost_7047.InsertItem(m_listLost_7047.GetItemCount(), number);
	m_listLost_7047.SetItemData(row, (DWORD_PTR)pos);
	m_listLost_7047.SetItemText(row, 1, item.name_7047);
	m_listLost_7047.SetItemText(row, 2, g_categoryNames[item.category_7047]);
	m_listLost_7047.SetItemText(row, 3, item.location_7047);
	m_listLost_7047.SetItemText(row, 4, item.date_7047);
	if (item.status_7047 == 0)
		m_listLost_7047.SetItemText(row, 5, L"待处理");
	else
		m_listLost_7047.SetItemText(row, 5, L"已完成");
}

void CLostFound2Dlg_7047::insertFoundRow_7047(int pos, int score)
{
	Item_7047 item = m_book_7047.all_7047[pos];
	CString number;
	number.Format(L"%d", pos + 1);
	int row = m_listFound_7047.InsertItem(m_listFound_7047.GetItemCount(), number);
	m_listFound_7047.SetItemData(row, (DWORD_PTR)pos);
	m_listFound_7047.SetItemText(row, 1, item.name_7047);
	m_listFound_7047.SetItemText(row, 2, g_categoryNames[item.category_7047]);
	m_listFound_7047.SetItemText(row, 3, item.location_7047);
	m_listFound_7047.SetItemText(row, 4, item.date_7047);
	if (item.status_7047 == 0)
		m_listFound_7047.SetItemText(row, 5, L"待处理");
	else
		m_listFound_7047.SetItemText(row, 5, L"已完成");

	CString scoreText = L"-";
	if (score == 4)
		scoreText = L"4-高度";
	else if (score == 3)
		scoreText = L"3-较高";
	else if (score == 2)
		scoreText = L"2-可能";
	else if (score == 1)
		scoreText = L"1-同类";
	else if (score == 0)
		scoreText = L"0-人工核对";
	m_listFound_7047.SetItemText(row, 6, scoreText);
}

CString CLostFound2Dlg_7047::buildItemDetail_7047(int pos)
{
	if (pos < 0 || pos >= m_book_7047.cnt_7047)
		return L"请选择一条记录查看完整信息。";

	Item_7047 item = m_book_7047.all_7047[pos];
	CString personTitle = L"失主";
	if (item.type_7047 == 1)
		personTitle = L"上交人";
	CString statusText = L"待处理";
	if (item.status_7047 == 1)
		statusText = L"已完成";

	CString detail;
	detail.Format(
		L"名称：%s\r\n描述：%s\r\n地点：%s    日期：%s\r\n%s：%s    电话：%s    状态：%s",
		(LPCTSTR)item.name_7047, (LPCTSTR)item.description_7047,
		(LPCTSTR)item.location_7047, (LPCTSTR)item.date_7047,
		(LPCTSTR)personTitle, (LPCTSTR)item.personName_7047,
		(LPCTSTR)item.phone_7047, (LPCTSTR)statusText);
	return detail;
}

void CLostFound2Dlg_7047::updateLostDetail_7047()
{
	m_editLostDetail_7047.SetWindowText(buildItemDetail_7047(getLostSelectedIndex_7047()));
}

void CLostFound2Dlg_7047::updateFoundDetail_7047()
{
	m_editFoundDetail_7047.SetWindowText(buildItemDetail_7047(getFoundSelectedIndex_7047()));
}

void CLostFound2Dlg_7047::showItems_7047()
{
	m_listLost_7047.DeleteAllItems();
	m_listFound_7047.DeleteAllItems();
	for (int i = 0; i < m_book_7047.cnt_7047; i++)
	{
		if (m_book_7047.all_7047[i].type_7047 == 0)
			insertLostRow_7047(i);
		else
			insertFoundRow_7047(i, -1);
	}
	m_matchCnt_7047 = 0;
	m_currentLostPos_7047 = -1;
	m_editLostDetail_7047.SetWindowText(L"请选择一条记录查看完整信息。");
	m_editFoundDetail_7047.SetWindowText(L"请选择一条记录查看完整信息。");
	m_listLost_7047.Invalidate();
	m_listFound_7047.Invalidate();
}

void CLostFound2Dlg_7047::showQueryResult_7047(int resultPos[], int resultCnt)
{
	m_listLost_7047.DeleteAllItems();
	m_listFound_7047.DeleteAllItems();
	for (int i = 0; i < resultCnt; i++)
	{
		int pos = resultPos[i];
		if (m_book_7047.all_7047[pos].type_7047 == 0)
			insertLostRow_7047(pos);
		else
			insertFoundRow_7047(pos, -1);
	}
	m_matchCnt_7047 = 0;
	m_currentLostPos_7047 = -1;
	m_editLostDetail_7047.SetWindowText(L"请选择一条记录查看完整信息。");
	m_editFoundDetail_7047.SetWindowText(L"请选择一条记录查看完整信息。");
	m_listLost_7047.Invalidate();
	m_listFound_7047.Invalidate();
}

void CLostFound2Dlg_7047::showMatchResult_7047()
{
	m_listFound_7047.DeleteAllItems();
	for (int i = 0; i < m_matchCnt_7047; i++)
		insertFoundRow_7047(m_matches_7047[i].foundIndex_7047, m_matches_7047[i].score_7047);
	if (m_matchCnt_7047 > 0)
	{
		m_listFound_7047.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED,
			LVIS_SELECTED | LVIS_FOCUSED);
		m_listFound_7047.EnsureVisible(0, FALSE);
		updateFoundDetail_7047();
	}
	else
	{
		m_editFoundDetail_7047.SetWindowText(L"没有找到满足条件的匹配候选。");
	}
	m_listLost_7047.Invalidate();
	m_listFound_7047.Invalidate();
}

int CLostFound2Dlg_7047::getLostSelectedIndex_7047()
{
	POSITION selected = m_listLost_7047.GetFirstSelectedItemPosition();
	if (selected == NULL)
		return -1;
	int row = m_listLost_7047.GetNextSelectedItem(selected);
	int pos = (int)m_listLost_7047.GetItemData(row);
	if (pos < 0 || pos >= m_book_7047.cnt_7047)
		return -1;
	return pos;
}

int CLostFound2Dlg_7047::getFoundSelectedIndex_7047()
{
	POSITION selected = m_listFound_7047.GetFirstSelectedItemPosition();
	if (selected == NULL)
		return -1;
	int row = m_listFound_7047.GetNextSelectedItem(selected);
	int pos = (int)m_listFound_7047.GetItemData(row);
	if (pos < 0 || pos >= m_book_7047.cnt_7047)
		return -1;
	return pos;
}

void CLostFound2Dlg_7047::OnBnClickedAddLost_7047()
{
	CLostItemDlg_7047 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	Item_7047 item;
	item.type_7047 = 0;
	item.name_7047 = dlg.m_name_7047;
	item.category_7047 = dlg.m_category_7047;
	item.description_7047 = dlg.m_description_7047;
	item.location_7047 = dlg.m_location_7047;
	item.date_7047 = dlg.m_date_7047;
	item.personName_7047 = dlg.m_personName_7047;
	item.phone_7047 = dlg.m_phone_7047;
	item.status_7047 = 0;
	if (!m_book_7047.addItem_7047(item))
	{
		MessageBox(L"登记失败：请检查必填内容和真实日期；系统最多100条；也可能是数据文件无法保存。", L"提示");
		return;
	}
	showItems_7047();
	MessageBox(L"登记丢失物品成功！", L"提示");
}

void CLostFound2Dlg_7047::OnBnClickedAddFound_7047()
{
	CFoundItemDlg_7047 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	Item_7047 item;
	item.type_7047 = 1;
	item.name_7047 = dlg.m_name_7047;
	item.category_7047 = dlg.m_category_7047;
	item.description_7047 = dlg.m_description_7047;
	item.location_7047 = dlg.m_location_7047;
	item.date_7047 = dlg.m_date_7047;
	item.personName_7047 = dlg.m_personName_7047;
	item.phone_7047 = dlg.m_phone_7047;
	item.status_7047 = 0;
	if (!m_book_7047.addItem_7047(item))
	{
		MessageBox(L"登记失败：请检查必填内容和真实日期；系统最多100条；也可能是数据文件无法保存。", L"提示");
		return;
	}
	showItems_7047();
	MessageBox(L"登记捡到物品成功！", L"提示");
}

void CLostFound2Dlg_7047::OnBnClickedModifyLost_7047()
{
	int pos = getLostSelectedIndex_7047();
	if (pos == -1 || m_book_7047.all_7047[pos].type_7047 != 0)
	{
		MessageBox(L"请先选择一条丢失记录！");
		return;
	}

	CLostItemDlg_7047 dlg;
	Item_7047 oldItem = m_book_7047.all_7047[pos];
	dlg.m_name_7047 = oldItem.name_7047;
	dlg.m_category_7047 = oldItem.category_7047;
	dlg.m_description_7047 = oldItem.description_7047;
	dlg.m_location_7047 = oldItem.location_7047;
	dlg.m_date_7047 = oldItem.date_7047;
	dlg.m_personName_7047 = oldItem.personName_7047;
	dlg.m_phone_7047 = oldItem.phone_7047;
	if (dlg.DoModal() != IDOK)
		return;

	Item_7047 item = oldItem;
	item.name_7047 = dlg.m_name_7047;
	item.category_7047 = dlg.m_category_7047;
	item.description_7047 = dlg.m_description_7047;
	item.location_7047 = dlg.m_location_7047;
	item.date_7047 = dlg.m_date_7047;
	item.personName_7047 = dlg.m_personName_7047;
	item.phone_7047 = dlg.m_phone_7047;
	if (!m_book_7047.modifyItem_7047(pos, item))
	{
		MessageBox(L"修改失败：请检查必填内容和真实日期，或检查数据文件是否能够保存。");
		return;
	}
	showItems_7047();
	MessageBox(L"修改成功！");
}

void CLostFound2Dlg_7047::OnBnClickedModifyFound_7047()
{
	int pos = getFoundSelectedIndex_7047();
	if (pos == -1 || m_book_7047.all_7047[pos].type_7047 != 1)
	{
		MessageBox(L"请先选择一条捡到记录！");
		return;
	}

	CFoundItemDlg_7047 dlg;
	Item_7047 oldItem = m_book_7047.all_7047[pos];
	dlg.m_name_7047 = oldItem.name_7047;
	dlg.m_category_7047 = oldItem.category_7047;
	dlg.m_description_7047 = oldItem.description_7047;
	dlg.m_location_7047 = oldItem.location_7047;
	dlg.m_date_7047 = oldItem.date_7047;
	dlg.m_personName_7047 = oldItem.personName_7047;
	dlg.m_phone_7047 = oldItem.phone_7047;
	if (dlg.DoModal() != IDOK)
		return;

	Item_7047 item = oldItem;
	item.name_7047 = dlg.m_name_7047;
	item.category_7047 = dlg.m_category_7047;
	item.description_7047 = dlg.m_description_7047;
	item.location_7047 = dlg.m_location_7047;
	item.date_7047 = dlg.m_date_7047;
	item.personName_7047 = dlg.m_personName_7047;
	item.phone_7047 = dlg.m_phone_7047;
	if (!m_book_7047.modifyItem_7047(pos, item))
	{
		MessageBox(L"修改失败：请检查必填内容和真实日期，或检查数据文件是否能够保存。");
		return;
	}
	showItems_7047();
	MessageBox(L"修改成功！");
}

void CLostFound2Dlg_7047::OnBnClickedDeleteLost_7047()
{
	int pos = getLostSelectedIndex_7047();
	if (pos == -1 || m_book_7047.all_7047[pos].type_7047 != 0)
	{
		MessageBox(L"请先选择一条丢失记录！");
		return;
	}
	if (m_book_7047.delItem_7047(pos))
	{
		showItems_7047();
		MessageBox(L"删除成功！");
	}
	else
		MessageBox(L"删除失败：数据文件无法保存。");
}

void CLostFound2Dlg_7047::OnBnClickedDeleteFound_7047()
{
	int pos = getFoundSelectedIndex_7047();
	if (pos == -1 || m_book_7047.all_7047[pos].type_7047 != 1)
	{
		MessageBox(L"请先选择一条捡到记录！");
		return;
	}
	if (m_book_7047.delItem_7047(pos))
	{
		showItems_7047();
		MessageBox(L"删除成功！");
	}
	else
		MessageBox(L"删除失败：数据文件无法保存。");
}

void CLostFound2Dlg_7047::OnBnClickedQuery_7047()
{
	CQueryDlg_7047 dlg;
	if (dlg.DoModal() != IDOK)
		return;
	dlg.m_keyword_7047.Trim();
	if (dlg.m_keyword_7047.IsEmpty())
	{
		MessageBox(L"请输入查询关键词！");
		return;
	}

	int resultPos[N];
	int type = dlg.m_type_7047 - 1;
	int resultCnt = m_book_7047.queryItem_7047(dlg.m_keyword_7047, type, resultPos);
	showQueryResult_7047(resultPos, resultCnt);
	if (resultCnt == 0)
		MessageBox(L"未找到相关物品！");
}

void CLostFound2Dlg_7047::OnBnClickedMatch_7047()
{
	int lostPos = getLostSelectedIndex_7047();
	if (lostPos == -1 || m_book_7047.all_7047[lostPos].type_7047 != 0)
	{
		MessageBox(L"请先选择一条丢失记录！");
		return;
	}
	if (m_book_7047.all_7047[lostPos].status_7047 != 0)
	{
		MessageBox(L"已完成的记录不能再次匹配！");
		return;
	}

	m_matchCnt_7047 = m_book_7047.matchItem_7047(lostPos, m_matches_7047);
	if (m_matchCnt_7047 == 0)
	{
		m_currentLostPos_7047 = -1;
		showMatchResult_7047();
		MessageBox(L"当前没有待处理的捡到物品，可先登记后再认领！");
		return;
	}

	m_currentLostPos_7047 = lostPos;
	showMatchResult_7047();
	CString message;
	message.Format(L"已列出%d条待处理捡到记录，匹配分仅供参考，请人工核对后确认认领。", m_matchCnt_7047);
	MessageBox(message, L"匹配完成");
}

void CLostFound2Dlg_7047::OnBnClickedClaim_7047()
{
	// 捡到记录是必选；丢失记录可以没有，适应“先捡到、后登记丢失”的实际流程。
	int foundPos = getFoundSelectedIndex_7047();
	if (foundPos == -1 || m_book_7047.all_7047[foundPos].type_7047 != 1 ||
		m_book_7047.all_7047[foundPos].status_7047 != 0)
	{
		MessageBox(L"请在右侧选择一条待处理的捡到记录！");
		return;
	}

	int lostPos = getLostSelectedIndex_7047();
	// 如果匹配后左侧没有选中行，再使用本次匹配保存的丢失下标。
	if (lostPos == -1)
		lostPos = m_currentLostPos_7047;
	if (lostPos < 0 || lostPos >= m_book_7047.cnt_7047 ||
		m_book_7047.all_7047[lostPos].type_7047 != 0 ||
		m_book_7047.all_7047[lostPos].status_7047 != 0)
		lostPos = -1;

	CString text;
	if (lostPos >= 0)
	{
		text = L"确认将“" + m_book_7047.all_7047[foundPos].name_7047 +
			L"”归还给“" + m_book_7047.all_7047[lostPos].personName_7047 + L"”吗？";
	}
	else
	{
		text = L"当前没有对应的丢失登记，确认将“" +
			m_book_7047.all_7047[foundPos].name_7047 + L"”标记为已认领吗？";
	}
	if (MessageBox(text, L"认领确认", MB_YESNO | MB_ICONQUESTION) != IDYES)
		return;

	if (m_book_7047.claimItem_7047(lostPos, foundPos))
	{
		MessageBox(L"认领成功！");
		showItems_7047();
	}
	else
	{
		MessageBox(L"认领失败：记录可能已经处理，或数据文件无法保存！");
	}
}

void CLostFound2Dlg_7047::OnBnClickedClear_7047()
{
	if (m_book_7047.clearBook_7047())
	{
		showItems_7047();
		MessageBox(L"已经清空全部记录！");
	}
	else
		MessageBox(L"清空失败：数据文件无法保存。");
}

void CLostFound2Dlg_7047::OnBnClickedRefresh_7047()
{
	if (!m_book_7047.loadBook_7047())
	{
		MessageBox(L"数据文件损坏或无法读取；原文件仍然保留。", L"数据提示", MB_OK | MB_ICONWARNING);
		return;
	}
	showItems_7047();
}

void CLostFound2Dlg_7047::OnBnClickedExit_7047()
{
	OnCancel();
}

void CLostFound2Dlg_7047::OnLvnItemchangedListLost_7047(NMHDR* pNMHDR, LRESULT* pResult)
{
	updateLostDetail_7047();
	*pResult = 0;
}

void CLostFound2Dlg_7047::OnLvnItemchangedListFound_7047(NMHDR* pNMHDR, LRESULT* pResult)
{
	updateFoundDetail_7047();
	*pResult = 0;
}

void CLostFound2Dlg_7047::OnNMCustomdrawListLost_7047(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVCUSTOMDRAW draw = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	if (draw->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}
	if (draw->nmcd.dwDrawStage == CDDS_ITEMPREPAINT && m_currentLostPos_7047 >= 0)
	{
		int row = (int)draw->nmcd.dwItemSpec;
		int pos = (int)m_listLost_7047.GetItemData(row);
		if (pos == m_currentLostPos_7047)
		{
			draw->clrText = RGB(20, 70, 130);
			draw->clrTextBk = RGB(220, 235, 255);
		}
	}
	*pResult = CDRF_DODEFAULT;
}

void CLostFound2Dlg_7047::OnNMCustomdrawListFound_7047(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVCUSTOMDRAW draw = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	if (draw->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}
	if (draw->nmcd.dwDrawStage == CDDS_ITEMPREPAINT && m_matchCnt_7047 > 0)
	{
		int row = (int)draw->nmcd.dwItemSpec;
		int score = _ttoi(m_listFound_7047.GetItemText(row, 6));
		if (score == 4)
		{
			draw->clrText = RGB(0, 95, 45);
			draw->clrTextBk = RGB(198, 239, 206);
		}
		else if (score == 3)
		{
			draw->clrText = RGB(45, 80, 15);
			draw->clrTextBk = RGB(226, 239, 218);
		}
		else if (score == 2)
		{
			draw->clrText = RGB(125, 80, 0);
			draw->clrTextBk = RGB(255, 242, 204);
		}
	}
	*pResult = CDRF_DODEFAULT;
}
