#include <iostream>
#include <thread> //���������� �������
#include <chrono>
#include <vector>
#include <string_view>
#include <mutex>

//��������������� � �����������

//����������� �����
//��������� ��������
//����� ������

//���������� - ������������ ������ ���������, ����������������� 
//����� ����� ����������� ������ ������������ ����������.

//��������������� ���������� -  ��� ����������������� ���������, 
//��� ������� ������������ ����������, ����������� ���� ��������
//� ������ ������ �������, �������������� ��� ���������� ���������� 
//���������� �������� ������������.



using namespace std;
using namespace chrono;

void Fill(vector<double>* cources) {
	for (size_t i = 0; i < cources->capacity(); i++) {
		this_thread::sleep_for(milliseconds(15));
		cources->emplace_back(15 + (double)::rand() / (1 + ::rand()));
	}
}

mutex mt;

void Print(vector<double>::iterator start, 
		vector<double>::iterator stop,
		string_view name) {
	while (start <= stop) {
		lock_guard lg(mt);
		cout << name;
		cout << "Value: ";
		cout << *start;
		cout << '\n';
		++start;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");

	this_thread::get_id(); //���������� ���������� ������ / ID ������
	this_thread::sleep_for(milliseconds(10)); // ��������� ���������� �������� ������ �� ����� �� �����
	vector<double> udsCource;
	udsCource.reserve(540);
	vector<double> euroCource;
	euroCource.reserve(540);
	vector<double> phoundCource;
	phoundCource.reserve(540);
	thread tr1(Fill, &udsCource);
	//Fill(&udsCource);
	thread tr2(Fill, &euroCource);
	//Fill(&euroCource);
	thread tr3(Fill, &phoundCource);
	//Fill(&phoundCource);
	tr1.join();
	thread tr4(Print, udsCource.begin(), udsCource.begin() + 100, "USD ");
	thread tr5(
		[&tr2, &euroCource]() {
			tr2.join();
			Print(euroCource.begin(), euroCource.begin() + 100, "Euro "); }
	);
	tr3.join();
	Print(phoundCource.begin(), phoundCource.begin() + 100, "Phound ");
	tr5.join();
	tr4.join();
	



	//tr4.detach();

	return 0;
}//this_thread::sleep_until(); // �������� ����������� ������-���� ���������� �������