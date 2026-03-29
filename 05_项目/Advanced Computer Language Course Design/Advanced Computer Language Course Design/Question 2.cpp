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

//  函数声明
void ModeMenu();
void RegisterMenu();
void LoginMenu();
void registerPlayer();
void clear();
string getCurTime();
void saveGameRecord(int mode, int target_number, int guess_count, bool is_win, int time_used, int score);
void updatePlayer(int win, int score, int guessCount);
void updateRanking(int mode, int score, int guessCount);
void showGameHistory();
void showRanking();
void ClassicMode();
void HardMode();

////数 据 结 构   
// 游戏记录结构
struct GameRecord {
	int game_id; //游戏编号（自动生成）
	string player_name; //玩家姓名
	int mode; //游戏模式：1-经典 2-困难 3-对战 4-电脑猜
	int target_number; //目标数字
	int guess_count; //猜测次数
	int is_win; //是否获胜：1-是 0-否
	int time_used; //使用时间（秒）
	int score; //得分
	char date_time[20]; //游戏时间
};

// 玩家信息结构
struct Player {
	string name; //玩家姓名
	string password; //密码（简单加密）
	int total_games;//总游戏次数
	int win_games;
	int total_score;
	int best_score;
	int best_guess;
	int login_count;
};


// 排行榜结构
struct  RankingItem {
	string player_name;
	int mode;
	int score;
	int guess_count;
	int time_used;
};

////全局变量 
Player cu_player;
bool isLoggedIn = false;

////辅助函数
void clear() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getCurTime() {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	char buffer[80];
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", ltm);
	return string(buffer);
}

// 密码加密函数（凯撒密码）
string enPw(string pw) {
	string rpw = pw;
	for (size_t i = 0; i < rpw.length(); i++) {
		char c = rpw[i];
		if (c >= 'a' && c <= 'z') {
			rpw[i] = 'a' + (c - 'a' + 3) % 26;
		}
		else if (c >= 'A' && c <= 'Z') {
			rpw[i] = 'A' + (c - 'A' + 3) % 26;
		}
		else if (c >= '0' && c <= '9') {
			rpw[i] = '0' + (c - '0' + 2) % 10;
		}
	}
	return rpw;
}

////玩家系统函数
// 玩家注册函数
void registerPlayer() {
	cout << "=========== 玩家注册 ==========="<< endl;
	cout << "请输入用户名(不要有空格): ";
	string name;
	string password;
	cin >> name;
	cout << "请输入密码(不要有空格): ";
	cin >> password;

	// 检查用户名是否已存在
	ifstream inFile("players.dat");
	string exName;
	int tg, wg, ts, bs, bg, lc;
	string pw;
	bool ex = false;

	while (inFile >> exName >> pw >> tg >> wg >> ts >> bs >> bg >> lc) {
		if (exName == name) {
			ex = true;
			break;
		}
	}
	inFile.close();

	if (ex) {
		cout << "用户名已存在，请使用其他用户名！"<< endl;
		return;
	}

	// 创建新玩家
	cu_player.name = name;
	cu_player.password = password;
	cu_player.total_games = 0;
	cu_player.win_games = 0;
	cu_player.total_score = 0;
	cu_player.best_score = 0;
	cu_player.best_guess = 9999;
	cu_player.login_count = 0;

	// 保存到文件
	ofstream outFile("players.dat", ios::app);
	if (outFile) {
		outFile << cu_player.name << " "
			<< enPw(cu_player.password) << " "
			<< cu_player.total_games << " "
			<< cu_player.win_games << " "
			<< cu_player.total_score << " "
			<< cu_player.best_score << " "
			<< cu_player.best_guess << " "
		    << cu_player.login_count << endl;
		cout << "注册成功！"<< endl;
		isLoggedIn = true;
	}
	else {
		cout << "文件打开失败！"<< endl;
	}
	outFile.close();
	system("pause");
}

