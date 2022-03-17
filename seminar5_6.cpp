#include <chrono>
#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>

//Таймер для второй задачи
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

//Исследование изменения ёмкости вектора в первой задачи с помощью прямого добавления элементов и функции reserve
template <typename T>
class TestVector : std::vector<T>	
{	
	

public:	
	void memoryResearch(const std::string& s)
	{
		std::cout<<s<<"\n";
		std::cout<<"capacity: "<<this->capacity()<<"\n";
		std::cout<<"memory: "<<this->capacity()*sizeof(T)<<"\n";
		std::cout<<"____________________"<<"\n";
	}
	void push_back_r(T& value )
	{
		memoryResearch("before");
		this->push_back(value);
		memoryResearch("after");
	}
	void push_back_reserve()
	{
		memoryResearch("before");
		this->reserve(5);
		memoryResearch("after");
	}
};
////////////////////////////

int main(int argc, char ** argv)
{
	
	//Первая задача
	TestVector<int> v;
	TestVector<int> v_r;


	for(int i = 0; i<50; ++i)	
		v.push_back_r(i);
	//Ответ: изменяется как степени двойки

	std::cout<<"----USING METHOD RESERVE----"<<std::endl;

	v_r.push_back_reserve();
	//Ответ: изменяется так, как мы запросим

	//Конец первой задачи

	//Вторая задача
	std::vector<int> c1 = {48,50,29,56,-25,30,10,2,0,9,1};
	std::array<int, 11> c2 = {48,50,29,56,-25,30,10,2,0,9,1};
	std::deque<int> c3 = {48,50,29,56,-25,30,10,2,0,9,1};
	std::list<int> c41 = {48,50,29,56,-25,30,10,2,0,9,1};
	std::list<int> c42 = {48,50,29,56,-25,30,10,2,0,9,1};
	std::forward_list<int> c51 = {48,50,29,56,-25,30,10,2,0,9,1};
	std::forward_list<int> c52 = {48,50,29,56,-25,30,10,2,0,9,1};

	{
		Timer timer("vector");
		std::cout<<"ONLY STD::SORT"<<std::endl;
		std::sort(c1.begin(),c1.end());
		std::cout<<std::endl;
	}

	{
		Timer timer("array");
		std::cout<<"ONLY STD::SORT"<<std::endl;
		std::sort(c2.begin(),c2.end());
		std::cout<<std::endl;
	}

	{
		Timer timer("deque");
		std::cout<<"ONLY STD::SORT"<<std::endl;
		std::sort(c3.begin(),c3.end());
		std::cout<<std::endl;
	}

	{
		Timer timer("list");
		std::cout<<"OWN SORT"<<std::endl;
		c42.sort(std::less<int>());
		std::cout<<std::endl;
	}

	{
		Timer timer("forward_list");
		std::cout<<"OWN SORT"<<std::endl;
		c52.sort(std::less<int>());
		std::cout<<std::endl;
	}

	/* Таблица результатов:
		1. vector - 25
		2. array - 23
		3. deque - 25
		4. list - 38
		5. forward_list - 22

		Победитель: forward_list

	*/


	//Конец второй задачи

	return 0;
}