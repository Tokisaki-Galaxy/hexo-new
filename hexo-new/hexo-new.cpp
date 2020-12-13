// hexo-new.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <io.h>

int main(int argc, char* argv[])
{
	using namespace std;

	string path, tmp;
	ifstream instream;
	ofstream outstream;

	try {
		if (argc == 1) {
			cout << "请指定新建文件名。" << endl;
			throw;
		}
		tmp = "source\\_posts\\";
		tmp += argv[1];
		path = tmp + ".md";
		cout << path;
		if (!_access(path.c_str(), 0)) {
			cout << "存在目标文件，程序退出。" << endl;
			throw;
		}
		else if (_access("scaffolds\\post.md", 0))
		{
			cout << "没有找到模板文件scaffolds\\post.md，程序退出。" << endl;
			throw;
		}
	}
	catch (int e) {
		return -1;
	}

	try {
		instream.open("scaffolds\\post.md");
		outstream.open(path);

		if (instream.fail()) {
			cout << "打开模板文件失败，程序退出。" << endl;
			throw;
		}
		else if (outstream.fail())
		{
			cout << "打开目标文件失败，程序退出。" << endl;
			throw;
		}

		while (getline(instream, tmp)) {
			if (tmp.find("{{ title }}") != -1) {
				tmp = "title: ";
				tmp+=argv[1];
			}
			else if (tmp.find("{{ date }}") != -1)
			{
				tmp = "date: ";

				time_t now = time(0);
				tm* ltm = localtime(&now);
				// 输出 tm 结构的各个组成部分
				tmp = tmp + to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday) + " " + to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
			}
			outstream << tmp << endl;
		}
	}
	catch(int e){
		instream.close();
		outstream.close();
		return -1;
	}
	instream.close();
	outstream.close();
	return 0;
}
