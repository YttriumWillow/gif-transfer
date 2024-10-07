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
    std::cout << "[INFO] ���س����˳�" << '\n';
    system("pause");
}

int main(/*int argc, char const* argv[]*/) {
    fdata mp4File;
    intptr_t mp4Stat = _findfirst(".\\src\\*.mp4", &mp4File);


    // ɨ��ͬһĿ¼�µ� mp4 �ļ�
    if (mp4Stat == -1) {
        std::cout << RED << "[ERROR] δ�ҵ��κ� mp4 �ļ���" << RESET << '\n';
        return pauseExit(), 0;
    }
    std::vector<int> mp4Size;
    std::vector<std::string> mp4List;
    do {
        mp4List.push_back(mp4File.name);
        mp4Size.push_back(mp4File.size);
    } while (_findnext(mp4Stat, &mp4File) == 0);


    // �ļ��б�
    std::cout << "ɨ�赽�� mp4 �ļ�����Ϊ: " << mp4List.size() << '\n';
    rep (i, 0, (int)mp4List.size() - 1) {
        std::cout << i << ". ";
        std::cout << '[' << mp4Size[i] * 1.0 / 1024 / 1024 << " MB]" << ' ';
        std::cout << mp4List[i] << '\n';
    }
    std::cout << "��Ҫ����һ���ļ�ִ�в������������: ";


    // ѡ���ļ�
    int oprFileOrd = 0; bool f = 1; do {
        std::cin >> oprFileOrd;
        f = oprFileOrd < 0 or oprFileOrd >= mp4List.size();
        if (f) std::cout << "��������������룺";
    } while (f);
    std::cout << "�Ѿ�ѡ���ļ�: " << oprFileOrd << ". " << mp4List[oprFileOrd] << '\n';
    auto oprFileName = mp4List[oprFileOrd];
    std::cout << "ԭ�ļ���С: " << mp4Size[oprFileOrd] * 1.0 / 1024 / 1024 << " MB\n";

    // ffmpeg -i .\12.mp4 -ss 00:05:00 -t 00:10:00 -vf "fps=12,scale=320:-1:flags=lanczos,pad=320:320:0:70:black" out320_2.gif

    // ��ò���
    std::cout << YELLOW << "[WARN] ������У������д�Ĳ����ϲ��Ϸ��˾������Լ����Ű���ˡ�\n";
    std::cout << YELLOW << "[WARN] ͵��Ĭ��������Ƶ���� 16:9 ��һ����˵��������\n" << RESET;

    std::cout << "[INFO] ʱ���ʽ������(00:05:10=5min10s �� ����)\n";
    std::cout << "[INFO] �Ƽ��Ĳ��� 180-300s 320px 12fps �Լ�΢��һ��\n\n";

    std::cout << "��ʼʱ��[hh:mm:ss �� ����](����start����ǰ�濪ʼ): ";
    std::string st; std::cin >> st;
    std::cout << "����ʱ��[hh:mm:ss �� ����](����endһֱ�ص����): ";
    std::string ed; std::cin >> ed;

    std::cout << "����ֱ��������α߳�(�߳�����һ�����֣���): ";
    int siz; std::cin >> siz;

    std::cout << "�����Ƶ֡��(һ������): ";
    int fps; std::cin >> fps; 

    std::cout << "����ļ���: ";
    std::string outName; std::cin >> outName; 

    // ��������

    std::string command = ".\\ffmpeg -c:v h264_qsv -i";
    command += " .\\src\\" + oprFileName;
    if (st != "start") command += " -ss " + st;
    if (ed != "end") command += " -t " + ed;
    std::string vf = "\"";
    vf += "fps=" + std::to_string(fps) + ",scale=" + std::to_string(siz) + ":-1:flags=lanczos,pad=" + std::to_string(siz) + ":"
        + std::to_string(siz) + ":0:" + std::to_string((siz - siz / 16 * 9) / 2) + ":black\"";

    command += " -vf " + vf + " " + outName + ".gif";

    std::cout << "[INFO] ��������: " << command << '\n';
    std::cout << YELLOW << "[WARN] ׼����ʼ����..." << RESET << '\n';

    system(("start powershell /c " + command + ";pause").c_str());

    std::cout << "[INFO] �������" << '\n';

    _findclose(mp4Stat); pauseExit();
}