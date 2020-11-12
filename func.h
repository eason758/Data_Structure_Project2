#pragma once

#ifndef FUNC
#define FUNC

#include "class.h"


void Floor::set_node_max_cost(Node* node,bool consider_dist) {

	int max = 0;
	int x = node->cel->loc.x;
	int y = node->cel->loc.y;


	max = MAX(max, node->cost[0]);
	max = MAX(max, node->cost[1]);
	max = MAX(max, node->cost[2]);
	max = MAX(max, node->cost[3]);

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

void Floor::set_node_cost(Node* node,bool consider_dist) {

	int x = node->cel->loc.x;
	int y = node->cel->loc.y;
	
	if (consider_dist) {
		if (map[y][x + 1]->dist > left_step()) node->cost[0] = -1;
		else if (visited(node, 1, 0)) node->cost[0] = 0;
		else if (walkable(x + 1, y))node->cost[0] = map[y][x + 1]->cost;

		if (map[y - 1][x]->dist > left_step()) node->cost[1] = -1;
		else if (visited(node, 0, -1)) node->cost[1] = 0;
		else if (walkable(x, y - 1))node->cost[1] = map[y - 1][x]->cost;

		if (map[y][x - 1]->dist > left_step()) node->cost[2] = -1;
		else if (visited(node, -1, 0)) node->cost[2] = 0;
		else if (walkable(x - 1, y))node->cost[2] = map[y][x - 1]->cost;

		if (map[y + 1][x]->dist > left_step()) node->cost[3] = -1;
		else if (visited(node, 0, 1)) node->cost[3] = 0;
		else if (walkable(x, y + 1))node->cost[3] = map[y + 1][x]->cost;
	}
	else {
		// is it visited?
		if (visited(node, 1, 0)) node->cost[0] = 0;
		else if (walkable(x + 1, y))node->cost[0] = map[y][x + 1]->cost;

		if (visited(node, 0, -1)) node->cost[1] = 0;
		else if (walkable(x, y - 1))node->cost[1] = map[y - 1][x]->cost;

		if (visited(node, -1, 0)) node->cost[2] = 0;
		else if (walkable(x - 1, y))node->cost[2] = map[y][x - 1]->cost;

		if (visited(node, 0, 1)) node->cost[3] = 0;
		else if (walkable(x, y + 1))node->cost[3] = map[y + 1][x]->cost;
	}
}




















Node* reverse_tree(Node* cur) {
	if (cur != nullptr ) {
		for (Node* tmp = cur->parent; tmp != nullptr; tmp = tmp->parent) {
			tmp->child[0] = cur;
			cur = tmp;
		}
	}
	return cur;
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
			cout << map[i][j]->cost << " ";
		}
		cout << endl;
	}
	cout << endl;							// cost

	for (vector<cell*>::iterator it = unclean.begin(); it != unclean.end(); it++) 
		cout << (**it).loc << " ";

	cout << endl;							// unclean


	stack<Node*> s;
	// path
	cout << "----------------------------PATH---------------------" << endl;
	int step = 0;
	for (Node* cur = finalNode; cur != nullptr; cur = cur->parent) {
		s.push(cur);
		step++;
	}

	while (!s.empty()) {
		cout << s.top()->cel->loc <<" ";
		s.pop();
	}
	cout << endl;
	cout << "There are " << step << " steps in the path" << endl;
	cout << "and there are " << unclean.size() << " unclean in the map" << endl;
	cout << "----------------------------PATH---------------------" << endl;

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
