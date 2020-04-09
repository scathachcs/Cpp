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

	void ReadFile() {//���ļ����ݵ��뻺����
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
	void Writefile() {//�ѻ���������д���ļ�
		outfile = ofstream(filename, ios::out);
		if (!outfile.is_open()) {
			std::cout << "failed to open " << filename << '\n';
		}

		for (auto it = textBuffer.cbegin(); it != textBuffer.cend(); it++) {
				 outfile<< *it << endl;
		}

		outfile.close();
	}
	void Show() {//�ѻ�����������ʾ
		for (auto pos = textBuffer.cbegin(); pos != textBuffer.cend(); pos++) {
			cout << *pos << endl;
		}
	}
	
	void Delete() {//ɾ����ǰ�У�curLine�ƶ�����һ��
		auto pos = textBuffer.cbegin();
		for (int i=0;i<curLine; i++) {
			pos++;
		}
		textBuffer.erase(pos);
	}
	void Insert (int x,string line) {//�����У��ṩ�кź����ݣ�curLine�ƶ�����ǰ��
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
		int flag=0;//�˳���־��
		while (1) {
			if (flag == 1) {
				break;
			}
			if (textBuffer.empty() != true) {
				cout << endl;
				cout << "��ǰ�кţ�" << curLine << endl;
				auto pos = textBuffer.cbegin();
				for (int i = 0; i < curLine; i++) {
					pos++;
				}
				cout << *pos << endl;
			}
			cout << "������ָ�";
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
					//ת����һ��
					curLine = 0;
				break;

			case'e':
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else
					//ת�����һ��
					curLine = textBuffer.size()-1;
				break;

			case'p':
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else {
					if ((curLine - 1) >= 0) {
						//ת����һ��
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
						curLine++;//ת����һ��
					
				}
					
				break;
			case'g'://��תָ����
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else {
					//ת��ָ����
					int x;
					cout << "������ָ���У�";
					cin >> x;
					if (x < 0 || x >=textBuffer.size())
						cout << "��Χ����" << endl;
					else
					    curLine = x;
				}
				break;
			case'i'://��������
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else {
					string str;
					cout << "����������е����ݣ�";
					cin >> str;
					int x;
					cout << "����������е��кţ�";
					cin >> x;
					Insert(x, str);
				}
				break;
			case'd'://ɾ����ǰ��
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else {
					Delete();
				}
				break;
			case'v'://�鿴������
				if (textBuffer.empty() == true) {
					cout << "error: empty" << endl;
				}
				else {
					Show();
				}
				break;
			case'f'://����ĳһĿ�괮
			{
				cout << "�ӵ�һ�п�ʼ�������룺0 ||�ӵ�ǰ����ʼ�������룺1"<<endl;
			    int x;
			    while (1) {
					cout << "�����룺 ";
				     cin >> x;
				     if (x == 0 || x == 1) {
					      break;
				      }
				     cout << "�����������������" << endl;
			    }
			    cout << "������Ҫ���ҵ��ַ�����";
			    string substr;
			    cin >> substr;
			    cout<<"Ŀ�괮λ�ڵ�"<<Findstring(x, substr)<<"��"<<endl;
			    break;
			}
			case'c'://�滻�ı�
			{
				cout << "�ӵ�һ�п�ʼ�����滻���룺0 ||��ǰ�в����滻���룺1" << endl;
				int x;
				while (1) {
					cout << "�����룺 ";
					cin >> x;
					if (x == 0 || x == 1) {
						break;
					}
					cout << "�����������������" << endl;
				}
				string sub1;
				cout << "������Ҫ���ҵ��ַ�����";
				cin >> sub1;
				string sub2;
				cout << "������Ҫ�滻���ַ�����";
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
			case'q'://�˳�
				flag = 1;
				break;
			case'h':
			case'?':
				cout << "r:��ȡ�ı��ļ����������У�����������ǰ���κ����ݽ���ʧ����ǰ�����ļ��ĵ�һ��" << endl;
				cout << "w����������������д���ı��ļ�����ǰ�л򻺳��������ı�" << endl;
				cout << "i�����˵������У��û�������ǡ������ʾ������Ӧ���������в��ṩ���к�" << endl;
				cout << "d��ɾ����ǰ�в��Ƶ���һ��" << endl;
				cout << "f�����Դӵ�1�п�ʼ��ӵ�ǰ�п�ʼ�����Ұ������û������Ŀ�괮�ĵ�һ��" << endl;
				cout << "c���û�������ַ����޸ĳ��û�������滻�ı�����ѡ���ǽ��ڵ�ǰ������Ч�Ļ��Ƕ�ȫ����Ч��" << endl;
				cout << "q���˳��༭������������" << endl;
				cout << "h����ʾ������������İ�����Ϣ������Ҳ����?��ΪH�������" << endl;
				cout << "n����ǰ���Ƶ���һ�У�Ҳ�����Ƶ�����������һ��" << endl;
				cout << "p����ǰ���Ƶ���һ�У�Ҳ�����Ƶ�����������һ��" << endl;
				cout << "b����ǰ���Ƶ���ʼ����Ҳ�����Ƶ��������ĵ�һ��" << endl;
				cout << "e����ǰ���Ƶ���������Ҳ�����Ƶ������������һ��" << endl;
				cout << "g����ǰ���Ƶ������������û�ָ������" << endl;
				cout << "v������������ȫ�����ݴ�ӡ���ն���" << endl;
				break;
			default:
				cout << "ָ�����,������h��?�鿴����" << endl;
				break;
			}
			
				
		}
		
	}

};