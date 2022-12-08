#include<MPprj/MPprj.h>
#if defined(_MSC_VER) && _MSC_VER > 1310
# define utf8(str)  ConvertToUTF8(L##str)
const char* ConvertToUTF8(const wchar_t* pStr) {
	static char szBuf[5120];
	WideCharToMultiByte(CP_UTF8, 0, pStr, -1, szBuf, sizeof(szBuf), NULL, NULL);
	return szBuf;
}
#else
// Visual C++ 2003 and gcc will use the string literals as is, so the files 
// should be saved as UTF-8. gcc requires the files to not have a UTF-8 BOM.
# define utf8(str)  str
#endif
std::pair<std::chrono::duration<float>, std::chrono::duration<float>> Timer_for_solution
(std::vector<int>(*f1)(int, std::vector<int>), void(*f2)(int, std::vector<int>), int n, std::vector<int> data) {
	std::chrono::time_point<std::chrono::steady_clock> start_input, end_input, start_output, end_output;//переменные для хранения замеров
	
	start_input = std::chrono::high_resolution_clock::now();	//замер ввода данных
	std::vector<int> vec = f1(n, data);		//хранение результата для последующей обработки данных
	end_input = std::chrono::high_resolution_clock::now();

	start_output = std::chrono::high_resolution_clock::now();	//замер обработки данных
	f2(n, vec);
	end_output = std::chrono::high_resolution_clock::now();

	return { (end_input - start_input), (end_output - start_output) };	//вывод результатов замеров
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

void test_data_generator(int i, int n, std::vector<int>& test) {
	for (int k = 0; k < i; k++) test.push_back(0);
	for (int el = test.back() + 1; test.size() < n - i; el++) {
		for (int k = 0; k < i; k++) {
			test.push_back(el);
		}
	}
	for (int k = 0; k < i; k++) test.push_back(n);
	auto rng = std::default_random_engine{};
	std::shuffle(test.begin(), test.end(), rng); //test generation
}

void to_test(const int test_amount, const int n, std::vector<int>& test, std::vector<std::vector<double>>& input_duration1, //getting data
std::vector<std::vector<double>>& input_duration2, std::vector<std::vector<double>>& output_duration1, std::vector<std::vector<double>>& output_duration2) {

	std::vector<int>(*inp_first_ex)(int, std::vector<int>) = input_first_example;	//pointers for functions
	std::vector<int>(*inp_sec_ex)(int, std::vector<int>) = input_second_example;
	void(*outp_first_ex)(int, std::vector<int>) = output_first_example;
	void(*outp_sec_ex)(int, std::vector<int>) = output_second_example;

	for (int k = 0; k < test_amount; k++) {
		std::pair<std::chrono::duration<float>, std::chrono::duration<float>> duration1 = //getting pairs of results 
			Timer_for_solution(inp_first_ex, outp_first_ex, n, test);
		input_duration1[k].push_back((double)duration1.first.count());
		output_duration1[k].push_back((double)duration1.second.count());

		std::pair<std::chrono::duration<float>, std::chrono::duration<float>> duration2 = //results for the second solution
			Timer_for_solution(inp_sec_ex, outp_sec_ex, n, test);
		input_duration2[k].push_back((double)duration2.first.count());
		output_duration2[k].push_back((double)duration2.second.count());
	}
}

void make_graphics(const int test_amount, const std::vector<int>& N, const std::vector<std::string>& names, std::vector<double>& x, 
std::vector<std::vector<std::vector<double>>>& y, std::vector<std::vector<double>>& input_duration1, std::vector<std::vector<double>>& input_duration2, 
std::vector<std::vector<double>>& output_duration1, std::vector<std::vector<double>>& output_duration2) {

	const int size = N.size();
	std::vector<double> gen_in_dur1(size * 4), gen_in_dur2(size * 4), gen_out_dur1(size * 4), gen_out_dur2(size * 4);

	y= std::vector<std::vector<std::vector<double>>>(4, std::vector<std::vector<double>>(4));

	for (size_t i = size / 10; i < size * 9 / 10; i++) {
		x.push_back(N[i]);
	}

	for (size_t k = 0; k < 4; k++)
	{
		for (size_t i = size * k; i < size * (k + 1); i++) {
			for (size_t k = 0; k < test_amount; k++) {
				gen_in_dur1[i] += input_duration1[k][i];
				gen_in_dur2[i] += input_duration2[k][i];
				gen_out_dur1[i] += output_duration1[k][i];
				gen_out_dur2[i] += output_duration2[k][i];
			}
		}
		for (size_t i = size * k + size / 10, ind = 0; i < size * k + size * 9 / 10; i++, ind++) {
			y[0][k].push_back(gen_in_dur1[i]*100000 / test_amount / x[ind]);
			y[1][k].push_back(gen_in_dur2[i] * 100000 / test_amount / x[ind]);
			y[2][k].push_back(gen_out_dur1[i] * 100000 / test_amount / x[ind]);
			y[3][k].push_back(gen_out_dur2[i] * 100000 / test_amount / x[ind]);
		}
	}
}

void make_png(const int k, const std::string& names, std::vector<double>& x, std::vector<std::vector<std::vector<double>>>& y) {
		auto ax1 = matplot::figure();
		matplot::hold(matplot::on);
		matplot::xlabel("n");
		matplot::ylabel("t/n*e+05");
		matplot::title(names);

		auto p1 = matplot::plot(x, y[k][0]);
		auto p2 = matplot::plot(x, y[k][1]);
		auto p3 = matplot::plot(x, y[k][2]);
		auto p4 = matplot::plot(x, y[k][3]);
		matplot::hold(matplot::off);
		matplot::save(names + ".png");
		matplot::show();

		//auto ax = matplot::nexttile();
		//matplot::hold(matplot::on);
		//matplot::xlabel("n*e-2");
		//matplot::ylabel("t/n*e+3");
		//matplot::title(names[k]);

		//auto p1 = matplot::plot(ax, x, y[k][0]);
		//p1->display_name("k=1");
		//auto p2 = matplot::plot(ax, x, y[k][1]);
		//p2->display_name("0.5");
		//auto l = matplot::legend();
		//matplot::save(names[k] + ".png");
}


std::wstring make_paragraph() {
	return L"<br/><br/>";
}

std::wstring push_png(std::string img) {
	std::string tmp = "![[" + img + ".png]]";
	return std::wstring(tmp.begin(), tmp.end());
}



std::wstring make_heading(std::wstring name) {
	//std::string tmp = "\n## " + name +"\n";
	//return std::wstring(tmp.begin(), tmp.end());
	return L"\n## " + name + L"\n";
}

std::wstring make_link(std::wstring name, std::wstring link) {
	//std::string tmp = "[" + name + "](" + link + ")";
	//return std::wstring(tmp.begin(), tmp.end());
	return L"[" + name + L"](" + link + L")";
}



void make_md_rus(std::vector<std::string> names) {
	std::wstring mainTEXT = make_link(L"Мой репозиторий", L"https://github.com/K-Grachev-2106756/grachev_k_y") +
		make_paragraph() +
		make_heading(L"Вступление") +
		L"!!!Результаты могут быть воспроизведены." +
		make_paragraph() +
		L"Тесты проводились для каждого значения k для каждого значения n 10 раз. Выходные данные представляют собой средние значения t/n." +
		make_paragraph() +
		L"На рисунках мы можем видеть графики зависимости t/n от n с изменяющимся коэффициентом k = m/M"
		L" (k = 1, 0,5, 0,25, 0,125 - не меньше, потому что при больших объемах данных gnuplot рисует не все графики или вообще ничего не рисует)." +
		make_paragraph() +
		L"Я не до конца разобрался в логике работы библиотеки matplot, поэтому не смог для каждого изображения добавить информацию о том, какого цвета какой график:" +
		make_paragraph() +
		L"Для k = 1 - голубой график, для k = 0.5 - красный, для k = 0.25 - желтый и для k = 0.125 - фиолетовый." +
		make_paragraph() +
		L"Для лучшего масштаба и меньшей потери данных t/n было умножено на e+05 во время вычислений." +
		make_paragraph() +
		L"Слева и справа векторы вычисленных значений t/n были обрезаны на 10% от их длины." +
		make_paragraph() +
		L"Тесты проводились отдельно для каждого графика: input_1, input_2, output_1, output_2." +
		make_paragraph() +
		L"Результаты экспериментов приведены ниже." +
		make_paragraph() +
		make_heading(L"О графиках :") +
		L"Input_1. На этом графике мы видим, что чем больше отличаются данные, тем хуже первая программа справляется с вводом данных. Также обратите внимание, что наш график не выстраивается в линию: отношение t / n стремится к нулю по мере увеличения аргумента n." +
		make_paragraph() +
		push_png(names[0]) +
		make_paragraph() +
		L"Input_2. На этом графике показаны очень странные линии. Следовательно, трудно судить о влиянии коэффициента k на ввод данных второго решения. Хотя в среднем его скорость превышает первое решение." +
		make_paragraph() +
		push_png(names[1]) +
		make_paragraph() +
		L"Проанализировав графики, можно отметить, что второе решение справляется со своей задачей более стабильно и быстрее." +
		make_paragraph() +
		L"Output_1. Время обработки данных первого решения быстро стремится к нулю с увеличением n." +
		make_paragraph() +
		push_png(names[2]) +
		make_paragraph() +
		L"Output_2. Мы можем заметить, насколько велико значение отношения t/n. Это говорит о том, что скорость обработки данных для второго решения очень низкая. Первое решение превосходит второе местами в сотни раз." +
		make_paragraph() +
		push_png(names[3]) +
		make_paragraph() +
		L"Если сравнить скорость обработки данных обоих вариантов, то первое решение выигрывает безоговорочно: в некоторых местах оно выигрывает у второго в сотни раз. Итог: хотя второе решение выигрывает в скорости ввода информации, но это не так существенно, как полное поражение в скорости обработки данных. Наш победитель: первое решение." +
		make_paragraph() +
		make_paragraph();

	const wchar_t* str = mainTEXT.c_str();
	std::ofstream fout; //making a doc
	fout.open("results_rus.md");
	fout << ConvertToUTF8(str);
	fout.close();
	delete str;
}

/*fout << make_link("Мой репозиторий", "https://github.com/K-Grachev-2106756/grachev_k_y") <<
		make_paragraph() <<
		make_heading("Вступление") <<
		"!!!Результаты могут быть воспроизведены." <<
		make_paragraph() <<
		"Тесты проводились для каждого значения k для каждого значения n 10 раз. Выходные данные представляют собой средние значения t/n." <<
		make_paragraph() <<
		"На рисунках мы можем видеть графики зависимости t/n от n с изменяющимся коэффициентом k = m/M"
		"(k = 1, 0,5, 0,25, 0,125 - не меньше, потому что при больших объемах данных gnuplot рисует не все графики или вообще ничего не рисует)." <<
		make_paragraph() <<
		"Я не доконца разобрался в логике работы библиотеки matplot, поэтому не смог для каждого изображения добавить информацию о том, какого цвета какой график:"<<
		make_paragraph()<<
		"Для k = 1 - голубой график, для k = 0.5 - красный, для k = 0.25 - желтый и для k = 0.125 - фиолетовый."<<
		make_paragraph()<<
		"Для лучшего масштаба и меньшей потери данных t/n было умножено на e+05 во время вычислений." <<
		make_paragraph() <<
		"Слева и справа векторы вычисленных значений t/n были обрезаны на 10% от их длины." <<
		make_paragraph() <<
		"Тесты проводились отдельно для каждого графика: input_1, input_2, output_1, output_2." <<
		make_paragraph() <<
		"Результаты экспериментов приведены ниже." <<
		make_paragraph() <<
		make_heading("О графиках :") <<
		"Input_1. На этом графике мы видим, что чем больше отличаются данные, тем хуже первая программа справляется с вводом данных. Также обратите внимание, что наш график не выстраивается в линию: отношение t / n стремится к нулю по мере увеличения аргумента n." <<
		make_paragraph() <<
		push_png(names[0]) <<
		make_paragraph() <<
		"Input_2. На этом графике показаны очень странные линии. Следовательно, трудно судить о влиянии коэффициента k на ввод данных второго решения. Хотя в среднем его скорость превышает первое решение." <<
		make_paragraph() <<
		push_png(names[1]) <<
		make_paragraph() <<
		"Проанализировав графики, можно отметить, что второе решение справляется со своей задачей более стабильно и быстрее." <<
		make_paragraph() <<
		"Output_1. Время обработки данных первого решения быстро стремится к нулю с увеличением n." <<
		make_paragraph() <<
		push_png(names[2]) <<
		make_paragraph() <<
		"Output_2. Мы можем заметить, насколько велико значение отношения t/n. Это говорит о том, что скорость обработки данных для второго решения очень низкая. Первое решение превосходит второе местами в сотни раз." <<
		make_paragraph() <<
		push_png(names[3]) <<
		make_paragraph() <<
		"Если сравнить скорость обработки данных обоих вариантов, то первое решение выигрывает безоговорочно: в некоторых местах оно выигрывает у второго в сотни раз. Итог: хотя второе решение выигрывает в скорости ввода информации, но это не так существенно, как полное поражение в скорости обработки данных. Наш победитель: первое решение." <<
		make_paragraph() <<
		make_paragraph();*/

//void make_md_eng(std::vector<std::string> names) {
//	std::ofstream fout; //making a doc
//	fout.open("results_eng.md");
//	fout << make_link("my repository", "https://github.com/K-Grachev-2106756/grachev_k_y") <<
//		make_paragraph() <<
//		make_heading("Introduction") <<
//		"!!!The results can be reproduced." <<
//		make_paragraph() <<
//		"The tests were run for each value of k for each value of n 10 times. The output data are the average values of t/n." <<
//		make_paragraph() <<
//		"In the pictures we can see graphs of the dependence of t/n on n with a changing coefficient k = m/ M"
//		"(k = 1, 0.5, 0.25, 0.125 - no less, because with large amounts of data, gnuplot does not draw all graphs or does not draw anything)." <<
//		make_paragraph() <<
//		"I did not fully understand the logic of the matplot library, so I could not add information for each image about which color is which graph:" <<
//		make_paragraph() <<
//		"For k = 1 - blue graph, for k = 0.5 - red, for k = 0.25 - yellow and for k = 0.125 - purple." <<
//		make_paragraph() <<
//		"For better scale and less data loss, t/n was multiplied by e+05 during calculations." <<
//		make_paragraph() <<
//		"On the left and right, the vectors of the calculated t/n values were cut off by 10% of their length." <<
//		make_paragraph() <<
//		"The tests were run separately for each graph: input_1, input_2, output_1, output_2." <<
//		make_paragraph() <<
//		"The results of the experiments are given below" <<
//		make_paragraph() <<
//		make_heading("About graphics :") <<
//		"Input_1. In this graph, we can see that the more different the data, the worse the first program copes with data entry.Also note that our graph does not line up : the ratio t / n tends to zero as the argument n increases." <<
//		make_paragraph() <<
//		push_png(names[0]) <<
//		make_paragraph() <<
//		"Input_2.  This graph shows very strange lines. Therefore, it is difficult to judge the influence of the coefficient k for data entry of the second solution. Although on average, its speed exceeds the first solution." <<
//		make_paragraph() <<
//		push_png(names[1]) <<
//		make_paragraph() <<
//		"After analyzing the graphs, it can be noted that the second solution copes with its task more stably and faster." <<
//		make_paragraph() <<
//		"Output_1. The data processing time of the first solution quickly tends to zero with increasing n." <<
//		make_paragraph() <<
//		push_png(names[2]) <<
//		make_paragraph() <<
//		"Output_2. We can notice how high the value of the t/n ratio is. This suggests that the data processing speed for the second solution is very low. The first solution surpasses the second in places by hundreds of times." <<
//		make_paragraph() <<
//		push_png(names[3]) <<
//		make_paragraph() <<
//		"If we compare the data processing speed of both options, then the first solution wins unconditionally : in some places it wins the second one hundreds of times. Bottom line : although the second solution wins in the speed of information input, but it is not as significant as a total defeat in the speed of data processing. Our winner : the first decision." <<
//		make_paragraph() <<
//		make_paragraph();
//	fout.close();
//}


