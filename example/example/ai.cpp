#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <limits>
#include <sstream>
using namespace std;

// =============== 数据结构定义 ===============
struct GameRecord {
    string playerName;
    int mode;
    int targetNumber;
    int guessCount;
    bool isWin;
    int score;
    string dateTime;
};

struct Player {
    string name;
    int totalGames;
    int winGames;
    int totalScore;
    int bestScore;
    int bestGuess;
};

struct RankingItem {
    string playerName;
    int mode;
    int score;
    int guessCount;
    int timeUsed;
};

// =============== 函数声明 ===============
void showMainMenu();
void registerPlayer();
void loginPlayer();
void showGameModeMenu();
void classicMode();
void hardMode();
void saveGameRecord(int mode, int target, int guessCount, bool isWin, int score);
void showGameHistory();
void updatePlayerStats(int win, int score, int guessCount);
void showRanking();
void updateRanking(int mode, int score, int guessCount);
void clearInputBuffer();
string getCurrentDateTime();
void showPlayerStats();

// =============== 全局变量 ===============
Player currentPlayer;
bool isLoggedIn = false;

// =============== 辅助函数 ===============
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

// =============== 主菜单函数 ===============
void showMainMenu() {
    cout << "\n=======================================\n";
    cout << "         趣味猜数字游戏\n";
    cout << "=======================================\n";
    cout << "当前用户: ";
    if (isLoggedIn) {
        cout << currentPlayer.name;
    }
    else {
        cout << "未登录";
    }
    cout << "\n=======================================\n";
    cout << "1. 玩家登录/注册\n";
    cout << "2. 开始游戏\n";
    cout << "3. 查看游戏历史\n";
    cout << "4. 查看排行榜\n";
    cout << "5. 查看个人统计\n";
    cout << "6. 退出游戏\n";
    cout << "=======================================\n";
    cout << "请选择(1-6): ";
}

// =============== 玩家系统函数 ===============
void registerPlayer() {
    cout << "\n=== 玩家注册 ===\n";
    cout << "请输入用户名(不要有空格): ";
    string name;
    cin >> name;

    // 检查用户名是否已存在
    ifstream inFile("players.dat");
    string existingName;
    int tg, wg, ts, bs, bg;
    bool exists = false;

    while (inFile >> existingName >> tg >> wg >> ts >> bs >> bg) {
        if (existingName == name) {
            exists = true;
            break;
        }
    }
    inFile.close();

    if (exists) {
        cout << "用户名已存在，请使用其他用户名！\n";
        return;
    }

    // 创建新玩家
    currentPlayer.name = name;
    currentPlayer.totalGames = 0;
    currentPlayer.winGames = 0;
    currentPlayer.totalScore = 0;
    currentPlayer.bestScore = 0;
    currentPlayer.bestGuess = 9999;

    // 保存到文件
    ofstream outFile("players.dat", ios::app);
    if (outFile) {
        outFile << currentPlayer.name << " "
            << currentPlayer.totalGames << " "
            << currentPlayer.winGames << " "
            << currentPlayer.totalScore << " "
            << currentPlayer.bestScore << " "
            << currentPlayer.bestGuess << endl;
        cout << "注册成功！\n";
        isLoggedIn = true;
    }
    else {
        cout << "文件打开失败！\n";
    }
    outFile.close();
}

