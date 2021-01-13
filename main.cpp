#include <iostream>
#include <fstream>
#include "evaluate.h"
using namespace std;

//��������� ������ �� ��������� ����
void load(string filename, string& input) {
	char next;
	ifstream in(filename);
	if (in.is_open())
	{
		while (!in.eof()) {
			next = in.peek();
			input += next;
			in.get();
		}
	}
	else cout << "Unable to open the file. Check the name of the file.";
	in.close();

}

//��������� ��������� � ������� ����
void save(string filename, stack<double>& output) {
	ofstream out;
	out.open(filename);
	if (out)
	{
		while (!output.empty()) {
			out << output.top();
			out << ' ';
			output.pop();
		}
		cout << "Successfully saved result." << endl;
	}
	else cout << "Unable to save information in this file." << endl;

	out.close();

}
int main() {


	string fileForInput, input = "", fileForResult;
	cout << "Enter the name of the file with expression to evaluate: ";
	cin >> fileForInput;
	load(fileForInput, input);

	//cout << "Expression: " << input << endl;

	stack<double> s;
	s = evaluate(input);

	// ��� ������ �� � ������, �� ������ � �������� ����� � �������
	// � ������� �������� �����.
	if (!s.empty()) {
		cout << endl;
		cout << "Enter the name of the wanted file to save the result in: ";
		cin >> fileForResult;
		save(fileForResult, s);
	}


	return 0;
}