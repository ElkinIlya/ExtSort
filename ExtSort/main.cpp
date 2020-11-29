#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <string>

int file_size = 1000;

void mergeTwoArrays(std::string f1_name,
					std::string f2_name,
					std::string output_name)
{

	std::ifstream f1(f1_name); //input
	std::ifstream f2(f2_name);

	std::ofstream f(output_name); //output

	int last1, last2;
	last1 = last2 = -1;

	while (!f1.eof() || !f2.eof()) {
		if (!f1.eof() && last1 == -1) {
			f1 >> last1;
		}
		if (!f2.eof() && last2 == -1) {

			f2 >> last2;
		}
		if (last1 == -1) {
			f << last2 << " ";
			last2 = -1;
		}
		else {
			if (last2 == -1) {
				f << last1 << " ";
				last1 = -1;
			}
			else {
				if (last1 < last2) {
					f << last1 << " ";
					last1 = -1;
				}
				else {
					f << last2 << " ";
					last2 = -1;
				}
			}
		}
	}
}

void merge_k_arrays(std::vector<std::string> files, std::string output_name) {
	for (int i = 0; i < files.size() - 1; ++i) {
		mergeTwoArrays(files[i], files[i + 1], "tmp.txt");
		std::ifstream fin("tmp.txt");
		std::ofstream fout(files[i + 1]);
		while (!fin.eof()) {
			int x;
			fin >> x;
			fout << x << " ";
		}
	}

	std::ifstream fin(files.back());
	std::ofstream fout(output_name);
	while (!fin.eof()) {
		int x;
		fin >> x;
		fout << x << " ";
	}
}

void sort_file(std::string file_name) {
	std::vector<int> a;
	std::ifstream fin(file_name);
	while (!fin.eof()) {
		int x;
		fin >> x;
		a.push_back(x);
	}
	sort(a.begin(), a.end());
	fin.close();
	std::ofstream fout(file_name);
	for (int e : a) fout << e << " ";
	fout.close();
}

int main() {
	std::vector<std::string> files;
	std::ifstream fin("input.txt");
	int cnt = 0;
	int num_of_files = 0;
	std::ofstream fout;
	while (!fin.eof()) {
		if (cnt == 0) {
			if(fout.is_open())
				fout.close();
			files.push_back("f_" + std::to_string(cnt) + ".txt");
			fout.open(files.back());
		}
		int x;
		fin >> x;
		fout << x << " ";
		cnt = (cnt++) % file_size;
	}
	fout.close();
	for (auto e : files) sort_file(e);
	merge_k_arrays(files, "output.txt");
	for (auto e : files) {
		std::remove(e.c_str());
	}
	return 0;
}