void loginPlayer() {
    cout << "\n=== 玩家登录 ===\n";
    cout << "请输入用户名: ";
    string name;
    cin >> name;

    ifstream inFile("players.dat");
    if (!inFile) {
        cout << "找不到玩家数据文件！\n";
        return;
    }

    bool found = false;
    string playerName;
    int totalGames, winGames, totalScore, bestScore, bestGuess;

    while (inFile >> playerName >> totalGames >> winGames >> totalScore >> bestScore >> bestGuess) {
        if (playerName == name) {
            found = true;
            currentPlayer.name = playerName;
            currentPlayer.totalGames = totalGames;
            currentPlayer.winGames = winGames;
            currentPlayer.totalScore = totalScore;
            currentPlayer.bestScore = bestScore;
            currentPlayer.bestGuess = bestGuess;
            break;
        }
    }

    inFile.close();

    if (found) {
        cout << "登录成功！欢迎回来，" << name << "！\n";
        isLoggedIn = true;

        // 显示玩家统计
        cout << "\n=== 您的游戏统计 ===\n";
        cout << "总游戏次数: " << currentPlayer.totalGames << endl;
        cout << "获胜次数: " << currentPlayer.winGames << endl;
        if (currentPlayer.totalGames > 0) {
            float winRate = (float)currentPlayer.winGames / currentPlayer.totalGames * 100;
            cout << "胜率: " << fixed << setprecision(1) << winRate << "%" << endl;
        }
        cout << "总得分: " << currentPlayer.totalScore << endl;
        cout << "最高得分: " << currentPlayer.bestScore << endl;
        cout << "最少猜测次数: " << (currentPlayer.bestGuess == 9999 ? 0 : currentPlayer.bestGuess) << endl;
    }
    else {
        cout << "用户名不存在！\n";
        cout << "是否要注册新用户？(1=是, 0=否): ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            registerPlayer();
        }
    }
}

// =============== 游戏模式函数 ===============
void showGameModeMenu() {
    cout << "\n=== 选择游戏模式 ===\n";
    cout << "1. 经典模式 (1-100)\n";
    cout << "2. 困难模式 (1-1000)\n";
    cout << "3. 返回主菜单\n";
    cout << "请选择(1-3): ";
}

void classicMode() {
    srand(time(0));
    int target = rand() % 100 + 1;
    int guessCount = 0;
    int guess;

    cout << "\n=== 经典单人模式 ===\n";
    cout << "已经生成1-100的随机数，开始猜一猜 吧！\n";
    cout << "提示：每次猜测后系统会告诉你太大了或太小了\n";

    do {
        cout << "\n第" << (guessCount + 1) << "次猜测: ";

        // 输入验证
        while (!(cin >> guess)) {
            cout << "请输入有效的数字: ";
            clearInputBuffer();
        }

        guessCount++;

        if (guess > target) {
            cout << "太大了！\n";
        }
        else if (guess < target) {
            cout << "太小了！\n";
        }
        else {
            cout << "\n恭喜猜对了！\n";
            cout << "正确答案: " << target << endl;
            cout << "猜测次数: " << guessCount << endl;

            // 计算分数
            int score = 1000 - guessCount * 10;
            if (score < 0) score = 0;

            cout << "获得分数: " << score << endl;

            // 保存记录
            saveGameRecord(1, target, guessCount, true, score);

            // 更新玩家数据
            updatePlayerStats(1, score, guessCount);

            // 更新排行榜
            updateRanking(1, score, guessCount);

            break;
        }

        // 提示
        if (guessCount % 5 == 0) {
            cout << "提示: 已经猜了" << guessCount << "次了！\n";
        }
    } while (true);
}

void hardMode() {
    srand(time(0));
    int target = rand() % 1000 + 1;
    int guessCount = 0;
    int guess;
    const int maxAttempts = 10;

    cout << "\n=== 困难挑战模式 ===\n";
    cout << "已生成1-1000的随机数，你有" << maxAttempts << "次机会！\n";

    for (int i = 1; i <= maxAttempts; i++) {
        cout << "\n第" << i << "次猜测，剩余机会: " << (maxAttempts - i) << "\n";
        cout << "请输入你的猜测: ";

        // 输入验证
        while (!(cin >> guess)) {
            cout << "请输入有效的数字: ";
            clearInputBuffer();
        }

        guessCount = i;

        if (guess > target) {
            cout << "太大了！\n";
        }
        else if (guess < target) {
            cout << "太小了！\n";
        }
        else {
            cout << "\n恭喜猜对了！\n";
            cout << "正确答案: " << target << endl;
            cout << "猜测次数: " << guessCount << endl;

            // 计算分数
            int score = (maxAttempts - guessCount + 1) * 100;

            cout << "获得分数: " << score << endl;

            // 保存记录
            saveGameRecord(2, target, guessCount, true, score);

            // 更新玩家数据
            updatePlayerStats(1, score, guessCount);

            // 更新排行榜
            updateRanking(2, score, guessCount);

            return;
        }
    }

    cout << "\n很遗憾，机会用完了！\n";
    cout << "正确答案是: " << target << endl;

    // 保存记录
    saveGameRecord(2, target, maxAttempts, false, 0);

    // 更新玩家数据
    updatePlayerStats(0, 0, maxAttempts);
}