// 玩家登录函数
void loginPlayer() {
	const int MAX_ATT = 3;
	int att = 0;

	cout << "============ 玩家登录 ============" << endl;
	cout << "请输入用户名（不要有空格）: ";
	string name;
	cin >> name;   // 用户名只在最开始输入一次，密码在循环内重输

	while (att < MAX_ATT) {
		string password;   // 每次循环重新定义，接收新密码
		cout << "请输入密码（不要有空格）: ";
		cin >> password;

		ifstream inFile("players.dat");
		if (!inFile) {
			cout << "找不到玩家数据文件！" << endl;
			return;
		}

		bool found = false;
		bool login = false;
		string playerName;
		string passWord;
		int totalGames, winGames, totalScore, bestScore, bestGuess, loginCount;

		while (inFile >> playerName >> passWord >> totalGames >> winGames>> totalScore >> bestScore >> bestGuess >> loginCount) {
			if (playerName == name) {
				found = true;
				if ( enPw(password) == passWord) {
					login = true;
					cu_player.name = playerName;
					cu_player.total_games = totalGames;
					cu_player.win_games = winGames;
					cu_player.total_score = totalScore;
					cu_player.best_score = bestScore;
					cu_player.best_guess = bestGuess;
					cu_player.login_count = loginCount;
				}
				break;
			}
		}
		inFile.close();

		if (found && login) {
			cu_player.login_count++;
			cu_player.password = passWord;
			cout << "登录成功！欢迎回来，" << name << "！"<< endl;
			isLoggedIn = true;

			cout << "============ 您的游戏统计 ============" << endl;
			cout << "总游戏次数: " << cu_player.total_games << endl;
			cout << "获胜次数: " << cu_player.win_games << endl;
			if (cu_player.total_games > 0) {
				float winRate = (float)cu_player.win_games / cu_player.total_games * 100;
				cout << "胜率: " << fixed << setprecision(1) << winRate << "%" << endl;
			}
			cout << "总得分: " << cu_player.total_score << endl;
			cout << "最高得分: " << cu_player.best_score << endl;
			cout << "最少猜测次数: " << (cu_player.best_guess == 9999 ? 0 : cu_player.best_guess) << endl;
			system("pause");
			return;
		}
		else if (!found) {
			cout << "用户名不存在！" << endl;
			cout << "是否要注册新用户？(1=是, 0=否): ";
			int choice;
			cin >> choice;
			if (choice == 1) {
				registerPlayer();
			}
			return;   //返回主菜单（避免无限循环）
		}
		else {   //密码错误
			++att;
			cout << "密码错误！剩余 " << MAX_ATT - att << " 次机会" << endl;
			if (att >= MAX_ATT) {
				cout << "尝试次数过多，返回主菜单。" << endl;
				return;
			}
			//继续循环，重新输入密码
		}
	}
}


void saveGameRecord(int mode, int target_number, int guess_count, bool is_win, int time_used, int score){
	ofstream outFile("game_records.txt", ios::app);
	static int con = 0;
	if (outFile) {
		con++;
		outFile << con <<","
			<< cu_player.name << ","
			<< mode << ","
			<< target_number << ","
			<< guess_count << ","
			<< (is_win ? 1 : 0) << ","
			<< time_used <<","
			<< score << ","
			<< getCurTime() << endl;
		cout << "游戏记录已保存！"<< endl;
	}
	else {
		cout << "保存记录失败！"<< endl;
	}
	outFile.close();
}

