#ifndef TIMER_H
#define TIMER_H

#include <bits/stdc++.h>
using namespace std;

class Timer {
	float time;
public:
	Timer();
	void Update(float dt);
	void Restart();
	float Get();
};

#endif
