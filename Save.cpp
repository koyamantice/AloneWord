#include"Save.h"

//�ÓI�����o�ϐ��̎���
int Save::ClearCount = 5;
bool Save::FirstClear = false;
bool Save::SecondClear = false;
bool Save::ThirdClear = false;
bool Save::FouthClear = false;
bool Save::FifthClear = false;
bool Save::PerfectClear = false;

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

void Save::PerfectSave() {
	PerfectClear = true;
}

//�����o�֐�
void Save::ResetClearSave() {
	ClearCount = 0;
}

void Save::ResetFirstSave() {
	FirstClear = false;
}

void Save::ResetSecondSave() {
	SecondClear = false;
}

void Save::ResetThirdSave() {
	ThirdClear = false;
}

void Save::ResetFouthSave() {
	FouthClear = false;
}

void Save::ResetFifthSave() {
	FifthClear = false;
}

