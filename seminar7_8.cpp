#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>
#include <chrono>

//Таймер
class Timer
{

private:	
	std::chrono::steady_clock::time_point begin_time;
	const std::string name;

public:	
	Timer(const std::string& name): name(name)
	{
		begin_time = std::chrono::steady_clock::now();
	}
	~Timer()
	{
		std::chrono::steady_clock::time_point end_time 
						= std::chrono::steady_clock::now();
		
		std::chrono::microseconds duration = 
			std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time);
		
		std::cout<<"name: "<<name<<" time current: "<<duration.count()<<"\n";
	}

};
///////////////////////////

int main() {
	int N = 400;

	//Random number generation

	std::vector<int> generator;
    std::vector<int>::iterator it;
    std::mt19937 eng{std::random_device{}()};

    for (int i=0;i<N;i++) {
        int q = std::uniform_int_distribution<int>{0, N}(eng);
 
        do {
            q = std::uniform_int_distribution<int>{0, N}(eng);
            it = std::find(generator.begin(), generator.end(), q);
        } while (it != generator.end());
 
        generator.push_back(q);
 
    }

    ///////////////////////////

	std::set<int> a;
    
	{
	Timer timer("total_time_set");

	for(int i = 0; i<generator.size(); ++i) 
		{
			a.insert(generator.at(i));
		}

		std::cout<<"______________"<<std::endl;
	}

	std::vector<int> b;

	{
	Timer timer("total_time_vector");

	for(int i = 0; i<generator.size(); ++i) 
		{
			b.push_back(generator.at(i));
		}

	std::sort(b.begin(), b.end());

		std::cout<<"______________"<<std::endl;
	}

	/*
	Результаты 5 тестов N=100:
	1. вектор - 67
	   множество - 176
	2. вектор - 91
	   множество - 171
	3. вектор - 63
	   множество - 181
	4. вектор - 82 
	   множество - 212
	5. вектор - 49 
	   множествo - 144

	Результаты 5 тестов N=200:
	1. вектор - 135
	   множество - 298
	2. вектор - 131
	   множество - 311
	3. вектор - 136
	   множество - 307
	4. вектор - 83
	   множество - 208
	5. вектор - 146
	   множествo -  314

	Результаты 5 тестов N=300:
	1. вектор - 134
	   множество - 245
	2. вектор - 158
	   множество - 343
	3. вектор - 213
	   множество - 459
	4. вектор - 217
	   множество - 433
	5. вектор - 159
	   множествo - 347

	Результаты 5 тестов N=400:
	1. вектор - 201
	   множество - 413
	2. вектор - 164
	   множество - 333
	3. вектор - 152
	   множество - 332
	4. вектор - 159
	   множество - 334
	5. вектор - 155
	   множествo - 366

	Ответ: константа находится в диапазоне между 2 и 3, вектор работает в данном случае быстрее
	*/
   
	return 0;
}
