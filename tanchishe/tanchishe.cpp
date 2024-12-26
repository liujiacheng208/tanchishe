// tanchishe.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <graphics.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 游戏窗口大小
const int WIDTH = 400;
const int HEIGHT = 400;
const int CELL_SIZE = 20;  // 每个格子的大小

// 贪吃蛇的最大长度
const int MAX_SNAKE_LENGTH = (WIDTH / CELL_SIZE) * (HEIGHT / CELL_SIZE);

// 方向数组：上、右、下、左
const int DIR_X[4] = { -1, 0, 1, 0 };
const int DIR_Y[4] = { 0, 1, 0, -1 };

// 贪吃蛇的状态
struct Snake {
    vector<pair<int, int>> body;  // 贪吃蛇的身体坐标
    int dir;  // 当前蛇头的方向
};

// 游戏状态
struct Game {
    Snake snake;
    pair<int, int> food;  // 食物的位置
    bool gameOver;
};

// 初始化游戏
void initGame(Game& game) {
    game.snake.body.clear();
    game.snake.body.push_back({ 10, 10 });  // 初始蛇的位置
    game.snake.dir = 2;  // 初始蛇的方向：向右
    srand((unsigned)time(NULL));
    game.food = { rand() % (WIDTH / CELL_SIZE),rand() % (HEIGHT / CELL_SIZE) };  // 食物的位置
    game.gameOver = false;
}
void darwSnake(Game& game) {
    setfillcolor(GREEN);
	for (auto& p : game.snake.body) {
		bar(p.second * CELL_SIZE, p.first * CELL_SIZE, (p.second + 1) * CELL_SIZE, (p.first + 1) * CELL_SIZE);
	}
}
void darwFood(Game& game) {
	setfillcolor(RED);
	bar(game.food.second * CELL_SIZE, game.food.first * CELL_SIZE, (game.food.second + 1) * CELL_SIZE, (game.food.first + 1) * CELL_SIZE);
}
// 主函数
int main() {
    initgraph(WIDTH, HEIGHT);  // 初始化图形界面

    Game game;
    initGame(game);  // 初始化游戏
	darwSnake(game);
	darwFood(game);  // 绘制食物
    _getch();
    
    return 0;
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
