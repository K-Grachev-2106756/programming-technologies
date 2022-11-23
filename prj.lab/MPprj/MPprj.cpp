#include<MPprj/MPprj.h>
#include <iterator>
#include <algorithm>
#include <unordered_set>

std::pair<std::chrono::duration<float>, std::chrono::duration<float>> Timer_for_solution
(std::vector<int>(*f1)(int, std::vector<int>), void(*f2)(int, std::vector<int>), int n, std::vector<int> data) {
	std::chrono::time_point<std::chrono::steady_clock> start_input, end_input, start_output, end_output;//переменные для хранения замеров
	
	start_input = std::chrono::high_resolution_clock::now();	//замер ввода данных
	std::vector<int> vec = f1(n, data);		//хранение результата для последующей обработки данных
	end_input = std::chrono::high_resolution_clock::now();

	start_output = std::chrono::high_resolution_clock::now();	//замер обработки данных
	f2(n, vec);
	end_output = std::chrono::high_resolution_clock::now();

	return { end_input - start_input, end_output - start_output };	//вывод результатов замеров
}

std::vector<int> input_first_example(int n, std::vector<int> vec) {
	std::vector<int> as(200001, -1);
	for (int i = 0; i < n; i += 1) {
		int idx = vec[i];
		as[idx] = n - i - 1;
	}
	return as;
}

std::vector<int> input_second_example(int n, std::vector<int> vec) {
	std::vector<int> data(n, 0);
	for (int i = 0; i < n; i += 1) {
		data[i] = vec[i];
	}
	return data;
}

void output_first_example(int n, std::vector<int> data) {
	int res = std::distance(data.begin(),
		std::max_element(data.begin(), data.end()));
}

void output_second_example(int n, std::vector<int> data) {
	std::unordered_set<int> unique;
	unique.reserve(200000);
	int idx_unique = n;
	for (int i = n - 1; 0 <= i; i -= 1) {
		if (unique.find(data[i])==unique.end()) {
			idx_unique = data[i];
			unique.insert(idx_unique);
		}
	}
}