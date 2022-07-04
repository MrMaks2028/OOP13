#include <iostream>
#include <thread> //библиотека потоков
#include <chrono>
#include <vector>
#include <string_view>
#include <mutex>

//многопоточность в приложениях

//управляющий поток
//атомарные операции
//гонки данных

//сопроцессы - равноправная группа процессов, взаимодействующая 
//между собой операторами явного переключения управления.

//Векторизованные вычисления -  вид распараллеливания программы, 
//при котором однопоточные приложения, выполняющие одну операцию
//в каждый момент времени, модифицируются для выполнения нескольких 
//однотипных операций одновременно.



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

	this_thread::get_id(); //возвращает дескриптор потока / ID потока
	this_thread::sleep_for(milliseconds(10)); // Блокирует выполнение текущего потока на какое то время
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
}//this_thread::sleep_until(); // Ожидание переданного какого-либо системного события