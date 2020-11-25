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
				unclean_size++;
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
				unclean_size++;
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
				unclean_size++;
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
				unclean_size++;
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









void myheap::push(Node* node) {
	//cout << "push" << endl;
	int cur_index = heap.size();
	heap.push_back(node);
	if (cur_index != 0) {
		while (smaller_than(heap[cur_index], heap[(cur_index + 1) / 2 - 1])) {
			Node* tmp = heap[(cur_index + 1) / 2 - 1];
			heap[(cur_index + 1) / 2 - 1] = heap[cur_index];
			heap[cur_index] = tmp;
			cur_index = (cur_index + 1) / 2 - 1;
			if (cur_index == 0) break;
		}
	}
	//cout << "push end" << endl;
}
void myheap::pop() {
	//cout << "pop" << endl;
	if (heap.empty()) {
		cout << "heap empty" << endl;
		exit(1);
	}
	else if (heap.size() == 1) heap.pop_back();
	else {
		int cur_index = 0;
		heap[0] = heap.back();
		heap.pop_back();
		int min_index;
		while (1) {
			if (int(heap.size()) < (cur_index + 1) * 2) break;
			else if (int(heap.size()) < (cur_index + 1) * 2 + 1) min_index = (cur_index + 1) * 2 - 1;
			else if (smaller_than(heap[(cur_index + 1) * 2], heap[(cur_index + 1) * 2 - 1])) min_index = (cur_index + 1) * 2;
			else min_index = (cur_index + 1) * 2 - 1 ;
			if (smaller_than(heap[min_index], heap[cur_index])) {
				Node* tmp = heap[min_index];
				heap[min_index] = heap[cur_index];
				heap[cur_index] = tmp;
				cur_index = min_index;
			}
			else break;
		}

	}
	//cout << "pop end" << endl;
}

bool myheap::smaller_than(Node* lhs, Node* rhs) {
	return ((abs(lhs->cel->loc.x - dest.x) + abs(lhs->cel->loc.y - dest.y)) < (abs(rhs->cel->loc.x - dest.x) + abs(rhs->cel->loc.y - dest.y)));
}





#endif
