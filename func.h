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



void Floor::set_node_cost(Node* node,bool consider_dist) {

	int x = node->cel->loc.x;
	int y = node->cel->loc.y;
	
	if (consider_dist) {

		if (walkable(x + 1, y)) {
			if (left_step() == 0 && map[y][x + 1] == home) {
				node->cost[0] = 10000;
				cur_step = 0;
			}
			else if (map[y][x + 1]->dist > left_step() + 1) node->cost[0] = -1;
			else if (map[y][x + 1]->visited == 1) node->cost[0] = 0;
			else node->cost[0] = map[y][x + 1]->cost;
		}
		else
		{
			node->cost[0] = -1;
		}
		if (walkable(x, y - 1)) {
			if (left_step() == 0 && map[y - 1][x] == home) {
				node->cost[1] = 10000;
				cur_step = 0;
			}
			else if (map[y - 1][x]->dist > left_step() + 1) node->cost[1] = -1;
			else if (map[y - 1][x]->visited == 1) node->cost[1] = 0;
			else node->cost[1] = map[y - 1][x]->cost;
		}
		else
		{
			node->cost[1] = -1;
		}

		if (walkable(x - 1, y)) {
			if (left_step() == 0 && map[y][x - 1] == home) {
				node->cost[2] = 10000;
				cur_step = 0;
			}
			else if (map[y][x - 1]->dist > left_step() + 1) node->cost[2] = -1;
			else if (map[y][x - 1]->visited == 1) node->cost[2] = 0;
			else node->cost[2] = map[y][x - 1]->cost;
		}
		else
		{
			node->cost[2] = -1;
		}

		if (walkable(x, y + 1)) {
			if (left_step() == 0 && map[y + 1][x] == home) {
				node->cost[3] = 10000;
				cur_step = 0;
			}
			else if (map[y + 1][x]->dist > left_step() + 1) node->cost[3] = -1;
			else if (map[y + 1][x]->visited == 1) node->cost[3] = 0;
			else node->cost[3] = map[y + 1][x]->cost;
		}
		else
		{
			node->cost[3] = -1;
		}
	}
	else {
		if (walkable(x + 1, y)) {
			if (map[y][x + 1]->visited == 1) node->cost[0] = 0;
			else node->cost[0] = map[y][x + 1]->cost;
		}
		else node->cost[0] = -1;

		if (walkable(x, y - 1)) {
			if (map[y - 1][x]->visited == 1) node->cost[1] = 0;
			else node->cost[1] = map[y - 1][x]->cost;
		}
		else node->cost[1] = -1;

		if (walkable(x - 1, y)) {
			if (map[y][x - 1]->visited == 1) node->cost[2] = 0;
			else node->cost[2] = map[y][x - 1]->cost;
		}
		else node->cost[2] = -1;

		if (walkable(x, y + 1)) {
			if (map[y + 1][x]->visited == 1) node->cost[3] = 0;
			else node->cost[3] = map[y + 1][x]->cost;
		}
		else node->cost[3] = -1;
	}
}




















Node* Floor::reverse_tree(Node* cur) {
	goto_step = 0;
	int cur_dist = cur->cel->dist;
	if (cur != nullptr ) {
		for (Node* tmp = cur->parent; tmp != nullptr; tmp = tmp->parent) {
			tmp->child = cur;
			cur = tmp;
			goto_step++;
			
		}
	}
	if (goto_step + cur_dist > left_step()) return nullptr;
	return cur;
}


void Floor::debug() {



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

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << map[i][j]->visited;
		}
		cout << endl;
	}
	cout << endl;							// visited




	stack<Node*> s;
	// path
	cout << "----------------------------PATH---------------------" << endl;
	int step = 0;

	Node* cur = tree.root;
	while (cur != nullptr) {
		cout << cur->cel->loc<<" ";
		cur = cur->child;
		step++;
	}
	cout << endl;
	cout << "There are " << step << " steps in the path" << endl;
	cout << "and there are " << init_unclean_size << " unclean in the map" << endl;
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
