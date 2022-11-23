#include<MPprj/MPprj.h>
#include<algorithm>
#include <random>
#include<string>

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


std::vector<int> N{ 16, 160, 1600, 3200, 6400,  12800, 16000, 
19200, 22400, 25600, 28800, 32000, 35200, 38400, 41600, 44800, 48000, 
51200, 54400, 57600, 60800, 64000, 67200, 70400, 73600, 76800, 80000, 
83200, 86400, 89600, 92800, 96000, 99200, 102400, 105600, 108800, 112000, 
115200, 118400, 121600, 124800, 128000, 131200, 134400, 137600, 140800, 
144000, 147200, 150400, 153600, 156800, 160000, 163200, 166400, 169600, 
172800, 176000, 179200, 182400, 185600, 188800, 192000, 195200, 198400}; //вектор значений n

//std::vector<int> N{ 160,1600,3200,9600, 16000, 25600,41600, 60800, 92800, 128000,  160000,192000 };

int main() {
	std::vector<int>(*inp_first_ex)(int, std::vector<int>) = input_first_example;//указатели на тестируемые функции
	std::vector<int>(*inp_sec_ex)(int, std::vector<int>) = input_second_example;
	void(*outp_first_ex)(int, std::vector<int>) = output_first_example;
	void(*outp_sec_ex)(int, std::vector<int>) = output_second_example;

	//векторы для замеров в тесте m/M
	const int test_amount = 10;
	std::vector<std::vector<double>> input_duration1(test_amount), input_duration2(test_amount), output_duration1(test_amount), output_duration2(test_amount);


	for (int i = 1; i <= 8; i *= 2) { // m/M = 1, 1/2, ..., 1/8 
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
	std::vector<double> gen_input_dur1(N.size()*4), gen_input_dur2(N.size()*4), gen_output_dur1(N.size()*4), gen_output_dur2(N.size()*4);

	std::vector<std::vector<double>> y1(4), y2(4), y3(4), y4(4);
	std::vector<double> x;
	for (size_t i = N.size() / 10; i < N.size() * 9 / 10; i++) {
		x.push_back(N[i] / 1000);
	}

	for (size_t k = 0; k < 4; k++)
	{
		for (size_t i = N.size()*k; i < N.size()*(k+1); i++) {
			for (size_t k = 0; k < test_amount; k++) {
				gen_input_dur1[i] += input_duration1[k][i];
				gen_input_dur2[i] += input_duration2[k][i];
				gen_output_dur1[i] += output_duration1[k][i];
				gen_output_dur2[i] += output_duration2[k][i];
			}
		}
		for (size_t i = N.size()*k + N.size() / 10, ind = 0; i < N.size() * k + N.size() * 9 / 10; i++, ind++) {
			y1[k].push_back(gen_input_dur1[i] / test_amount / x[ind]);
			y2[k].push_back(gen_input_dur2[i] / test_amount / x[ind]);
			y3[k].push_back(gen_output_dur1[i] / test_amount / x[ind]);
			y4[k].push_back(gen_output_dur2[i] / test_amount / x[ind]);
		}	
	}
	
	auto ax1 = matplot::nexttile(), ax2 = matplot::nexttile(), ax3 = matplot::nexttile(), ax4 = matplot::nexttile();

	matplot::hold(matplot::on);
	matplot::xlabel("n*e-3");
	matplot::ylabel("t/n*e+3");
	matplot::title("input ex1");

	auto p1 = plot(ax1,x, y1[0]); 
	p1->display_name("k=1");	
	auto p2 = plot(ax1,x, y1[1]);
	p2->display_name("0.5");	
	auto p3 = plot(ax1, x, y1[2]);
	p3->display_name("0.25");	
	auto p4 = plot(ax1, x, y1[3]);
	p4->display_name("0.125");
	
	matplot::legend();

	matplot::hold(matplot::on);
	matplot::xlabel("n*e-4");
	matplot::ylabel("t/n*e+4");
	matplot::title("input ex2");

	auto p5 = plot(ax2, x, y2[0]);
	p5->display_name("k=1");
	auto p6 = plot(ax2, x, y2[1]);
	p6->display_name("0.5");
	auto p7 = plot(ax2, x, y2[2]);
	p7->display_name("0.25");
	auto p8 = plot(ax2, x, y2[3]);
	p8->display_name("0.125");

	matplot::legend();

	matplot::hold(matplot::on);
	matplot::xlabel("n*e-3");
	matplot::ylabel("t/n*e+3");
	matplot::title("output ex1");

	auto p9 = plot(ax3, x, y3[0]);
	p9->display_name("k=1");
	auto p10 = plot(ax3, x, y3[1]);
	p10->display_name("0.5");
	auto p11 = plot(ax3, x, y3[2]);
	p11->display_name("0.25");
	auto p12 = plot(ax3, x, y3[3]);
	p12->display_name("0.125");

	matplot::legend();

	matplot::hold(matplot::on);
	matplot::xlabel("n*e-3");
	matplot::ylabel("t/n*e+3");
	matplot::title("output ex2");

	auto p13 = plot(ax4, x, y4[0]);
	p13->display_name("k=1");
	auto p14 = plot(ax4, x, y4[1]);
	p14->display_name("0.5");
	auto p15 = plot(ax4, x, y4[2]);
	p15->display_name("0.25");
	auto p16 = plot(ax4, x, y4[3]);
	p16->display_name("0.125");

	matplot::legend();

	matplot::show();
}