#include<MPprj/MPprj.h>
#include<fstream>
/*MY OWN NOTES

m - kitchens amount
М - max number
n - visits amount

/*tests:
	M = m - вектор случайная перестановка с уникальными значениями
	отношения между переменными
	k = m/M с шагом 0.5
*/

/* обработка измерений - отсеить слева и справа 10 процентов, гистограммы, усреднить значения
много векторов, 
для каких n : от 1 до 200000 включительно с шагом? n{2,10,100,500,2500, 5000, 7500, 12500, 25000, 50000, 100000, 200000}
m от 1 до n
M сделаем как n. У сформированного вектора pop_back() и push значение из n. = ПОЛУЧИЛИ НАБОР ЧИСЕЛ. Вектор длиной n сделать из набора. 
строим графики t/n (n) для разных соотношений? */

const std::vector<int> N{ 16, 160, 1600, 3200, 6400,  12800, 16000, 
19200, 22400, 25600, 28800, 32000, 35200, 38400, 41600, 44800, 48000, 
51200, 54400, 57600, 60800, 64000, 67200, 70400, 73600, 76800, 80000, 
83200, 86400, 89600, 92800, 96000, 99200, 102400, 105600, 108800, 112000, 
115200, 118400, 121600, 124800, 128000, 131200, 134400, 137600, 140800, 
144000, 147200, 150400, 153600, 156800, 160000, 163200, 166400, 169600, 
172800, 176000, 179200, 182400, 185600, 188800, 192000, 195200, 198400}; //n-values vector

int main() {
	//НЕ УДАЛЯЙ
	const int test_amount = 10;

	//vectors for m/M-test
	std::vector<std::vector<double>> input_duration1(test_amount), input_duration2(test_amount), output_duration1(test_amount), output_duration2(test_amount);

	for (int i = 1; i <= 8; i *= 2) { // m/M = 1, 1/2, ..., 1/8 
		std::vector<int> test;
		for (int n : N) {
			int M = n;
			int m = M / i;
			test_data_generator(i, n, test);
			to_test(test_amount, n, test, input_duration1, input_duration2, output_duration1, output_duration2);
		}
	} //data had beeen generated

	std::vector<std::string> names{ "input ex1", "input ex2", "output ex1", "output ex2" };
	std::vector<std::vector<std::vector<double>>> y;
	std::vector<double> x;

	make_graphics(test_amount, N, names, x, y, input_duration1, input_duration2, output_duration1, output_duration2);

	for (size_t k = 0; k < 4; k++) {
		make_png(k, names[k], x, y); //pictures had been done
	}
	//НЕ УДАЛЯЙ

	std::ofstream fout; //making a doc
	fout.open("results.md");
	fout << make_link("my repository","https://github.com/K-Grachev-2106756/grachev_k_y")<<
		make_paragraph()<<
		make_heading("Introduction")<< 
		"Everything is in English, because otherwise the characters turn into this: Абв"<<
		make_paragraph() <<
		"!!!The results can be reproduced."<<
		make_paragraph() <<
		"The tests were run for each value of k for each value of n 10 times. The output data are the average values of t/n." <<
		make_paragraph() <<
		"In the pictures we can see graphs of the dependence of t/n on n with a changing coefficient k = m/ M" 
		"(k = 1, 0.5, 0.25, 0.125 - no less, because with large amounts of data, gnuplot does not draw all graphs or does not draw anything)." <<
		make_paragraph() <<
		"For better scale and less data loss, t/n was multiplied by e+05 during calculations." <<
		make_paragraph() <<
		"On the left and right, the vectors of the calculated t/n values were cut off by 10% of their length." <<
		make_paragraph() <<
		"The tests were run separately for each graph: input_1, input_2, output_1, output_2." <<
		make_paragraph() <<
		"The results of the experiments are given below" <<
		make_paragraph() <<
		make_heading("About graphics :") <<
		"Input_1. In this graph, we can see that the more different the data, the worse the first program copes with data entry.Also note that our graph does not line up : the ratio t / n tends to zero as the argument n increases." <<
		make_paragraph() <<
		push_png(names[0]) <<
		make_paragraph() <<
		"Input_2.  This graph shows very strange lines. Therefore, it is difficult to judge the influence of the coefficient k for data entry of the second solution. Although on average, its speed exceeds the first solution." <<
		make_paragraph() <<
		push_png(names[1]) <<
		make_paragraph() <<
		"After analyzing the graphs, it can be noted that the second solution copes with its task more stably and faster." <<
		make_paragraph() <<
		"Output_1. The data processing time of the first solution quickly tends to zero with increasing n." <<
		make_paragraph() <<
		push_png(names[2]) <<
		make_paragraph() <<
		"Output_2. We can notice how high the value of the t/n ratio is. This suggests that the data processing speed for the second solution is very low. The first solution surpasses the second in places by hundreds of times." <<
		make_paragraph() <<
		push_png(names[3]) <<
		make_paragraph() <<
		"If we compare the data processing speed of both options, then the first solution wins unconditionally : in some places it wins the second one hundreds of times. Bottom line : although the second solution wins in the speed of information input, but it is not as significant as a total defeat in the speed of data processing. Our winner : the first decision." <<
		make_paragraph() <<
		make_paragraph();
	fout.close();
}