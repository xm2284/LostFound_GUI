#include "pch.h"
#include "LostFoundBook.h"

// 数据文件固定放在exe旁边，避免不同启动目录产生多份数据。
static CString getDataFilePath()
{
	WCHAR modulePath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, modulePath, MAX_PATH);
	CString path = modulePath;
	int pos = path.ReverseFind(L'\\');
	if (pos >= 0)
		path = path.Left(pos + 1);
	return path + L"lostfound_gui.dat";
}

LostFoundBook_7047::LostFoundBook_7047()
{
	cnt_7047 = 0;
}

void LostFoundBook_7047::normalizeItem_7047(Item_7047& item)
{
	item.name_7047.Trim();
	item.description_7047.Trim();
	item.location_7047.Trim();
	item.date_7047.Trim();
	item.personName_7047.Trim();
	item.phone_7047.Trim();
}

bool LostFoundBook_7047::isDateFormat_7047(CString date)
{
	// 先检查长度，再逐个检查字符，避免把字母等内容当作日期。
	if (date.GetLength() != 8)
		return false;

	for (int i = 0; i < 8; i++)
	{
		if (date[i] < L'0' || date[i] > L'9')
			return false;
	}

	int year = _ttoi(date.Left(4));
	int month = _ttoi(date.Mid(4, 2));
	int day = _ttoi(date.Right(2));
	if (month < 1 || month > 12)
		return false;

	int daysOfMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	bool leapYear = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
	if (leapYear)
		daysOfMonth[1] = 29;
	return day >= 1 && day <= daysOfMonth[month - 1];
}

bool LostFoundBook_7047::isValidItem_7047(Item_7047 item)
{
	normalizeItem_7047(item);
	// 所有新增、修改和文件读取的数据都从这里经过，保证数据规则一致。
	if (item.type_7047 < 0 || item.type_7047 > 1)
		return false;
	if (item.category_7047 < 0 || item.category_7047 > 6)
		return false;
	if (item.status_7047 < 0 || item.status_7047 > 1)
		return false;
	if (item.name_7047.IsEmpty() || item.description_7047.IsEmpty() ||
		item.location_7047.IsEmpty() || !isDateFormat_7047(item.date_7047) ||
		item.personName_7047.IsEmpty() || item.phone_7047.IsEmpty())
		return false;
	if (item.name_7047.GetLength() > 39 || item.description_7047.GetLength() > 199 ||
		item.location_7047.GetLength() > 59 || item.personName_7047.GetLength() > 19 ||
		item.phone_7047.GetLength() > 19)
		return false;
	return true;
}

bool LostFoundBook_7047::addItem_7047(Item_7047 item)
{
	normalizeItem_7047(item);
	item.status_7047 = 0;
	if (cnt_7047 >= N || !isValidItem_7047(item))
		return false;

	all_7047[cnt_7047] = item;
	cnt_7047++;
	if (!saveBook_7047())
	{
		cnt_7047--;
		return false;
	}
	return true;
}

bool LostFoundBook_7047::modifyItem_7047(int pos, Item_7047 item)
{
	if (pos < 0 || pos >= cnt_7047)
		return false;

	normalizeItem_7047(item);
	// 修改普通字段时不改变记录类型和处理状态。
	item.type_7047 = all_7047[pos].type_7047;
	item.status_7047 = all_7047[pos].status_7047;
	if (!isValidItem_7047(item))
		return false;

	Item_7047 oldItem = all_7047[pos];
	all_7047[pos] = item;
	if (!saveBook_7047())
	{
		all_7047[pos] = oldItem;
		return false;
	}
	return true;
}

bool LostFoundBook_7047::delItem_7047(int pos)
{
	if (pos < 0 || pos >= cnt_7047)
		return false;

	Item_7047 deletedItem = all_7047[pos];
	// 删除数组中间记录后，后面的记录依次向前移动一格。
	for (int i = pos; i < cnt_7047 - 1; i++)
		all_7047[i] = all_7047[i + 1];

	cnt_7047--;
	if (!saveBook_7047())
	{
		for (int i = cnt_7047; i > pos; i--)
			all_7047[i] = all_7047[i - 1];
		all_7047[pos] = deletedItem;
		cnt_7047++;
		return false;
	}
	return true;
}

