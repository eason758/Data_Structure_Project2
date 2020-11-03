#pragma once

#ifndef ROBOT
#define ROBOT

#include "class.h"

/*

	step計算出去第一步~回家的那一步 <= battery
	output的時候記得要多output第一步是家裡

*/


void Robot::init(int b,coordinate h){

	battery = b;
	step = 0;
	cur_loc = h;

}




#endif