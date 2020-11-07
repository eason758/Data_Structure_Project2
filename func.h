#pragma once

#ifndef FUNC
#define FUNC

#include "class.h"


void Floor::set_node_max_cost(Node* node) {

	int max = 0;
	int x = node->cel->loc.x;
	int y = node->cel->loc.y;

	cout << "\n"<<node->cost[0] << endl;
	max = MAX(max, node->cost[0]);
	cout << "max:" << max << endl;

	cout << node->cost[1] << endl;
	max = MAX(max, node->cost[1]);
	cout << "max:" << max << endl;

	cout << node->cost[2] << endl;
	max = MAX(max, node->cost[2]);
	cout << "max:" << max << endl;
	
	cout << node->cost[3] << endl;
	max = MAX(max, node->cost[3]);
	cout << "max:" << max << endl;
	
	node->max_cost =  max;
}

bool Floor::visited(Node* node, int x, int y) {

	int n_x = node->cel->loc.x;
	int n_y = node->cel->loc.y;

	if (walkable(n_x + x, n_y + y)) {

		for (vector<int>::iterator it = node->branch.begin(); it != node->branch.end(); it++) {
			if (map[n_y + y][n_x + x]->visited_branches.count(*it)) {
				return true;
			}
		}

	}
	return false;
}

void Floor::set_node_cost(Node* node) {

	int x = node->cel->loc.x;
	int y = node->cel->loc.y;
	cout << "			(" << y << " , " << x << ")";
	// is it visited?

	if (visited(node, 1, 0)) node->cost[0] = 0;
	else node->cost[0] = map[y][x + 1]->cost;

	if (visited(node, 0, -1)) node->cost[1] = 0;
	else node->cost[1] = map[y - 1][x]->cost;

	if (visited(node, -1, 0)) node->cost[2] = 0;
	else node->cost[2] = map[y][x - 1]->cost;

	if (visited(node, 0, 1)) node->cost[3] = 0;
	else node->cost[3] = map[y + 1][x]->cost;

}























void Floor::debug() {

	cout << endl;

	cout << "total branch: "<<tree.total_branch << endl;
	cout << "branch : "<< tree.cur_branch << endl;

	cout << endl;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << (*map[i][j]).attr<<" ";
		}
		cout << endl;
	}
	cout << endl;							// map

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << (*map[i][j]).cost << " ";
		}
		cout << endl;
	}
	cout << endl;							// cost

	for (vector<cell*>::iterator it = unclean.begin(); it != unclean.end(); it++) 
		cout << (**it).loc << " ";

	cout << endl;							// unclean


	cout << "-----------------------------------------------------" << endl;
	for (Node* cur = tree.root; cur != nullptr; cur = cur->child[0]) {
		cout << cur->cel->loc <<" ";
	}
	cout << endl;
	cout << "-----------------------------------------------------" << endl;

	cout << "home : " << (*home).loc << endl;


	cout << "\n" << endl;

}

void debug(Floor& floor) {

	cout << "\n" 
		 << "------------debug------------" << endl;

	floor.debug();

	cout << "\n"
		<< "------------debug------------" << endl;

}




#endif