int LostFoundBook_7047::queryItem_7047(CString keyword, int type, int resultPos[])
{
	keyword.Trim();
	if (keyword.IsEmpty())
		return 0;

	int resultCnt = 0;
	for (int i = 0; i < cnt_7047; i++)
	{
		// type=-1表示全部，0表示丢失，1表示捡到。
		if (type != -1 && all_7047[i].type_7047 != type)
			continue;

		if (all_7047[i].name_7047.Find(keyword) >= 0 ||
			all_7047[i].location_7047.Find(keyword) >= 0)
		{
			// 保存真实数组下标，筛选后的列表仍能正确执行修改和删除。
			resultPos[resultCnt] = i;
			resultCnt++;
		}
	}
	return resultCnt;
}

bool LostFoundBook_7047::isRelated_7047(CString a, CString b)
{
	a.Trim();
	b.Trim();
	if (a.IsEmpty() || b.IsEmpty())
		return false;
	// 单字符和占位词不参加匹配，避免“1”匹配“17号楼”。
	if (a.GetLength() < 2 || b.GetLength() < 2 ||
		a == L"无" || b == L"无" ||
		a == L"未知" || b == L"未知" ||
		a == L"不详" || b == L"不详")
		return false;

	// 任意一方包含另一方就算相关，例如“蓝牙耳机”和“耳机”。
	if (a.Find(b) >= 0)
		return true;
	if (b.Find(a) >= 0)
		return true;
	return false;
}

int LostFoundBook_7047::getMatchScore_7047(int lostPos, int foundPos)
{
	// 类别不同直接排除；类别相同先得1分。
	if (all_7047[lostPos].category_7047 != all_7047[foundPos].category_7047)
		return 0;

	int score = 1;
	if (isRelated_7047(all_7047[lostPos].name_7047, all_7047[foundPos].name_7047))
		score++;
	if (isRelated_7047(all_7047[lostPos].location_7047, all_7047[foundPos].location_7047))
		score++;
	if (all_7047[lostPos].date_7047 == all_7047[foundPos].date_7047)
		score++;
	return score;
}

int LostFoundBook_7047::matchItem_7047(int lostPos, MatchResult_7047 results[])
{
	if (lostPos < 0 || lostPos >= cnt_7047 ||
		all_7047[lostPos].type_7047 != 0 || all_7047[lostPos].status_7047 != 0)
		return 0;

	int resultCnt = 0;
	for (int i = 0; i < cnt_7047; i++)
	{
		// 所有待处理的捡到记录都列入候选，匹配分只作排序提示。
		// 最终是否归还由值班室人员人工核对，不由分数硬性拦截。
		if (all_7047[i].type_7047 != 1 || all_7047[i].status_7047 != 0)
			continue;

		int score = getMatchScore_7047(lostPos, i);
		results[resultCnt].lostIndex_7047 = lostPos;
		results[resultCnt].foundIndex_7047 = i;
		results[resultCnt].score_7047 = score;
		resultCnt++;
	}

	// 使用简单排序，把高分候选放在前面。
	for (int i = 0; i < resultCnt - 1; i++)
	{
		for (int j = i + 1; j < resultCnt; j++)
		{
			if (results[j].score_7047 > results[i].score_7047)
			{
				MatchResult_7047 temp = results[i];
				results[i] = results[j];
				results[j] = temp;
			}
		}
	}
	return resultCnt;
}

bool LostFoundBook_7047::claimItem_7047(int lostPos, int foundPos)
{
	if (foundPos < 0 || foundPos >= cnt_7047)
		return false;
	if (all_7047[foundPos].type_7047 != 1 || all_7047[foundPos].status_7047 != 0)
		return false;
	if (lostPos >= 0 && (lostPos >= cnt_7047 ||
		all_7047[lostPos].type_7047 != 0 || all_7047[lostPos].status_7047 != 0))
		return false;
	// 匹配分只用于推荐，确认认领由工作人员人工完成，不强制分数阈值。
	// 有对应丢失记录时同时完成两边；没有时只完成捡到记录。
	if (lostPos >= 0)
		all_7047[lostPos].status_7047 = 1;
	all_7047[foundPos].status_7047 = 1;
	if (!saveBook_7047())
	{
		if (lostPos >= 0)
			all_7047[lostPos].status_7047 = 0;
		all_7047[foundPos].status_7047 = 0;
		return false;
	}
	return true;
}

