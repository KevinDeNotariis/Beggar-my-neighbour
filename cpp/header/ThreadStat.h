#include <map>
#include <vector>
#include <string>

class ThreadStat {
public:
	int num_of_games;
	// [ (number_of_threads, comp_times: [..., ..., ...]), 
	//   (number_of_threads, comp_times: [..., ..., ...]), ... ] 
	std::map<int,std::vector<unsigned long long int>> threadStat;

	// [ (number_of_threads, mean_of_comp_times), ...]
	std::map<int, double> timeMean;

	void computeTimeMean();

	void feedThreadStat(int num_of_threads, unsigned long long int comp_time);

	std::string toString();
};