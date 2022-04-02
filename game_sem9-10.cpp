#include <iostream>
#include <string>
#include <random>

class Hero {
private:
	std::string name;
	int health;
	int strength;

public:
	Hero(const std::string& name, int health, const int strength): name(name), health(health), strength(strength) {

	}

	void strike(Hero& otherHero) {
		std::random_device dev;
    	std::mt19937 rng(dev());
    	std::uniform_int_distribution<std::mt19937::result_type> dist(0,otherHero.getStrength());
		int buff = dist(rng);
		if((otherHero.getHealth()-buff) > 0) {
			otherHero.setHealth((health-buff));
			std::cout << otherHero.getName() << " health is: " << otherHero.getHealth()<<std::endl;
		}
		else
			otherHero.setHealth(0);
	}

	void setHealth(int health) {
		this->health = health;
	}

	std::string getName() {
		return name;
	}

	int getHealth() {
		return this->health;
	}

	int getStrength() {
		return this->strength;
	}

	~Hero(){
		std::cout<<"Hero "<<name<<" dead"<<std::endl;
	}

};

int main() {
	Hero* first = new Hero("Elf", 100, 5);
	Hero* second = new Hero("Orc", 70, 3);

	for(;;) {
		std::cout<< first->getName() << " strikes!"<<std::endl;
		first->strike(*second);
		if(second->getHealth() == 0) {
 			delete second;
 			break;
		}
		std::cout<< second->getName() << " strikes!"<<std::endl;
		second->strike(*first);
		if(first->getHealth() == 0) {
 			delete first;
 			break;
		}
	}

	return 0;
}
