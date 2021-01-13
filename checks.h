#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <cstring>
#include "helpers.h"
using namespace std;


//проверава дали таговете са в правилна подредба
bool checkTags(string input) {
	stack<string> s;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '<') {
			int checkFrom = i + 2;
			if (input[i + 1] != '/') s.push(readOpeningTag(input, i));
			else if (!s.empty() && readOpeningTag(input, checkFrom) == s.top()) {
				s.pop();
			}
			else {
				cout << "Take a look at " << s.top() << " and its closing tag. " << endl;
				return false;
			}
		}
	}
	return s.empty();
}


//проверява дали тагът съществува в езика
bool isTagPartOfIML(string tag) {
	if (tag == "MAP-INC" || tag == "MAP-MLT" || tag == "AGG-SUM" || tag == "AGG-PRO" || tag == "AGG-AVG" || tag == "AGG-FST" || tag == "AGG-LST" || tag == "SRT-REV" || tag == "SRT-ORD" || tag == "SRT-SLC" || tag == "SRT-DST") return true;
	return false;
}

//дали допънението към команда е число
bool isAdditionNumber(string addition) {
	for (int i = 0; i < addition.size(); i++) {
		if (addition[i] <= '0' || addition[i] >= '9') return false;
	}
	return true;
}

//ако командата изисква допълнение, проверява дали то е подходящо за нея
bool isSRTAdditionCorrect(string command, string addition) {
	if (command == "SRT-ORD" && (addition == "ASC" || addition == "DSC")) return true;
	else if (command == "SRT-SLC" && isAdditionNumber(addition)) return true;
	else return false;
}

//отбелязва кои команди изискват допълнение
bool hasCommandAddition(string command) {
	if (command == "MAP-INC" || command == "MAP-MLT" || command == "SRT-ORD" || command == "SRT-SLC") return true;
	return false;
}