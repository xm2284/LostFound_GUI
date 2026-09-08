// LostFound2Dlg.h: 头文件
//

#pragma once
#include "afxdialogex.h"
#include "LostFoundBook.h"
#include "resource.h"
#include <afxcmn.h>

class CLostFound2Dlg_7047 : public CDialogEx
{
public:
	CLostFound2Dlg_7047(CWnd* pParent = nullptr);
	enum { IDD = IDD_LOSTFOUND2_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	HICON m_hIcon_7047;

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_listLost_7047;       // 左侧丢失记录列表
	CListCtrl m_listFound_7047;      // 右侧捡到记录或匹配候选列表
	CEdit m_editLostDetail_7047;     // 左侧选中记录的完整信息
	CEdit m_editFoundDetail_7047;    // 右侧选中记录的完整信息
	LostFoundBook_7047 m_book_7047;       // 数据管理对象
	MatchResult_7047 m_matches_7047[N];   // 当前匹配候选
	int m_matchCnt_7047;             // 当前候选数量
	int m_currentLostPos_7047;       // 当前正在匹配的丢失记录下标

	void addColumns_7047();
	void adjustColumnWidths_7047();
	void showItems_7047();
	void showQueryResult_7047(int resultPos[], int resultCnt);
	void showMatchResult_7047();
	void insertLostRow_7047(int pos);
	void insertFoundRow_7047(int pos, int score);
	CString buildItemDetail_7047(int pos);
	void updateLostDetail_7047();
	void updateFoundDetail_7047();
	int getLostSelectedIndex_7047();
	int getFoundSelectedIndex_7047();

	afx_msg void OnBnClickedAddLost_7047();
	afx_msg void OnBnClickedModifyLost_7047();
	afx_msg void OnBnClickedDeleteLost_7047();
	afx_msg void OnBnClickedMatch_7047();
	afx_msg void OnBnClickedAddFound_7047();
	afx_msg void OnBnClickedModifyFound_7047();
	afx_msg void OnBnClickedDeleteFound_7047();
	afx_msg void OnBnClickedClaim_7047();
	afx_msg void OnBnClickedQuery_7047();
	afx_msg void OnBnClickedClear_7047();
	afx_msg void OnBnClickedRefresh_7047();
	afx_msg void OnBnClickedExit_7047();
	afx_msg void OnLvnItemchangedListLost_7047(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnItemchangedListFound_7047(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawListLost_7047(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawListFound_7047(NMHDR* pNMHDR, LRESULT* pResult);
};
