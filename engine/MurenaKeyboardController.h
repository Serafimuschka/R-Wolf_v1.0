#pragma once

//--------------------------------------------------
//	�����:			MurenaKeyboardController
//	���������:		MurenaKeyboardController
//	��������� ���� ����������� ������� ����������
//	����� ������:	Einhorn32 [������� �����]
//					2018, Einhorn32(c)
//--------------------------------------------------
class MurenaKeyboardController {
	float x, y;
	MurenaKeyboardController() {
		x = 0.0f;
		y = 0.0f;
	}
public:
	static float ArrowHook(char axis, float addition) {
		switch (axis) {
		case 'x':
			x += addition;
			break;
		case 'y':
			y += addition;
			break;
		}
		return x, y;
	}
};