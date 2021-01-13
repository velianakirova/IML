#pragma once
#include <queue>
#include "commands.h"
using namespace std;

class AGG : public Command {
public:

	static queue<double> apply(stack<double> nums, string command, string tagAddition, int fromIndex, int& howNumbersToRemove);

	static void agg(queue<double>& result, string wanted);

};
queue<double> AGG::apply(stack<double> nums, string command, string tagAddition, int fromIndex, int& howNumbersToRemove) {
	queue<double> result;
	copyFromIndex(nums, fromIndex, result);
	howNumbersToRemove = result.size();
	if (command == "AGG-SUM") {
		agg(result, "SUM");
	}
	else if (command == "AGG-PRO") {
		agg(result, "PRO");
	}
	else if (command == "AGG-AVG") {
		agg(result, "AVG");
	}
	else if (command == "AGG-FST") {
		agg(result, "FST");
	}
	else if (command == "AGG-LST") {
		agg(result, "LST");
	}
	return result;
}

void AGG::agg(queue<double>& result, string wanted) {
	double sum = 0;
	double count = 0;
	double pro = 1;
	double first = result.front();
	double last;
	while (!result.empty()) {
		last = result.front();
		sum += result.front();
		pro *= result.front();
		count++;
		result.pop();
	}

	if (wanted == "SUM") result.push(sum);
	else if (wanted == "PRO") result.push(pro);
	else if (wanted == "AVG") result.push(sum / count);
	else if (wanted == "FST") result.push(first);
	else if (wanted == "LST") result.push(last);
}

