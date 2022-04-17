#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <cmath>
#include <future>
#include <mutex>



#include "Timer.hpp"
	

	  

std::vector<std::pair<int,int>> paginate(size_t size,size_t row_count){

	std::vector<std::pair<int,int>>list;
	
	size_t end = row_count;
	
	for(size_t start = 0; start<size;){
		
		list.push_back(std::pair<int,int>(start,std::min(end,size)));
		start = end;
		end += row_count;

	}




	return move(list);


}



class Points{

	private:
		size_t size;
		

		double *x_;
		double *y_;

		size_t count = 0;
		size_t in_circle_count = 0;

		std::mutex mutex;


	public:
		
		Points(size_t size):size(size){

			x_ = new double[size];
			y_ = new double[size];
		}

		~Points(){
			
			delete [] x_;
			delete [] y_;

		}

		void set_point(double x, double y){
			x_[count]= x;
			y_[count]= y;
			++count;
			
		}


		void m_thread_compute(size_t row_in_thread){

			
			std::vector<std::future<void>> future_vectors;
			
	
			std::vector<std::pair<int,int>> v = paginate(size,row_in_thread);
			for(int i =0;i<v.size();i++){

				future_vectors.push_back(std::async([=]()->void{

					belong_count_mth(v[i].first,v[i].second);
					
				}));
			}
			



		}

		
		void belong_count_mth(size_t index_start,size_t index_stop){
				
			size_t local_in_circle_count = 0;

			for(size_t i = index_start; i<index_stop; ++i)
				if(1 > std::sqrt(std::pow(x_[i],2)+std::pow(y_[i],2))){
					++local_in_circle_count;
				}
			
			std::lock_guard<std::mutex> guard(mutex);	
			in_circle_count+=local_in_circle_count;
		//	std::cout<<in_circle_count<<"  in thrads: "<<index_start<<"\n";
		}

		void belong_count(){

			

			for(size_t i = 0; i<size; ++i)
				if(1 > std::sqrt(std::pow(x_[i],2)+std::pow(y_[i],2)))
					++in_circle_count;
			std::cout<<in_circle_count<<"  in one\n";
		}



	
		double get_result(){

			double pi = 4*static_cast<double>(in_circle_count)/size;
			
			std::cout<<"pi : "<<pi<<'\n';

			in_circle_count = 0;

			return pi;
		}

};




int main (){

	size_t size = 10'000'000;

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());

	std::uniform_real_distribution<> distr_x(0.0, 1.0);
	std::uniform_real_distribution<> distr_y(0.0, 1.0);

	Points points(size);
{   Timer timer("fill array");
	for	(int i =0;i<size ;++i){
	
		points.set_point(distr_x(gen),distr_y(gen));
	
		
	}

 }	
 {
 	Timer timer("compute distance");
 	points.belong_count();
	points.get_result();
 }

  {
 	Timer timer("compute mth distance");
 	points.m_thread_compute(1'000'000);
 	points.get_result();
 }	

 	
	return 0;
}