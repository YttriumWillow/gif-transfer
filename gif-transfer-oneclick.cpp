#include <bits/stdc++.h>
#include <io.h>

#define rep(i, l, r) for (int i = (l); i <= r; ++i)

#define RESET "\033[0m"
#define BLACK "\033[30m"  /* Black */
#define RED "\033[31m"    /* Red */
#define GREEN "\033[32m"  /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m"   /* Blue */
#define PURPLE "\033[35m" /* Purple */
#define CYAN "\033[36m"   /* Cyan */
#define WHITE "\033[37m"  /* White */

#define NORMAL (std::cout << RESET)
#define INFO (std::cout << GREEN)
#define WARN (std::cout << YELLOW)
#define ERROR (std::cout << RED)
#define DEBUG (std::cout << CYAN)
#define END (std::endl)
#define REND "\033[0m" << std::endl


typedef _finddata_t fdata;

void pauseExit() {
    std::cout << "[INFO] 按回车以退出" << '\n';
    system("pause");
}

int main(/*int argc, char const* argv[]*/) {
    fdata mp4File;
    intptr_t mp4Stat = _findfirst(".\\src\\*.mp4", &mp4File);


    // 扫描同一目录下的 mp4 文件
    if (mp4Stat == -1) {
        std::cout << RED << "[ERROR] 在 src 文件夹下未找到任何 mp4 文件！" << RESET << '\n';
        return pauseExit(), 0;
    }
    std::vector<int> mp4Size;
    std::vector<std::string> mp4List;
    do {
        mp4List.push_back(mp4File.name);
        mp4Size.push_back(mp4File.size);
    } while (_findnext(mp4Stat, &mp4File) == 0);


    // 文件列表
    std::cout << "扫描到的 mp4 文件数量为: " << mp4List.size() << '\n';
    rep (i, 0, (int)mp4List.size() - 1) {
        std::cout << i << ". ";
        std::cout << '[' << mp4Size[i] * 1.0 / 1024 / 1024 << " MB]" << ' ';
        std::cout << mp4List[i] << '\n';
    }
    std::cout << "需要对哪一个文件执行操作，输入序号: ";


    // 选定文件
    int oprFileOrd = 0; bool f = 1; do {
        std::cin >> oprFileOrd;
        f = oprFileOrd < 0 or oprFileOrd >= mp4List.size();
        if (f) std::cout << "序号有误重新输入：";
    } while (f);
    std::cout << "已经选定文件: " << oprFileOrd << ". " << mp4List[oprFileOrd] << '\n';
    auto oprFileName = mp4List[oprFileOrd];
    std::cout << "原文件大小: " << mp4Size[oprFileOrd] * 1.0 / 1024 / 1024 << " MB\n";

    // ffmpeg -i .\12.mp4 -ss 00:05:00 -t 00:10:00 -vf "fps=12,scale=320:-1:flags=lanczos,pad=320:320:0:70:black" out320_2.gif

    // 获得参数
    std::cout << YELLOW << "[WARN] 分辨率、帧率参数请查看同一目录下的 settings.json\n";

    std::cout << "起始时刻[hh:mm:ss 或 秒数](最前开始输入 0): ";
    std::string st; std::cin >> st;
    std::cout << "持续时长[hh:mm:ss 或 秒数](输入 e 截到最后): ";
    std::string ed; std::cin >> ed;

    std::cout << "输出文件名(请不要带.gif): ";
    std::string outName; std::cin >> outName; 

    // 生成命令

    int fps = 12;
    int siz = 320;

    std::string args = "\"";
    args += "fps=" + std::to_string(fps)
        + ",scale=" + std::to_string(siz)
        + ":-1:flags=lanczos,pad=" + std::to_string(siz) + ":"
        + std::to_string(siz)
        + ":0:"
        + std::to_string((siz - siz / 16 * 9) / 2) + ":black\"";

    std::string command;
    command = ".\\ffmpeg -i .\\src\\" + oprFileName + (ed != "e" ? "" : " -t " + ed) + " -vf " + args + " " + outName + ".gif";

    std::cout << "[INFO] 生成命令: " << command << '\n';
    std::cout << YELLOW << "[WARN] 准备开始生成..." << RESET << '\n';

    system(("start powershell /c " + command + ";pause").c_str());

    std::cout << "[INFO] 生成完毕" << '\n';

    _findclose(mp4Stat); pauseExit();
}