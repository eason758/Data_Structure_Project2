#pragma once

#ifndef FLOOR
#define FLOOR

#include "class.h"

void Floor::init(int r, int c) {

	row = r;
	col = c;
	map = new char*[row];
	for (int i = 0; i < row; i++) map[i] = new char;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'R') home = coordinate(i, j);
			if (map[i][j] == '0') unclean.push_back(coordinate(i, j));
		}
	}

}

#endif