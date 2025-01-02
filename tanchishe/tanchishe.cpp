// tanchishe.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//当然可以！以下//是一个简单的贪吃蛇自动寻路算法的C++实现示例。这个算法使用广度优先搜索（BFS）来找到从蛇头到食物的最短路径。

//当然可以！以下是一个使用 EasyX 库实现贪吃蛇自动寻路算法的简单示例。这个示例使用广度优先搜索（BFS）算法来实现自动寻路。

#include <graphics.h>
#include <conio.h>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <ctime>

// 定义表示点的结构体
struct Point {
    int x;
    int y;
    // 比较运算符，用于在map中作为键
    bool operator<(const Point& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

// 定义蛇的移动方向
enum Direction { UP, DOWN, LEFT, RIGHT };
// 定义方向数组，每个方向对应的坐标变化
const Point directions[4] = { {0, -10}, {0, 10}, {-10, 0}, {10, 0} };

// 蛇类
class Snake {
public:
    std::deque<Point> body;  // 蛇身的点的队列
    Direction dir;           // 当前移动方向
    // 构造函数，初始化蛇的起始位置
    Snake(int x, int y) {
        Point head = { x, y };
        body.push_back(head);
        dir = RIGHT;
    }

    // 移动蛇的位置
    void move() {
        Point head = body.front();  // 获取蛇头的位置
        head.x += directions[dir].x;
        head.y += directions[dir].y;
        body.push_front(head);  // 将新的头位置添加到队列前端
        body.pop_back();        // 移除队列末尾的点
    }

    // 增加蛇的长度
    void grow() {
        body.push_back(body.back());  // 在蛇尾增加一个点
    }

    // 绘制蛇
    void draw() {
        setfillcolor(GREEN);
        for (const Point& p : body) {
            fillrectangle(p.x, p.y, p.x + 10, p.y + 10);  // 绘制每一个蛇身的点
        }
    }

    // 改变蛇的移动方向
    void changeDirection(Direction newDir) {
        dir = newDir;
    }

    // 获取蛇头的位置
    Point getHead() const {
        return body.front();
    }
};

// 广度优先搜索 (BFS) 寻找路径
bool bfs(Point start, Point food, std::vector<std::vector<bool>>& visited, std::queue<Direction>& path) {
    std::queue<Point> q;
    std::map<Point, Point> parent;  // 用于记录每个点的前驱点
    q.push(start);
    visited[start.y / 10][start.x / 10] = true;

    // BFS 算法主循环
    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        // 如果找到了食物
        if (current.x == food.x && current.y == food.y) {
            // 回溯路径
            while (current.x != start.x || current.y != start.y) {
                Point prev = parent[current];
                if (prev.x == current.x) {
                    path.push((prev.y < current.y) ? DOWN : UP);
                }
                else {
                    path.push((prev.x < current.x) ? RIGHT : LEFT);
                }
                current = prev;
            }
            return true;
        }

        // 遍历所有可能的移动方向
        for (int i = 0; i < 4; ++i) {
            Point next = { current.x + directions[i].x, current.y + directions[i].y };

            // 检查下一个点是否在范围内且未访问过
            if (next.x >= 0 && next.x < 640 && next.y >= 0 && next.y < 480 && !visited[next.y / 10][next.x / 10]) {
                q.push(next);
                visited[next.y / 10][next.x / 10] = true;
                parent[next] = current;  // 记录前驱点
            }
        }
    }

    return false;
}

// 随机生成食物位置
Point generateRandomFood() {
    int x = (rand() % 64) * 10;  // 随机生成 x 坐标
    int y = (rand() % 48) * 10;  // 随机生成 y 坐标
    return { x, y };
}

int main() {
    // 初始化图形窗口
    initgraph(640, 480);
    setbkcolor(WHITE);  // 设置背景色
    cleardevice();
    srand(time(0));  // 初始化随机数种子

    Snake snake(100, 100);  // 创建蛇对象
    Point food = generateRandomFood();  // 生成初始食物位置
    std::queue<Direction> path;  // 用于存储蛇的移动路径

    while (true) {
        // 开始批量绘制
        BeginBatchDraw();

        // 清除屏幕
        cleardevice();

        // 创建并初始化访问矩阵
        std::vector<std::vector<bool>> visited(48, std::vector<bool>(64, false));
        if (path.empty() && !bfs(snake.getHead(), food, visited, path)) {
            break;  // 无法找到路径，结束游戏
        }

        if (!path.empty()) {
            snake.changeDirection(path.front());
            path.pop();
        }

        snake.move();

        // 检查蛇是否吃到食物
        if (snake.getHead().x == food.x && snake.getHead().y == food.y) {
            snake.grow();  // 增加蛇的长度
            food = generateRandomFood();  // 生成新的食物位置
        }

        // 绘制蛇和食物
        snake.draw();
        setfillcolor(RED);
        fillrectangle(food.x, food.y, food.x + 10, food.y + 10);

        // 结束批量绘制
        EndBatchDraw();

        Sleep(100);  // 控制蛇的移动速度
    }

    closegraph();  // 关闭图形窗口
    return 0;
}














//这个示例代码展示了如何使用 EasyX 库绘制贪吃蛇游戏的网格、蛇和食物，并使用广度优先搜索算法实现蛇自动寻路到食物。你可以根据需要进一步扩展和优化这个示例。希望这个示例对你有帮助！


//这个示例代码定义了一个20x20的网格，其中EMPTY表示空格，SNAKE表示蛇的身体，FOOD表示食物。bfs函数使用广度优先搜索来找到从蛇头到食物的最短路径，并返回路径。如果找到了路径，程序会输出路径上的每个点的坐标。

//希望这个示例对你有帮助！如果你有任何问题或需要进一步的修改，请随时告诉我。




// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
