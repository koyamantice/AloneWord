#pragma once
class Save {
public:

	void ClearSave();
	const int& GetClearCount() { return ClearCount; }
	static int ClearCount;
};