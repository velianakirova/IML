#pragma once

#include<iostream>
#include<cstring>
#include<stack>
#include<queue>
using namespace std;

//чете командите
string readOpeningTag(string& input, int& index) {
	if (input == "") return "";
	string tag = "";
	for (; index < input.size(); index++) {
		if (input[index] != ' ' && input[index] != '>') {
			if (input[index] != '<')
				tag += input[index];
		}
		else break;
	}
	return tag;
}

//допълнение към команда
string tagAddition(string& input, int& i) {
	bool flagAddition = false;
	string addition = "";
	for (; i < input.size(); i++) {
		if (input[i] == ' ') flagAddition = true;
		if (flagAddition && input[i] != '\"' && input[i] != '>' && input[i] != ' ') {
			addition += input[i];
		}
		if (input[i] == '>') break;
	}
	return addition;
}


//копира числа от стек от даден индекс нататък в опашка
void copyFromIndex(stack<double> nums, double index, queue<double>& result) {
	int doWhile = nums.size() - 1;
	while (doWhile >= index) {
		result.push(nums.top());
		nums.pop();
		doWhile--;
	}
}


//обръща опашка
void reverse(queue<double>& result) {
	double arr[20];
	double size = result.size();
	for (int i = 0; i < size; i++) {
		arr[i] = result.front();
		result.pop();
	}
	for (int i = size - 1; i >= 0; i--) {
		result.push(arr[i]);
	}
}

//сортира масив
void sortArr(double arr[], double size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (arr[j] < arr[j + 1]) swap(arr[j], arr[j + 1]);
		}
	}
}

