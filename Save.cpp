#include"Save.h"

//�ÓI�����o�ϐ��̎���
int Save::ClearCount = 0;
bool Save::FirstClear = false;
bool Save::SecondClear = false;
bool Save::ThirdClear = false;
bool Save::FouthClear = false;
bool Save::FifthClear = false;

//�����o�֐�
void Save::ClearSave() {
	ClearCount++;
}

void Save::FirstSave() {
	FirstClear = true;
}


void Save::SecondSave() {
	SecondClear = true;
}

void Save::ThirdSave() {
	ThirdClear = true;
}

void Save::FouthSave() {
	FouthClear = true;
}

void Save::FifthSave() {
	FifthClear = true;
}
