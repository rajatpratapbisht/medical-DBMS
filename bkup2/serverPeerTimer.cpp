#include <iomanip>
#include <iostream>

#include "ServerPeerTimer.h"

ClientTimer::ClientTimer() {
	sum = duration<double, std::micro>(0);
	max = duration<double, std::micro>(0);
	min = duration<double, std::micro>(9999999999.9f);
	op_count = 0;
}

void ClientTimer::Start() {
	start_time = high_resolution_clock::now();
}

void ClientTimer::End() {
	auto end_time = high_resolution_clock::now();
	elapsed_time = (end_time - start_time);
}

void ClientTimer::EndAndMerge() {
	End();
	op_count++;
	sum += elapsed_time;
	if (elapsed_time < min) {
		min = elapsed_time;
	}
	if (elapsed_time > max) {
		max = elapsed_time;
	}
}

void ClientTimer::Merge(ClientTimer timer) {
	sum += timer.sum;
	op_count += timer.op_count;
	if (timer.min < min) {
		min = timer.min;
	}
	if (timer.max > max) {
		max = timer.max;
	}	
}

void ClientTimer::PrintStats() {
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "time per operation: "<<sum.count() / op_count << "\n";
	std::cout << "minimum time count: "<<min.count() << "\n";
	std::cout << "maximum time count: "<<max.count() << std::endl;
	std::cout << "latency :" <<op_count / elapsed_time.count() * 1000000.0f << std::endl;
}

