#pragma once

#ifndef ROBOT
#define ROBOT

#include "class.h"

/*

	step�p��X�h�Ĥ@�B~�^�a�����@�B <= battery
	output���ɭ԰O�o�n�houtput�Ĥ@�B�O�a��

*/


void Robot::init(int b,coordinate h){

	battery = b;
	step = 0;
	cur_loc = h;

}




#endif