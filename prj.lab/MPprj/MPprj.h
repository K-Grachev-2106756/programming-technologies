#include<iostream>
#include<vector>

#include<chrono>

#include<cmath>
#include<matplot/matplot.h>

// m - число столовых
// М - максимальный номер 
// n - число посещений

/*тесты:
	M = m - вектор случайная перестановка с уникальными значениями 
	отношения между переменными
	k = m/M с шагом 0.5
*/

//обработка измерений - отсеить слева и справа 10 процентов, гистограммы, усреднить значения 
//много векторов, 

class Timer {
public:
	Timer() {
		start = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - start;
		std::cout << duration.count() << " s"<<std::endl;
	}
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
};

std::pair<std::chrono::duration<float>, std::chrono::duration<float>> Timer_for_solution
(std::vector<int>(*f1)(int, std::vector<int>), void(*f2)(int, std::vector<int>), int n, std::vector<int> data);


std::vector<int> input_first_example(int n, std::vector<int> data);
std::vector<int> input_second_example(int n, std::vector<int> data);
void output_first_example(int n, std::vector<int> data);
void output_second_example(int n, std::vector<int> data);