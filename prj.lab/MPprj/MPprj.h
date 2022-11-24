#include<iostream>
#include<vector>
#include<string>

#include<algorithm>
#include <random>

#include<chrono>

#include<cmath>
#include<matplot/matplot.h>

#include <iterator>
#include <unordered_set>

std::pair<std::chrono::duration<float>, std::chrono::duration<float>> Timer_for_solution
(std::vector<int>(*f1)(int, std::vector<int>), void(*f2)(int, std::vector<int>), int n, std::vector<int> data);


std::vector<int> input_first_example(int n, std::vector<int> data);
std::vector<int> input_second_example(int n, std::vector<int> data);
void output_first_example(int n, std::vector<int> data);
void output_second_example(int n, std::vector<int> data);

void test_data_generator(int i, int n, std::vector<int>& test);

void to_test(const int test_amount, const int n, std::vector<int>& test, std::vector<std::vector<double>>& input_duration1, //сбор данных для каждого n для каждого отношения m/M
	std::vector<std::vector<double>>& input_duration2, std::vector<std::vector<double>>& output_duration1, std::vector<std::vector<double>>& output_duration2);

void make_graphics(const int test_amount, const std::vector<int>& N, const std::vector<std::string>& names, std::vector<double>& x,
	std::vector<std::vector<std::vector<double>>>& y, std::vector<std::vector<double>>& input_duration1, std::vector<std::vector<double>>& input_duration2,
	std::vector<std::vector<double>>& output_duration1, std::vector<std::vector<double>>& output_duration2);

void make_png(const int k, const std::string& names, std::vector<double>& x, std::vector<std::vector<std::vector<double>>>& y);

std::string make_paragraph();
std::string push_png(std::string img);