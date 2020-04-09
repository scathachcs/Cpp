#pragma once
#include<iostream>
#include<string>
#include<list>
#include<fstream>

using namespace std;


class Editor {
private:
	string filename;
	list<string> textBuffer;
	int curLine;
	ifstream infile;
	ofstream outfile;
public:
	Editor() {
		curLine = 0;
	}
	Editor(string str) {
		filename = str;
		curLine = 0;
	}
	~Editor() {

	}

	void ReadFile() {//把文件内容导入缓冲区
		infile = ifstream(filename, ios::in);
		if (!infile.is_open()) {
			std::cout << "failed to open " << filename << '\n';
		}

		if (textBuffer.empty() != true) {
			textBuffer.clear();
		}

		for (string Line; getline(infile,Line);) {
			textBuffer.push_back(Line);
		}
		curLine = 0;
		infile.close();
	}
	void Writefile() {//把缓冲区内容写入文件
		outfile = ofstream(filename, ios::out);
		if (!outfile.is_open()) {
			std::cout << "failed to open " << filename << '\n';
		}

		for (auto it = textBuffer.cbegin(); it != textBuffer.cend(); it++) {
				 outfile<< *it << endl;
		}

		outfile.close();
	}
	void Show() {//把缓冲区内容显示
		for (auto pos = textBuffer.cbegin(); pos != textBuffer.cend(); pos++) {
			cout << *pos << endl;
		}
	}
	
	void Delete() {//删除当前行，curLine移动至下一行
		auto pos = textBuffer.cbegin();
		for (int i=0;i<curLine; i++) {
			pos++;
		}
		textBuffer.erase(pos);
	}
	void Insert (int x,string line) {//插入行，提供行号和内容，curLine移动至当前行
		auto pos = textBuffer.cbegin();
		for (int i = 0; i < x; i++) {
			pos++;
		}
		textBuffer.insert(pos, line);
		curLine = x;
	}

	int Findstring(int x,string substr) {
			int i = 0;
			auto pos = textBuffer.cbegin();
			if (x != 0) {
				for (; i < curLine; i++) {
					pos++;
				}
			}
			for (; pos != textBuffer.cend(); pos++) {
				if ((*pos).find(substr) != string::npos) {
					return i;
				}
				i++;
			}
	}
	void ChangeLine(string sub1,string sub2,int x) {
		if (x == 1) {
			auto pos = textBuffer.cbegin();
			for (int i = 0; i < curLine; i++) {
				pos++;
			}
			string line = (*pos);
				while (1) {
					if (line.find(sub1) != string::npos) {
						string::size_type i;
						i = line.find(sub1);
						line.replace(i, sub1.length(), sub2);
					}
					else
						break;
			}
				textBuffer.insert(pos, line);
				auto x = pos;
				pos--;
				textBuffer.erase(x);
		}
		else {
			auto pos = textBuffer.cbegin();
			for (; pos != textBuffer.cend(); pos++) {
				string line = (*pos);
				while (1) {
					if (line.find(sub1) != string::npos) {
						string::size_type i;
						i = line.find(sub1);
						line.replace(i, sub1.length(), sub2);
					}
					else
						break;
				}
				textBuffer.insert(pos, line);
				auto x = pos;
				pos--;
				textBuffer.erase(x);
				
			}
		}
	}

