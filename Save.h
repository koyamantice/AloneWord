#pragma once
class Save {
public:
	//メンバ関数
	void ClearSave();
	void FirstSave();
	void SecondSave();
	void ThirdSave();
	void FouthSave();
	void FifthSave();
	void PerfectSave();
	void ResetClearSave();
	void ResetFirstSave();
	void ResetSecondSave();
	void ResetThirdSave();
	void ResetFouthSave();
	void ResetFifthSave();
	//ゲッター
	const int& GetClearCount() { return ClearCount; }
	const bool& GetFirstClear() { return FirstClear; }
	const bool& GetSecondClear() { return SecondClear; }
	const bool& GetThirdClear() { return ThirdClear; }
	const bool& GetFouthClear() { return FouthClear; }
	const bool& GetFifthClear() { return FifthClear; }
	const bool& GetPerfectClear() { return PerfectClear; }
	//静的メンバ変数
	static int ClearCount;
	static bool FirstClear;
	static bool SecondClear;
	static bool ThirdClear;
	static bool FouthClear;
	static bool FifthClear;
	static bool PerfectClear;
};