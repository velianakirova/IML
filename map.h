#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include "commands.h"
using namespace std;

class MAP : public Command {
public:

	static queue<double> apply(stack<double> nums, string command, string tagAddition, int fromIndex, int& howNumbersToRemove);

	static double mapHelper(char op, double originalNum, double incOrMltWith);

	static void map(queue<double>& result, char op, string tagAddition);

	static double useAddition(string tagAddition, int i);

};


queue<double> MAP::apply(stack<double> nums, string command, string tagAddition, int fromIndex, int& howNumbersToRemove) {
	queue<double> result;
	copyFromIndex(nums, fromIndex, result);
	howNumbersToRemove = result.size();
	if (command == "MAP-INC") {
		map(result, '+', tagAddition);
	}
	else if (command == "MAP-MLT") {
		map(result, '*', tagAddition);
	}

	return result;
}

double MAP::mapHelper(char op, double originalNum, double incOrMltWith) {
	if (op == '+') return originalNum + incOrMltWith;
	else if (op == '*') return originalNum * incOrMltWith;
}

void MAP::map(queue<double>& result, char op, string tagAddition) {
	const double size = result.size();
	double* arr = new double[size];

	for (int i = 0; i < size; i++) {
		if (tagAddition[0] != '-') arr[i] = mapHelper(op, result.front(), useAddition(tagAddition, 0));
		else arr[i] = mapHelper(op, result.front(), (-1) * (useAddition(tagAddition, 1)));
		result.pop();
	}
	for (int i = 0; i < size; i++) {
		result.push(arr[i]);
	}
	delete[] arr;
}

double MAP::useAddition(string tagAddition, int i) {
	double tagAdd = 0;
	for (; i < tagAddition.size(); i++) {
		tagAdd = tagAdd * 10 + (int)(tagAddition[i] - '0');
	}
	return tagAdd;
}
