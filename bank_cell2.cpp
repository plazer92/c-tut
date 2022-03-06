#include <iostream>
#include <memory>
#include <cstdlib>
#include <unistd.h>

int global_id =0;

struct BankCell
{
	
	BankCell(int ammount)
	{
		this->ammount = ammount;
		
	}
	~BankCell()
	{
		std::cout<<"everyone is dead now!\n";
	}

	int ammount; // RUSSIAN RUB admits only whole numbers

	void show_ammount()
	{
		std::cout<<"CELL: "<<ammount<<"\n";
	}
};

class Human
{
public:
	const std::string name;
	const int id;
	std::shared_ptr <BankCell> cell;
	bool is_alive = true;

public:

	Human(std::string&& name):name(name),id(global_id++){}

	void open_cell()
	{
		if(cell == nullptr && is_alive)
		{
			cell = std::make_shared<BankCell>(40000);
		}
	}
	void give_access(Human &user)
	{
		if(is_alive)
			user.cell = cell;
	}
	void die()
	{
		this->cell = nullptr;
		is_alive = false;
	}	  	
};

int main(int argc,char** argv)
{
	Human a("A"),b("B"),c("D");
	a.open_cell();
	
	a.give_access(b);
	b.give_access(c);
	std::cout<<b.cell->ammount<<"\n";
	a.die();
	b.die();

	sleep(1);
	std::cout<<"______________\n";
}
