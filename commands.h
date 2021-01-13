#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include "helpers.h"
using namespace std;

class Command {
public:
	virtual queue<double> apply(stack<double> nums, string command, string tagAddition, int fromIndex, int& howNumbersToRemove) = 0;

};


