#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <cstring>
#include "checks.h"
#include "map.h"
#include "agg.h"
#include "srt.h"
using namespace std;

stack<double> evaluate(string input) {

	bool isInputCorrect = true;
	stack<double> nums;
	stack<string> commands;
	stack<string> additions;
	stack<double> fromIndex;
	double index = -1;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '<' && input[i + 1] != '/') {
			string command = readOpeningTag(input, i);
			if (isTagPartOfIML(command)) commands.push(command);
			else {
				cout << "Invalid tag appeard. Check your tags." << endl;
				cout << "(Possible error: tag " << command << " does not exist in IML.)" << endl;
				isInputCorrect = false;
				break;
			}

			//ако има допълнение към команда, която изисква допълнение
			if (input[i] == ' ' && input[i + 1] == '\"' && hasCommandAddition(command)) additions.push(tagAddition(input, i));
			//ако има допълннение, но командата не изисква такова
			else if (input[i] == ' ' && input[i + 1] == '\"' && !hasCommandAddition(command)) {
				cout << "Check the opening tag " << command << ". It does not have an addition." << endl;
				isInputCorrect = false;
				break;
			}
			//ако командата изисква допълнение, но такова не е хосочено в израза
			else if (hasCommandAddition(command) && (input[i] != ' ' || input[i + 1] != '\"')) {
				cout << "Check the opening tag " << command << ". The addition is missing." << endl;
				isInputCorrect = false;
				break;
			}
			fromIndex.push(index + 1);
		}
		else if (input[i] >= '0' && input[i] <= '9' && input[i - 1] != '\"' && input[i + 1] != '\"' && (input[i + 1] == ' ' || input[i + 1] == '<')) {
			if (input[i - 1] == '-') nums.push((-1) *(double) (input[i] - '0'));
			else nums.push((double)(input[i] - '0'));
			index++;
			//cout << input[i] << " is pushed." << endl;
		}
		else if (input[i] >= '0' && input[i] <= '9' && input[i - 1] != '\"' && input[i + 1] != '\"' && input[i + 1] >= '0' && input[i + 1] <= '9') {
			double num = double(input[i] - '0');
			while (input[i + 1] != ' ' && input[i + 1] != '<') {
				num = num * 10 + input[i + 1] - 48;
				i++;
			}
			if (input[i - 1] == '-') nums.push((-1) * num);
			else nums.push(num);
			index++;
			//cout << num << " is pushed." << endl;
		}
		else if ((((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) &&
			((input[i - 1] == ' ' && input[i + 1] == ' ') ||
				(input[i - 1] == ' ' && (input[i + 1] == '<' || input[i + 1] >= '0' && input[i + 1] <= '9')) ||
				(input[i + 1] == ' ' && (input[i - 1] == '>' || input[i - 1] >= '0' && input[i - 1] <= '9'))))) {

			isInputCorrect = false;
			cout << "Incorrect input." << endl << "(Possible mistake: '" << input[i] << "' is not supposed to be there." << endl;
			break;

		}
		else if (input[i] == '<' && input[i + 1] == '/') {
			if (checkTags(input)) {
				//cout << "\n Command: " << commands.top();
				string currCommand = commands.top(); commands.pop();
				double currFromIndex = fromIndex.top(); fromIndex.pop();
				int howNumbersToRemove;
				queue<double> temp;
				if (currCommand == "MAP-INC" || currCommand == "MAP-MLT") {
					//cout << "\n Tag Addition: " << additions.top() << endl;
					if (isAdditionNumber(additions.top()))
					{
						temp = MAP::apply(nums, currCommand, additions.top(), currFromIndex, howNumbersToRemove);
						additions.pop();
						//cout << "Correct addition";
					}
					else {
						cout << "Invalid input. Check the correction of the tags." << endl;
						isInputCorrect = false;
						break;
					}
				}
				else if (currCommand == "AGG-SUM" || currCommand == "AGG-PRO" || currCommand == "AGG-AVG" || currCommand == "AGG-FST" || currCommand == "AGG-LST") {
					//cout << "\n Tag Addition: \"none\" ";
					temp = AGG::apply(nums, currCommand, "", currFromIndex, howNumbersToRemove);
				}
				else if (currCommand == "SRT-ORD" || currCommand == "SRT-SLC") {
					if (isSRTAdditionCorrect(currCommand, additions.top())) {
						//cout << "\n Tag Addition: " << additions.top();
						temp = SRT::apply(nums, currCommand, additions.top(), currFromIndex, howNumbersToRemove);
						additions.pop();
					}
					else {
						cout << "Invalid input. Check the correction of the tags." << endl;
						isInputCorrect = false;
						break;
					}

				}
				else {
					//cout << "\n Tag Addition: \"none\" ";
					temp = SRT::apply(nums, currCommand, "", currFromIndex, howNumbersToRemove);
				}


				while (howNumbersToRemove > 0) { nums.pop(); howNumbersToRemove--; }

				//cout << "\n QUEUE: ";
				while (!temp.empty()) {
					//cout << temp.front() << " ";
					nums.push(temp.front());
					temp.pop();
				}
				//cout << endl;

			}
			else {
				isInputCorrect = false;
				cout << "Incorrect nesting." << endl;
				break;
			}
		}
	}


	if (!isInputCorrect) {
		while (!nums.empty()) {
			nums.pop();
		}
	}
	return nums;
}
