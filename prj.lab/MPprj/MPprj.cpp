#include<MPprj/MPprj.h>

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


std::string make_paragraph() {
	return "<br/><br/>";
}

std::string push_png(std::string img) {
	return "![[" + img + ".png]]";
}

std::string make_heading(std::string name) {
	return "\n## " + name + "\n";
}

std::string make_link(std::string name, std::string link) {
	return "[" + name + "](" + link + ")";
}