// =============== 数据管理函数 ===============
void saveGameRecord(int mode, int target, int guessCount, bool isWin, int score) {
    ofstream outFile("game_records.txt", ios::app);
    if (outFile) {
        outFile << currentPlayer.name << ","
            << mode << ","
            << target << ","
            << guessCount << ","
            << (isWin ? 1 : 0) << ","
            << score << ","
            << getCurrentDateTime() << endl;
        cout << "游戏记录已保存！\n";
    }
    else {
        cout << "保存记录失败！\n";
    }
    outFile.close();
}

void showGameHistory() {
    ifstream inFile("game_records.txt");
    if (!inFile) {
        cout << "暂无游戏记录\n";
        return;
    }

    cout << "========== 历史游戏记录 =========="<< endl;
    cout << left << setw(15) << "玩家"
        << setw(10) << "模式"
        << setw(10) << "目标"
        << setw(10) << "次数"
        << setw(10) << "胜负"
        << setw(10) << "得分"
        << setw(25) << "时间" << endl;
    cout << string(90, '-') << endl;

    string line;
    int count = 0;

    while (getline(inFile, line)) {
        // 替换逗号为空格以便显示
        string displayRecord = line;
        size_t pos = displayRecord.find(',');
        string playerName = displayRecord.substr(0, pos);

        if (playerName == currentPlayer.name) {
            for (size_t i = 0; i < displayRecord.length(); i++) {
                if (displayRecord[i] == ',') {
                    displayRecord[i] = ' ';
                }
            }
            cout << displayRecord << endl;
            count++;

            if (count >= 10) {
                cout << "...(只显示最近10条记录)\n";
                break;
            }
        }
    }

    inFile.close();

    if (count == 0) {
        cout << "没有找到您的游戏记录\n";
    }
}

void updatePlayerStats(int win, int score, int guessCount) {
    currentPlayer.totalGames++;
    if (win) {
        currentPlayer.winGames++;
    }
    currentPlayer.totalScore += score;

    if (score > currentPlayer.bestScore) {
        currentPlayer.bestScore = score;
    }

    if (win && guessCount < currentPlayer.bestGuess) {
        currentPlayer.bestGuess = guessCount;
    }

    // 更新文件
    vector<string> allPlayers;
    ifstream inFile("players.dat");
    string line;

    while (getline(inFile, line)) {
        allPlayers.push_back(line);
    }
    inFile.close();

    // 查找并更新当前玩家的数据
    for (size_t i = 0; i < allPlayers.size(); i++) {
        istringstream iss(allPlayers[i]);
        string name;
        iss >> name;

        if (name == currentPlayer.name) {
            // 更新这一行
            ostringstream oss;
            oss << currentPlayer.name << " "
                << currentPlayer.totalGames << " "
                << currentPlayer.winGames << " "
                << currentPlayer.totalScore << " "
                << currentPlayer.bestScore << " "
                << currentPlayer.bestGuess;
            allPlayers[i] = oss.str();
            break;
        }
    }

    // 写回文件
    ofstream outFile("players.dat");
    for (size_t i = 0; i < allPlayers.size(); i++) {
        outFile << allPlayers[i] << endl;
    }
    outFile.close();
}

void showPlayerStats() {
    if (!isLoggedIn) {
        cout << "请先登录查看个人统计！\n";
        return;
    }

    cout << "\n=== 个人游戏统计 ===\n";
    cout << "玩家: " << currentPlayer.name << endl;
    cout << "总游戏次数: " << currentPlayer.totalGames << endl;
    cout << "获胜次数: " << currentPlayer.winGames << endl;

    if (currentPlayer.totalGames > 0) {
        float winRate = (float)currentPlayer.winGames / currentPlayer.totalGames * 100;
        cout << "胜率: " << fixed << setprecision(1) << winRate << "%" << endl;
        cout << "平均得分: " << currentPlayer.totalScore / currentPlayer.totalGames << endl;
    }
    else {
        cout << "胜率: 0.0%" << endl;
        cout << "平均得分: 0" << endl;
    }

    cout << "最高得分: " << currentPlayer.bestScore << endl;
    if (currentPlayer.bestGuess == 9999) {
        cout << "最少猜测次数: 暂无" << endl;
    }
    else {
        cout << "最少猜测次数: " << currentPlayer.bestGuess << endl;
    }
}