// 更新玩家信息
void updatePlayer(int win, int score, int guessCount) {
	cu_player.total_games++;
	if (win) {
		cu_player.win_games++;
	}
	cu_player.total_score += score;

	if (score > cu_player.best_score) {
		cu_player.best_score = score;
	}

	if (win && guessCount < cu_player.best_guess) {
		cu_player.best_guess = guessCount;
	}

	// 更新文件
	vector<string> allPlayers;
	ifstream inFile("players.dat");
	string line;

	while (getline(inFile, line)) {
		allPlayers.push_back(line);
	}
	inFile.close();// 循环存 

	// 查找并更新当前玩家的数据
	for (size_t i = 0; i < allPlayers.size(); i++) {
		istringstream iss(allPlayers[i]);
		string name;
		iss >> name;

		if (name == cu_player.name) {
			// 更新这一行
			ostringstream oss;
			oss << cu_player.name << " "
				<< enPw(cu_player.password) << " "
				<< cu_player.total_games << " "
				<< cu_player.win_games << " "
				<< cu_player.total_score << " "
				<< cu_player.best_score << " "
				<< cu_player.best_guess << " "
				<< cu_player.login_count;
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


// 显示历史游戏记录（仅当前玩家）
void showGameHistory() {
	if (!isLoggedIn) {
		cout << "请先登录查看历史记录！" << endl;
		return;
	}

	ifstream inFile("game_records.txt");
	if (!inFile) {
		cout << "暂无游戏记录！" << endl;
		return;
	}

	cout << "\n========== 历史游戏记录 ==========" << endl;
	cout << left << setw(6) << "序号"
		<< setw(12) << "模式"
		<< setw(8) << "目标"
		<< setw(8) << "次数"
		<< setw(8) << "胜负"
		<< setw(8) << "用时(s)"
		<< setw(8) << "得分"
		<< setw(20) << "时间" << endl;
	cout << string(80, '-') << endl;

	string line;
	int count = 0;
	while (getline(inFile, line)) {
		stringstream ss(line);
		string now;
		// 文件格式：ID,玩家名,模式,目标,次数,是否胜利,用时,得分,日期时间
		getline(ss, now, ','); // ID（忽略）
		getline(ss, now, ','); // 玩家名
		if (now != cu_player.name) continue; // 只显示当前玩家

		// 模式
		getline(ss, now, ','); int mode = stoi(now);
		// 目标
		getline(ss, now, ','); int target = stoi(now);
		// 猜测次数
		getline(ss, now, ','); int guess = stoi(now);
		// 是否胜利
		getline(ss, now, ','); int isWin = stoi(now);
		// 使用时间
		getline(ss, now, ','); int timeUsed = stoi(now);
		// 得分
		getline(ss, now, ','); int score = stoi(now);
		// 日期时间（剩余部分）
		string dateTime;
		getline(ss, dateTime);

		// 输出一行记录
		cout << left << setw(6) << ++count
			<< setw(12) << (mode == 1 ? "经典" : (mode == 2 ? "困难" : "其他"))
			<< setw(8) << target
			<< setw(8) << guess
			<< setw(8) << (isWin ? "胜" : "负")
			<< setw(8) << timeUsed
			<< setw(8) << score
			<< setw(20) << dateTime << endl;

		if (count >= 20) { // 最多显示20条
			cout << "...(仅显示最近20条记录)" << endl;
			break;
		}
	}
	inFile.close();

	if (count == 0) {
		cout << "没有找到您的游戏记录。" << endl;
	}
	system("pause");
}

// 更新排行榜函数
void updateRanking(int mode, int score, int guess_count) {
	ofstream outFile("ranking.txt", ios::app);
	if (outFile) {
		outFile << cu_player.name << " "
			<< mode << " "
			<< score << " "
			<< guess_count << " "
			<< 0 << endl; // 时间暂设为0
	}
	outFile.close();
}

// 展示排行榜函数
void showRanking() {
	if (!isLoggedIn) {
		cout << "请先登录查看排行榜！" << endl;
		return;
	}

	ifstream inFile("game_records.txt");
	if (!inFile) {
		cout << "暂无游戏记录！" << endl;
		return;
	}

	// 临时结构体，用于存储记录中的必要字段
	struct TempRank {
		string name;
		int mode;
		int score;
		int guess;
		int time;
	};

	vector<TempRank> classic, hard;
	string line;
	while (getline(inFile, line)) {
		stringstream ss(line);
		string now;
		TempRank item;
		// 文件格式：ID,玩家名,模式,目标,次数,是否胜利,用时,得分,日期时间
		getline(ss, now, ','); // ID（忽略）
		getline(ss, item.name, ',');
		getline(ss, now, ','); item.mode = stoi(now);
		getline(ss, now, ','); // 目标数字（忽略）
		getline(ss, now, ','); item.guess = stoi(now);
		getline(ss, now, ','); // 是否胜利（忽略）
		getline(ss, now, ','); item.time = stoi(now);
		getline(ss, now, ','); item.score = stoi(now);
		// 剩余日期时间忽略

		if (item.mode == 1)
			classic.push_back(item);
		else if (item.mode == 2)
			hard.push_back(item);
	}
	inFile.close();

	// 排序规则：得分降序，得分相同则次数升序，次数相同则用时升序
	auto cmp = [](const TempRank& a, const TempRank& b) {
		if (a.score != b.score) return a.score > b.score;
		if (a.guess != b.guess) return a.guess < b.guess;
		return a.time < b.time;
		};
	sort(classic.begin(), classic.end(), cmp);
	sort(hard.begin(), hard.end(), cmp);

	// 显示经典模式排行榜
	cout << "========== 经典模式排行榜 ==========" << endl;
	cout << left << setw(5) << "排名" 
		<< setw(15) << "玩家"
		<< setw(8) << "得分" 
		<< setw(8) << "次数" 
		<< setw(8) << "用时(s)" << endl;
	cout << string(50, '-') << endl;

	for (size_t i = 0; i < classic.size() && i < 10; ++i) {
		cout << left << setw(5) << i + 1
			<< setw(15) << classic[i].name
			<< setw(8) << classic[i].score
			<< setw(8) << classic[i].guess
			<< setw(8) << classic[i].time << endl;
	}
	if (classic.empty()) cout << "暂无记录。" << endl;

	// 显示困难模式排行榜
	cout << "========== 困难模式排行榜 ==========" << endl;
	cout << left << setw(5) << "排名" 
		<< setw(15) << "玩家"
		<< setw(8) << "得分" 
		<< setw(8) << "次数" 
		<< setw(8) << "用时(s)" << endl;
	cout << string(50, '-') << endl;
	for (size_t i = 0; i < hard.size() && i < 10; ++i) {
		cout << left << setw(5) << i + 1
			<< setw(15) << hard[i].name
			<< setw(8) << hard[i].score
			<< setw(8) << hard[i].guess
			<< setw(8) << hard[i].time << endl;
	}
	if (hard.empty()) cout << "暂无记录。" << endl;

	// 保存到 ranking.txt
	ofstream outFile("ranking.txt");
	if (outFile) {
		outFile << "经典模式排行榜\n";
		outFile << "排名\t玩家\t得分\t次数\t用时(s)\n";
		for (size_t i = 0; i < classic.size() && i < 10; ++i) {
			outFile << i + 1 << "\t" 
				<< classic[i].name << "\t"
				<< classic[i].score << "\t" 
				<< classic[i].guess << "\t"
				<< classic[i].time << "\n";
		}
		outFile << "\n困难模式排行榜\n";
		outFile << "排名\t玩家\t得分\t次数\t用时(s)\n";
		for (size_t i = 0; i < hard.size() && i < 10; ++i) {
			outFile << i + 1 << "\t" 
				<< hard[i].name << "\t"
				<< hard[i].score << "\t" 
				<< hard[i].guess << "\t"
				<< hard[i].time << "\n";
		}
		outFile.close();
		cout << "\n排行榜已保存到 ranking.txt" << endl;
	}
	system("pause");
}

void MainMenu() {
	int choice = 0;
	struct Player cplayer;
	do {
		system("cls");// 清屏
		cout << "========= 趣味猜字游戏 =========" << endl;
		cout << "当前用户: ";
		if (isLoggedIn) {
			cout << cu_player.name;
		}
		else {
			cout << "未登录" << endl;
		}
		cout << "********************************" << endl;
		cout << "*            请选择            *" << endl;
		cout << "********************************" << endl;
		cout << "*           1. 注册            *" << endl;
		cout << "*           2. 登陆            *" << endl;
		cout << "*           3. 查看排行榜      *" << endl;
		cout << "*           4. 历史游戏记录    *" << endl;
		cout << "*           5. 退出            *" << endl;
		cout << "================================" << endl;
		cout << "请输入你的选择：";

		if (!(cin >> choice)) {
			cin.clear();                 // 清除错误状态
			cin.ignore(10000, '\n');     // 清空缓冲区
			cout << "请输入数字！！！" << endl;
			system("pause");
			continue;
		}

		switch (choice) {
		case 1:// 注册  
			RegisterMenu();
			break;
		case 2:// 登陆
			LoginMenu();
			break;
		case 3:// 查看排行榜
			showRanking();
			break;
		case 4:// 历史记录
			if (isLoggedIn) {
				showGameHistory();
			}
			else {
				cout << "您还未登陆，请登陆！" << endl;
				system("pause");
			}
			break;
		case 5:// 退出
			system("cls");// 清屏
			cout << "感谢使用，再见！" << endl;
			exit(0);
			break;
		default:
			system("pause");
			cout << "无效选择，请重新输入." << endl;
		}
	} while (1);
}



void RegisterMenu() {
	int choice;
	do {
		system("cls");// 清屏
		cout << "============ 请输入 ============" << endl;
		cout << "********************************" << endl;
		cout << "*         1.账号和密码：       *" << endl;
		cout << "*         2.返回               *" << endl;
		cout << "*         3.退出               *" << endl;
		cout << "================================" << endl;
		cout << "请输入你的选择：";

		if (!(cin >> choice)) {
			cin.clear();                 // 清除错误状态
			cin.ignore(10000, '\n');     // 清空缓冲区
			cout << "请输入数字！！！" << endl;
			system("pause");
			RegisterMenu();
			continue;
		}

		switch (choice) {
		case 1:
			registerPlayer();
			if (isLoggedIn) {
				ModeMenu();
			}
			break;
		case 2:
			MainMenu();
			break;
		case 3:
			cout << "感谢使用，再见！" << endl;
			exit(0);
			break;
		default:
			cout << "无效选择，请重新输入." << endl;
			system("pause");
		}
	} while (choice != 0);
}

void LoginMenu() {
	int choice;
	do {
		system("cls");// 清屏
		cout << "============ 请输入 ============" << endl;
		cout << "********************************" << endl;
		cout << "*         1.账号和密码：       *" << endl;
		cout << "*         2.返回               *" << endl;
		cout << "*         3.退出               *" << endl;
		cout << "================================" << endl;
		cout << "请输入你的选择：";

		if (!(cin >> choice)) {
			cin.clear();                 // 清除错误状态
			cin.ignore(10000, '\n');     // 清空缓冲区
			cout << "请输入数字！！！" << endl;
			system("pause");
			LoginMenu();
			continue;
		}
		switch (choice) {
		case 2:
			MainMenu();
			break;
		case 3:
			system("cls");// 清屏
			cout << "感谢使用，再见！" << endl;
			exit(0);
			break;
		case 1:
			loginPlayer();
			if (isLoggedIn) {
				ModeMenu();
			}
			break;
		default:
			cout << "无效选择，请重新输入." << endl;
			system("pause");
		}
	} while (choice != 0);
}


void ModeMenu() {
	int choice;
	do {
		system("cls");// 清屏
		cout << "============ 请输入 ============" << endl;
		cout << "*       1. 经典单人模式(1-100) *" << endl;
		cout << "*       2. 困难挑战模式(1-1000)*" << endl;
		cout << "*       3. 双人对战模式        *" << endl;
		cout << "*       4. 电脑猜数模式        *" << endl;
		cout << "*       5. 返回                *" << endl;
		cout << "*       6. 退出                *" << endl;
		cout << "================================" << endl;
		cout << "请输入你的选择：";

		if (!(cin >> choice)) {
			cin.clear();                 // 清除错误状态
			cin.ignore(10000, '\n');     // 清空缓冲区
			cout << "请输入数字！！！" << endl;
			system("pause");
			ModeMenu();
			continue;
		}

		switch (choice) {
		case 1:
			ClassicMode();
			break;
		case 2:
			HardMode();
			break;
		case 3:
			cout << "抱歉该功能暂未实现，敬请期待" << endl;
			system("pause");
			break;
		case 4:
			cout << "抱歉该功能暂未实现，敬请期待" << endl;
			system("pause");
			break;
		case 5:
			MainMenu();
			break;
		case 6:
			system("cls");// 清屏
			cout << "感谢使用，再见！" << endl;
			exit(0);
			break;
		default:
			cout << "无效选择，请重新输入." << endl;
			system("pause");
		}
	} while (choice != 6);
}
// 经典单人模式函数
void ClassicMode() {
	clock_t startTime = clock();//开始时间

	srand(time(0));
	int target = rand() % 100 + 1;
	int guessCount = 0;
	int guess;

	cout << "========= 经典单人模式 ========="<< endl;
	cout << "已经生成1-100的随机数，开始猜一猜吧！ "<< endl;
	cout << "提示：每次猜后系统会提示你猜大了或猜小了"<< endl;

	do {
		cout << "\n第" << (guessCount + 1) << "次猜测: ";

		// 输入验证
		while (!(cin >> guess)) {
			cout << "请输入有效的数字: ";
			clear();
		}

		guessCount++;

		if (guess > target) {
			cout << "太大了！\n";
		}
		else if (guess < target) {
			cout << "太小了！\n";
		}
		else {
			cout << "\n恭喜你猜对了！\n";
			cout << "正确答案: " << target << endl;
			cout << "猜测次数: " << guessCount << endl;

			clock_t endTime = clock();
			double timeUsed = double(endTime - startTime) / CLOCKS_PER_SEC;//时间

			// 计算分数
			int score = 1000 - guessCount * 10;
			if (score < 0) score = 0;

			cout << "获得分数: " << score << endl;

			// 保存记录
			saveGameRecord(1, target, guessCount, true, timeUsed, score);

			// 更新玩家数据
			updatePlayer(1, score, guessCount);

			// 更新排行榜
			updateRanking(1, score, guessCount);
			system("pause");
			break;
		}

		// 提示
		if (guessCount % 5 == 0) {
			cout << "提示: 已经猜了" << guessCount << "次了！\n";
		}
	} while (true);
}

//  困难挑战模式函数
void HardMode() {
	clock_t startTime = clock();//开始时间

	srand(time(0));
	int target = rand() % 1000 + 1;
	int guessCount = 0;
	int guess;
	const int maxAtt = 11;

	cout << "========= 困难挑战模式 =========="<< endl;
	cout << "已生成1-1000的随机数，你有" << maxAtt - 1 << "次机会！"<< endl;

	for (int i = 1; i < maxAtt; i++) {
		cout << "第" << i << "次猜测，剩余机会: " << (maxAtt - i) << endl;
		cout << "请输入你的猜测: ";

		// 输入验证
		while (!(cin >> guess)) {
			cout << "请输入有效的数字: ";
			clear();
		}

		guessCount = i;

		if (guess > target) {
			cout << "太大了！"<< endl;
		}
		else if (guess < target) {
			cout << "太小了！"<< endl;
		}
		else {
			cout << "恭喜猜对了！"<< endl;
			cout << "正确答案: " << target << endl;
			cout << "猜测次数: " << guessCount << endl;

			clock_t endTime = clock();
			double timeUsed = double(endTime - startTime) / CLOCKS_PER_SEC;

			int score = (maxAtt - guessCount + 1) * 100;

			cout << "获得分数: " << score << endl;

			saveGameRecord(2, target, guessCount, true, timeUsed, score);
			updatePlayer(1, score, guessCount);
			updateRanking(2, score, guessCount);
			system("pause");
			return;
		}
	}

	clock_t endTime = clock();
	double timeUsed = double(endTime - startTime) / CLOCKS_PER_SEC;

	cout << "很遗憾，机会用完了！"<< endl;
	cout << "正确答案是: " << target << endl;

	saveGameRecord(2, target, maxAtt, false, timeUsed, 0);

	updatePlayer(0, 0, maxAtt);
	system("pause");
}

int main() {
	MainMenu();
	ModeMenu();
	return 0;
}