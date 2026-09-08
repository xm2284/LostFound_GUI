#pragma once
#include <afxstr.h>

#define N 100

// 一条丢失或捡到物品记录。
struct Item_7047
{
	int type_7047;               // 0=丢失，1=捡到
	CString name_7047;           // 物品名称
	int category_7047;           // 类别编号0~6
	CString description_7047;    // 颜色、品牌等特征
	CString location_7047;       // 丢失或捡到地点
	CString date_7047;           // YYYYMMDD
	CString personName_7047;     // 失主或上交人姓名
	CString phone_7047;          // 联系电话
	int status_7047;             // 0=待处理，1=已完成
};

// 一条匹配候选，只记录双方下标和匹配分。
struct MatchResult_7047
{
	int lostIndex_7047;
	int foundIndex_7047;
	int score_7047;
};
