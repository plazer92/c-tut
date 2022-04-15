
#include <iostream>
#include <fstream>


class TextCreator
{	
	private:

		std::ofstream stream;
		int count;

	public:

		TextCreator(std::string path) : stream(path)
		{
		

			for(int i = 0 ; i<10; ++i)
			{
				for(int j = 0; j<15; ++j)
					stream<<static_cast<char>('A'+i);
				stream<<'\n';
			}

			stream.close();

			

		}

		void getLine(int n,char * buffer)
		{
			std::ifstream istream("test.txt");

			istream.seekg (0, std::ios::beg);
			std::string line;
			std::getline(istream,line);
			int length = line.size()+1;
			istream.seekg (0, std::ios::end);
			int count = istream.tellg()/length;
			std::cout<<count<<"\n";
			
			
			istream.seekg(length*n,std::ios::beg).read(buffer,length);
			

			 
		}


};

int main(int argc,char ** argv)
{
	TextCreator tc("test.txt");

	char buf[256];
	
	tc.getLine(2,buf);
	std::cout<<buf;
	

	return 0;
}