	void Run() {
		char Command;
		int flag=0;//退出标志符
		while (1) {
			if (flag == 1) {
				break;
			}
			if (textBuffer.empty() != true) {
				cout << endl;
				cout << "当前行号：" << curLine << endl;
				auto pos = textBuffer.cbegin();
				for (int i = 0; i < curLine; i++) {
					pos++;
				}
				cout << *pos << endl;
			}
			cout << "请输入指令：";
			cin>>Command;
			if (Command > 64 && Command < 91) {
				Command += 32;
			}
			switch (Command) {
			case'b':
				if (textBuffer.empty() == true) {
					cout << "error: empty"<<endl;
				}
				else
					//转到第一行
					curLine = 0;
				break;

			case'e':
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else
					//转到最后一行
					curLine = textBuffer.size()-1;
				break;

			case'p':
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else {
					if ((curLine - 1) >= 0) {
						//转到上一行
						curLine--;
					}
				}
					
				break;

			case'n':
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else {
					if((curLine+1)<textBuffer.size())
						curLine++;//转到下一行
					
				}
					
				break;
			case'g'://跳转指定行
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else {
					//转到指定行
					int x;
					cout << "请输入指定行：";
					cin >> x;
					if (x < 0 || x >=textBuffer.size())
						cout << "范围错误" << endl;
					else
					    curLine = x;
				}
				break;
			case'i'://插入新行
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else {
					string str;
					cout << "请输入插入行的内容：";
					cin >> str;
					int x;
					cout << "请输入插入行的行号：";
					cin >> x;
					Insert(x, str);
				}
				break;
			case'd'://删除当前行
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else {
					Delete();
				}
				break;
			case'v'://查看缓冲区
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else {
					Show();
				}
				break;
			case'f'://查找某一目标串
			{
				cout << "从第一行开始查找输入：0 ||从当前串开始搜索输入：1"<<endl;
			    int x;
			    while (1) {
					cout << "请输入： ";
				     cin >> x;
				     if (x == 0 || x == 1) {
					      break;
				      }
				     cout << "输入错误，请重新输入" << endl;
			    }
			    cout << "输入需要查找的字符串：";
			    string substr;
			    cin >> substr;
			    cout<<"目标串位于第"<<Findstring(x, substr)<<"行"<<endl;
			    break;
			}
			case'c'://替换文本
			{
				cout << "从第一行开始查找替换输入：0 ||当前行查找替换输入：1" << endl;
				int x;
				while (1) {
					cout << "请输入： ";
					cin >> x;
					if (x == 0 || x == 1) {
						break;
					}
					cout << "输入错误，请重新输入" << endl;
				}
				string sub1;
				cout << "输入需要查找的字符串：";
				cin >> sub1;
				string sub2;
				cout << "输入需要替换的字符串：";
				cin >> sub2;
				ChangeLine(sub1,sub2,x);
				break;
			}
			
			case'r':
				ReadFile();
				break;
			case'w':
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else {
					Writefile();
				}
				break;
			case'q'://退出
				flag = 1;
				break;
			case'h':
			case'?':
				cout << "r:读取文本文件到缓冲区中，缓冲区中以前的任何内容将丢失，当前行是文件的第一行" << endl;
				cout << "w：将缓冲区的内容写入文本文件，当前行或缓冲区均不改变" << endl;
				cout << "i：插人单个新行，用户必领在恰当的提示符的响应中输入新行并提供其行号" << endl;
				cout << "d：删除当前行并移到下一行" << endl;
				cout << "f：可以从第1行开始或从当前行开始，查找包含有用户请求的目标串的第一行" << endl;
				cout << "c：用户请求的字符串修改成用户请求的替换文本，可选择是仅在当前行中有效的还是对全文有效的" << endl;
				cout << "q：退出编辑器，立即结束" << endl;
				cout << "h：显示解释所有命令的帮助消息，程序也接受?作为H的替代者" << endl;
				cout << "n：当前行移到下一行，也就是移到缓冲区的下一行" << endl;
				cout << "p：当前行移到上一行，也就是移到缓冲区的上一行" << endl;
				cout << "b：当前行移到开始处，也就是移到级冲区的第一行" << endl;
				cout << "e：当前行移到结束处，也就是移到缓冲区的最后一行" << endl;
				cout << "g：当前行移到到缓冲区中用户指定的行" << endl;
				cout << "v：将缓冲区的全部内容打印到终端上" << endl;
				break;
			default:
				cout << "指令错误,可输入h或?查看帮助" << endl;
				break;
			}
			
				
		}
		
	}

};