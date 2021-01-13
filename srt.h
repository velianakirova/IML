#pragma once
#include <queue>
#include "commands.h"
using namespace std;

class SRT : public Command {
public:

	static queue<double> apply(stack<double> nums, string command, string tagAddition, int fromIndex, int& howNumbersToRemove);

};

queue<double> SRT::apply(stack<double> nums, string command, string tagAddition, int fromIndex, int& howNumbersToRemove) {
	queue<double> result;
	copyFromIndex(nums, fromIndex, result);
	howNumbersToRemove = result.size();
	if (command == "SRT-REV") {
		return result;
	}
	else if (command == "SRT-ORD") {
		int size = result.size();
		double* arr = new double[size];

		for (int i = 0; i < size; i++) {
			arr[i] = result.front();
			result.pop();
		}

		sortArr(arr, size);
		for (int i = 0; i < size; i++) {
			result.push(arr[i]);
		}

		if (tagAddition == "ASC") reverse(result);
		delete[] arr;
	}
	else if (command == "SRT-SLC") {
		stack<double> numsSave;
		reverse(result);
		while (!result.empty()) {
			numsSave.push(result.front());
			result.pop();
		}
		copyFromIndex(numsSave, tagAddition[0] - '0', result);
		reverse(result);
	}
	else if (command == "SRT-DST") {
		double* arr = new double[result.size()];
		int i = 0;
		arr[i] = -50;

		while (!result.empty()) {

			bool flag = false;

			//проверява дали някое от добавените в масива числа съвпада 
			//със следващото по ред от опашката, което трябва да се добави
			for (int j = 0; j <= i; j++) {
				if (arr[j] == result.front()) flag = true;
			}

			//ако такова число все още няма в масива, го добавяме 
			if (flag == false) {
				arr[i] = result.front();
				i++;
			}

			result.pop();
		}

		for (int j = 0; j < i; j++) {
			result.push(arr[j]);
		}

		delete[] arr;
	}

	return result;
}
