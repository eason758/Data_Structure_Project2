#pragma once

#ifndef FUNC
#define FUNC


#include "class.h"


void Floor::debug() {

	cout << endl;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << map[i][j]<<" ";
		}
		cout << endl;
	}
	cout << endl;

	for (vector<coordinate>::iterator it = unclean.begin(); it != unclean.end(); it++) 
		cout << *it << " ";

	cout << "\n" << endl;

}
void Robot::debug() {

	cout << "Battery: "<<battery
		 << " Step: " << step 
		 <<" cur_loc: "<< cur_loc 
		 << endl;

}

void debug(Floor& floor, Robot& robot) {

	cout << "\n" 
		 << "------------debug------------" << endl;

	floor.debug();
	robot.debug();

	cout << "\n"
		<< "------------debug------------" << endl;

}




#endif