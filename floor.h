#pragma once

#ifndef FLOOR
#define FLOOR

#include "class.h"

#define MAX(a,b) ((a>b) ? a : b ) 

void Floor::init(int r, int c, int b) {

	row = r;
	col = c;
	battery = b;
	min_step = 1000000000;
	cur_step = 0;


	map = new cell**[row];
	for (int i = 0; i < row; i++) map[i] = new cell*[col];

	
	char block;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> block;
			if (block == '1') map[i][j] = new cell(coor(i, j), WALL, -1);
			else if(block == '0') 
			{
				map[i][j] = new cell(coor(i, j), ROAD, 0);
				unclean.push_back(map[i][j]);
			}
			else home = map[i][j] = new cell(coor(i, j), HOME, 0);
		}
	}


	int co;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> co;
			map[i][j]->cost = co;
		}
	}


	tree.total_branch = 1;












}



//在此假設battery無限 (battery有限之後再改)
//貪婪:每條走可以把最多格填滿就是最好路徑
//步驟:
//把所有可以走的cell 都記起來(在哪裡 這是第幾步) 然後比較彼此之間的數值
//數值:(跟R越遠越好 - 是否走過*10000)  問題:怎麼知道他跟R的距離? 每次都用A*?
//
//取最大值的那幾個當作child, 記錄在queue裡面
//
//while loop取queue的所有Node 每一個Node個別再執行一次(這個while在 clear()中)
//他們所產生的child 都比較彼此之間的數值(亦即 同一個height 的node 都比較彼此的數值
//來決定要不要留)
//
//如果每個node都只能走到"走過"的格子 就
//
//
//
//
//
//while 直到 queue空了
//
//最後順利到達R的(如果有非最大值的child 就會死在路中央) 記錄他從leaf到root的step
//如果是 min 就紀錄順序
//繼續找有沒有其他順利到達R的 然後再執行前兩行


void Floor::clear(){



	do
	{
		walk();
	} while (0);

}

void Floor::walk() {

	int flag = 24;

	tree.set_root(new Node(home));
	tree.leaves.push_back(tree.get_root());

	tree.cur_branch = 1;
																				// 問題: 回不去家裡
	while (flag--)
	{
		cout << "flag: " << flag << endl;
		bool max_max_cost_is_zero = true;
		int new_branch = 0;
		

		// set node cost and check whether max_max = 0
		for (int i = 0; i < tree.cur_branch; i++)
		{
			set_node_cost(tree.leaves[i]);
			set_node_max_cost(tree.leaves[i]);

			if (tree.leaves[i]->max_cost > 0)
				max_max_cost_is_zero = false;
		}

		if (max_max_cost_is_zero) {

			cout << "\na!\n" << endl;
			//                  A*


		}
		else {
			vector<Node*> new_leaves;
			
			for (int i = 0 ; i < tree.cur_branch; i++)
			{
				int x = tree.leaves[i]->cel->loc.x;
				int y = tree.leaves[i]->cel->loc.y;		// current cell position

				int child = 0;
				vector<int> master_branch = tree.leaves[i]->branch;
				
				if (tree.leaves[i]->cost[0] == tree.leaves[i]->max_cost && tree.leaves[i]->max_cost != 0)
				{// one of max_grid
				
					//set child & parent
					tree.leaves[i]->child[child] = 
						new Node(map[y][x + 1], tree.leaves[i]);
					
					// set branch number
					tree.leaves[i]->child[child]->branch = master_branch;
					tree.leaves[i]->child[child]->branch.push_back(tree.total_branch);
					
					// set cell branch_visit
					tree.leaves[i]->child[child]->cel->visited_branches.insert(tree.total_branch++);
					
					//set same level vector
					new_leaves.push_back(tree.leaves[i]->child[child++]);

					new_branch++;
				}

				if (tree.leaves[i]->cost[1] == tree.leaves[i]->max_cost && tree.leaves[i]->max_cost != 0)
				{// one of max_grid
				
					//set child & parent
					tree.leaves[i]->child[child] =
						new Node(map[y - 1][x], tree.leaves[i]);

					// set branch number
					tree.leaves[i]->child[child]->branch = master_branch;
					tree.leaves[i]->child[child]->branch.push_back(tree.total_branch);

					// set cell branch_visit
					tree.leaves[i]->child[child]->cel->visited_branches.insert(tree.total_branch++);

					//set same level vector
					new_leaves.push_back(tree.leaves[i]->child[child++]);

					new_branch++;
				}

				if (tree.leaves[i]->cost[2] == tree.leaves[i]->max_cost && tree.leaves[i]->max_cost != 0)
				{/// one of max_grid
				
					//set child & parent
					tree.leaves[i]->child[child] =
						new Node(map[y][x - 1], tree.leaves[i]);

					// set branch number
					tree.leaves[i]->child[child]->branch = master_branch;
					tree.leaves[i]->child[child]->branch.push_back(tree.total_branch);

					// set cell branch_visit
					tree.leaves[i]->child[child]->cel->visited_branches.insert(tree.total_branch++);

					//set same level vector
					new_leaves.push_back(tree.leaves[i]->child[child++]);

					new_branch++;
				}

				if (tree.leaves[i]->cost[3] == tree.leaves[i]->max_cost && tree.leaves[i]->max_cost != 0)
				{// one of max_grid
				
					//set child & parent
					tree.leaves[i]->child[child] =
						new Node(map[y + 1][x], tree.leaves[i]);

					// set branch number
					tree.leaves[i]->child[child]->branch = master_branch;
					tree.leaves[i]->child[child]->branch.push_back(tree.total_branch);

					// set cell branch_visit
					tree.leaves[i]->child[child]->cel->visited_branches.insert(tree.total_branch++);

					//set same level vector
					new_leaves.push_back(tree.leaves[i]->child[child++]);

					new_branch++;
				}

			}
			
			tree.leaves = new_leaves;

		}
		
		tree.cur_branch = new_branch;

	}


}


bool Floor::walkable(int x, int y) {

	if (x < 0 || x >= col || y < 0 || y >= row) return false;
	if ((*map[y][x]).attr == WALL) return false;
	else return true;

}


#endif