bool LostFoundBook_7047::clearBook_7047()
{
	int oldCount = cnt_7047;
	cnt_7047 = 0;
	if (!saveBook_7047())
	{
		cnt_7047 = oldCount;
		return false;
	}
	return true;
}

void LostFoundBook_7047::writeString_7047(CFile& file, CString text)
{
	// CString长度不固定，所以先保存字符数，再保存实际字符。
	int length = text.GetLength();
	file.Write(&length, sizeof(int));
	if (length > 0)
		file.Write((LPCTSTR)text, length * sizeof(TCHAR));
}

bool LostFoundBook_7047::readString_7047(CFile& file, CString& text)
{
	int length = 0;
	if (file.Read(&length, sizeof(int)) != sizeof(int))
		return false;
	// 限制文件中的长度，防止损坏文件给出异常大的数值。
	if (length < 0 || length > 500)
		return false;

	TCHAR buffer[501] = { 0 };
	UINT bytes = length * sizeof(TCHAR);
	if (bytes > 0 && file.Read(buffer, bytes) != bytes)
		return false;

	buffer[length] = 0;
	text = buffer;
	return true;
}

bool LostFoundBook_7047::saveBook_7047()
{
	CString filePath = getDataFilePath();
	CString tempPath = filePath + L".tmp";
	CFile file;
	if (!file.Open(tempPath, CFile::modeCreate | CFile::modeWrite))
		return false;

	try
	{
		// 每条记录按固定顺序写入，读取时必须严格使用同样的顺序。
		file.Write(&cnt_7047, sizeof(int));
		for (int i = 0; i < cnt_7047; i++)
		{
			file.Write(&all_7047[i].type_7047, sizeof(int));
			file.Write(&all_7047[i].category_7047, sizeof(int));
			file.Write(&all_7047[i].status_7047, sizeof(int));
			writeString_7047(file, all_7047[i].name_7047);
			writeString_7047(file, all_7047[i].description_7047);
			writeString_7047(file, all_7047[i].location_7047);
			writeString_7047(file, all_7047[i].date_7047);
			writeString_7047(file, all_7047[i].personName_7047);
			writeString_7047(file, all_7047[i].phone_7047);
		}
		file.Close();
	}
	catch (CFileException* error)
	{
		error->Delete();
		file.Abort();
		DeleteFile(tempPath);
		return false;
	}

	if (!MoveFileEx(tempPath, filePath,
		MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
	{
		DeleteFile(tempPath);
		return false;
	}
	return true;
}

bool LostFoundBook_7047::loadBook_7047()
{
	cnt_7047 = 0;
	CString filePath = getDataFilePath();
	CString openPath = filePath;
	bool loadedLegacyFile = false;
	CFileStatus status;
	if (!CFile::GetStatus(filePath, status))
	{
		if (!CFile::GetStatus(L"lostfound_gui.dat", status))
			return true;
		openPath = L"lostfound_gui.dat";
		loadedLegacyFile = openPath.CompareNoCase(filePath) != 0;
	}

	CFile file;
	if (!file.Open(openPath, CFile::modeRead))
		return false;

	int fileCnt = 0;
	if (file.Read(&fileCnt, sizeof(int)) != sizeof(int) ||
		fileCnt < 0 || fileCnt > N)
	{
		file.Close();
		return false;
	}

	// 任意字段读取失败或内容非法，就放弃整份数据，避免使用半条记录。
	for (int i = 0; i < fileCnt; i++)
	{
		Item_7047 item;
		bool ok = true;
		ok = ok && file.Read(&item.type_7047, sizeof(int)) == sizeof(int);
		ok = ok && file.Read(&item.category_7047, sizeof(int)) == sizeof(int);
		ok = ok && file.Read(&item.status_7047, sizeof(int)) == sizeof(int);
		ok = ok && readString_7047(file, item.name_7047);
		ok = ok && readString_7047(file, item.description_7047);
		ok = ok && readString_7047(file, item.location_7047);
		ok = ok && readString_7047(file, item.date_7047);
		ok = ok && readString_7047(file, item.personName_7047);
		ok = ok && readString_7047(file, item.phone_7047);

		if (!ok || !isValidItem_7047(item))
		{
			cnt_7047 = 0;
			file.Close();
			return false;
		}

		normalizeItem_7047(item);
		all_7047[cnt_7047] = item;
		cnt_7047++;
	}
	file.Close();
	if (loadedLegacyFile && !saveBook_7047())
		return false;
	return true;
}
