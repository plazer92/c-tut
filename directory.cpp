
#include <filesystem>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>


namespace fs = std::filesystem;

class Observer
{

public:
	
	std::string path;

	Observer(std::string path):path(path){}

	~Observer()
	{
		if(fs::exists(path))	
			for(fs::directory_entry const & item : fs::directory_iterator(path))
			{
				std::cout<<"name: "<<item<<" ";
				std::cout<<"time: "<<(to_time_t(item.last_write_time()))<<" ";
				
				switch(item.status().type())
    			{
        			case fs::file_type::none: std::cout << " has `not-evaluated-yet` type"; break;
        			case fs::file_type::not_found: std::cout << " does not exist"; break;
        			case fs::file_type::regular: std::cout << " is a regular file"; break;
        			case fs::file_type::directory: std::cout << " is a directory"; break;
        			case fs::file_type::symlink: std::cout << " is a symlink"; break;
        			case fs::file_type::block: std::cout << " is a block device"; break;
        			case fs::file_type::character: std::cout << " is a character device"; break;
        			case fs::file_type::fifo: std::cout << " is a named IPC pipe"; break;
        			case fs::file_type::socket: std::cout << " is a named IPC socket"; break;
        			case fs::file_type::unknown: std::cout << " has `unknown` type"; break;
        			default: std::cout << " has `implementation-defined` type"; break;
    			}
				std::cout<<"\n";
			}
		else
			std::cout<<"wrong path\n";	

	}

	

private:

	template <typename TP> 
	std::time_t to_time_t(TP tp)
	{
    	using namespace std::chrono;
    	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
    	return system_clock::to_time_t(sctp);
	}

};


int main(int argc, char **argv)
{

	Observer o("/home/nikolay/Desktop");
}