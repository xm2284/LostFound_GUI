#pragma once
#include <afx.h>
#include "Item.h"

class LostFoundBook_7047
{
public:
	Item_7047 all_7047[N];
	int cnt_7047;

	LostFoundBook_7047();
	bool addItem_7047(Item_7047 item);                                  // 增加一条记录
	bool modifyItem_7047(int pos, Item_7047 item);                      // 修改指定下标的记录
	bool delItem_7047(int pos);                                    // 删除指定下标的记录
	int queryItem_7047(CString keyword, int type, int resultPos[]); // 查询并返回真实下标
	int matchItem_7047(int lostPos, MatchResult_7047 results[]);         // 列出全部待处理候选并按分数排序
	bool claimItem_7047(int lostPos, int foundPos);                 // 捡到必选，丢失可选，不强制匹配分
	bool clearBook_7047();                                          // 清空并保存，成功返回true
	bool loadBook_7047();                                           // 加载成功或文件不存在返回true
	bool saveBook_7047();                                           // 保存成功返回true

private:
	void normalizeItem_7047(Item_7047& item);                  // 去掉文本字段首尾空格
	bool isDateFormat_7047(CString date);                 // 判断日期是否为8位数字
	bool isValidItem_7047(Item_7047 item);                    // 统一检查记录范围、必填项和长度
	bool isRelated_7047(CString a, CString b);           // 判断两个名称或地点是否存在包含关系
	int getMatchScore_7047(int lostPos, int foundPos);   // 按类别、名称、地点和日期计算0~4分
	void writeString_7047(CFile& file, CString text);    // 按“长度+内容”写入一个CString
	bool readString_7047(CFile& file, CString& text);    // 按相同格式读取并检查文件数据
};
