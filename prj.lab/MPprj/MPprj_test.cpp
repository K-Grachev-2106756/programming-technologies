#include<MPprj/MPprj.h>
#include<algorithm>
#include <random>
using namespace matplot;

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
//для каких n : от 1 до 200000 включительно с шагом? n{2,10,100,500,2500, 5000, 7500, 12500, 25000, 50000, 100000, 200000}
//m от 1 до n
//M сделаем как n. У сформированного вектора pop_back() и push значение из n. = ПОЛУЧИЛИ НАБОР ЧИСЕЛ. Вектор длиной n сделать из набора. 
//строим графики t/n (n) для разных соотношений? 


std::vector<int> N{ 16, 160, 1600, 3200, 6400, 9600, 12800, 16000, 
19200, 22400, 25600, 28800, 32000, 35200, 38400, 41600, 44800, 48000, 
51200, 54400, 57600, 60800, 64000, 67200, 70400, 73600, 76800, 80000, 
83200, 86400, 89600, 92800, 96000, 99200, 102400, 105600, 108800, 112000, 
115200, 118400, 121600, 124800, 128000, 131200, 134400, 137600, 140800, 
144000, 147200, 150400, 153600, 156800, 160000, 163200, 166400, 169600, 
172800, 176000, 179200, 182400, 185600, 188800, 192000, 195200, 198400}; //вектор значений n

int main() {
	std::vector<int>(*inp_first_ex)(int, std::vector<int>) = input_first_example;//указатели на тестируемые функции
	std::vector<int>(*inp_sec_ex)(int, std::vector<int>) = input_second_example;
	void(*outp_first_ex)(int, std::vector<int>) = output_first_example;
	void(*outp_sec_ex)(int, std::vector<int>) = output_second_example;


	//тест для m/M шаг 1/2
	// m = 1, M = n
	// m = n/2, M = n
	// m = n, M = n

	//векторы для замеров в тесте m/M
	const int test_amount = 10;
	std::vector<std::vector<double>> input_duration1(test_amount), input_duration2(test_amount), output_duration1(test_amount), output_duration2(test_amount);


	for (int i = 1; i <= 16; i *= 2) {
		int m, M;
		std::vector<int> test;
		for (int k = 0; k < i; k++) test.push_back(0);
		for (int n : N) {
			M = n;
			m = M / i;
			for (int el = test.back() + 1; test.size() < n - i; el++) {
				for (int k = 0; k < i; k++) {
					test.push_back(el);
				}
			}
			for (int k = 0; k < i; k++) test.push_back(n);
			auto rng = std::default_random_engine{};
			std::shuffle(test.begin(), test.end(), rng); //генерация тестовых данных

			//сбор данных для каждого n для каждого отношения m/M
			for (int k = 0; k < test_amount; k++) {
				std::pair<std::chrono::duration<float>, std::chrono::duration<float>> duration1 = //получаем пары значений замеров
					Timer_for_solution(inp_first_ex, outp_first_ex, n, test);
				input_duration1[k].push_back((double)duration1.first.count());
				output_duration1[k].push_back((double)duration1.second.count());

				std::pair<std::chrono::duration<float>, std::chrono::duration<float>> duration2 = //замеры для второго решения
					Timer_for_solution(inp_sec_ex, outp_sec_ex, n, test);
				input_duration2[k].push_back((double)duration2.first.count());
				output_duration2[k].push_back((double)duration2.second.count());
			}
		}

	}

	const int gen_size = N.size() * 4 / 5;
	std::vector<double> gen_input_dur1(N.size()), gen_input_dur2(N.size()), gen_output_dur1(N.size()), gen_output_dur2(N.size());

	for (size_t i = 0; i < N.size(); i++) {
		for (size_t k = 0; k < test_amount; k++) {
			gen_input_dur1[i] += input_duration1[k][i];
			gen_input_dur2[i] += input_duration2[k][i];
			gen_output_dur1[i] += output_duration1[k][i];
			gen_output_dur2[i] += output_duration2[k][i];
		}
	}

	std::vector<double> x, y;
	for (size_t i = N.size()/10; i < N.size()*9/10; i++)
	{
		x.push_back(N[i] / 1000);
		y.push_back(gen_input_dur1[i] / test_amount/ x.back());
	}
	/*for (size_t i = 0; i < N.size(); i++)
	{
		std::cout << gen_input_dur1[i] << std::endl;
	}*/

	plot(x, y,"bo--");
	show();
}