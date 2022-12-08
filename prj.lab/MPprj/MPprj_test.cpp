#include<MPprj/MPprj.h>

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

	//wchar_t* str = L"аьвьаьваь";
	//std::ofstream fout; //making a doc
	//fout.open("results.md");
	//fout<<ConvertToUTF8(str);

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

	make_md_rus(names); //making report in Russian

}