// =============== 排行榜函数 ===============
void updateRanking(int mode, int score, int guessCount) {
    ofstream outFile("ranking.txt", ios::app);
    if (outFile) {
        outFile << currentPlayer.name << " "
            << mode << " "
            << score << " "
            << guessCount << " "
            << 0 << endl; // 时间暂设为0
    }
    outFile.close();
}

void showRanking() {
    ifstream inFile("ranking.txt");
    if (!inFile) {
        cout << "暂无排行榜数据\n";
        return;
    }

    cout << "\n=== 游戏排行榜 ===\n";
    cout << left << setw(15) << "玩家"
        << setw(10) << "模式"
        << setw(10) << "分数"
        << setw(10) << "猜测次数" << endl;
    cout << string(45, '-') << endl;

    vector<RankingItem> rankings;
    string playerName;
    int mode, score, guessCount, timeUsed;

    while (inFile >> playerName >> mode >> score >> guessCount >> timeUsed) {
        RankingItem item;
        item.playerName = playerName;
        item.mode = mode;
        item.score = score;
        item.guessCount = guessCount;
        item.timeUsed = timeUsed;
        rankings.push_back(item);
    }
    inFile.close();

    // 按分数排序
    for (size_t i = 0; i < rankings.size(); i++) {
        for (size_t j = i + 1; j < rankings.size(); j++) {
            if (rankings[j].score > rankings[i].score) {
                RankingItem temp = rankings[i];
                rankings[i] = rankings[j];
                rankings[j] = temp;
            }
        }
    }

    // 显示前10名
    int count = 0;
    for (size_t i = 0; i < rankings.size() && count < 10; i++) {
        cout << left << setw(15) << rankings[i].playerName
            << setw(10) << (rankings[i].mode == 1 ? "经典" : "困难")
            << setw(10) << rankings[i].score
            << setw(10) << rankings[i].guessCount << endl;
        count++;
    }

    if (count == 0) {
        cout << "暂无排名数据\n";
    }
}

// =============== 主函数 ===============
int main() {
    cout << "欢迎来到趣味猜数字游戏！\n";
    cout << "版本: 1.0 (适合大一C++课程设计)\n\n";

    int choice;

    do {
        showMainMenu();

        // 输入验证
        if (!(cin >> choice)) {
            cout << "请输入有效的数字(1-6): ";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
        case 1: // 玩家登录/注册
            cout << "\n1. 登录\n2. 注册\n请选择: ";
            int loginChoice;
            cin >> loginChoice;

            if (loginChoice == 1) {
                loginPlayer();
            }
            else if (loginChoice == 2) {
                registerPlayer();
            }
            else {
                cout << "无效选择！\n";
            }
            clearInputBuffer();
            break;

        case 2: // 开始游戏
            if (!isLoggedIn) {
                cout << "请先登录或注册！\n";
                break;
            }

            showGameModeMenu();
            int gameMode;
            cin >> gameMode;

            switch (gameMode) {
            case 1:
                classicMode();
                break;
            case 2:
                hardMode();
                break;
            case 3:
                break; // 返回主菜单
            default:
                cout << "无效选择！\n";
            }
            clearInputBuffer();
            break;

        case 3: // 查看游戏历史
            if (!isLoggedIn) {
                cout << "请先登录查看历史记录！\n";
            }
            else {
                showGameHistory();
            }
            break;

        case 4: // 查看排行榜
            showRanking();
            break;

        case 5: // 查看个人统计
            showPlayerStats();
            break;

        case 6: // 退出游戏
            cout << "\n感谢游玩，再见！\n";
            if (isLoggedIn) {
                cout << "再见，" << currentPlayer.name << "！\n";
            }
            break;

        default:
            cout << "无效选择，请重新输入！\n";
            clearInputBuffer();
        }

    } while (choice != 6);

    return 0;
}