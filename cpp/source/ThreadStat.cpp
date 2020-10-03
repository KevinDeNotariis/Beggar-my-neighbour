#include "../header/ThreadStat.h"

void ThreadStat::computeTimeMean() {
    for(auto& [num_of_threads, vector_of_times] : threadStat) {
        long double mean = 0;
        for(auto time : vector_of_times) {
            mean += time;
        }
        mean /= vector_of_times.size();
        timeMean.insert(std::pair(num_of_threads, mean));
    }
}

void ThreadStat::feedThreadStat(int num_of_threads, unsigned long long int comp_time) {
    if(threadStat.find(num_of_threads) == threadStat.end())
        threadStat.insert(std::pair(num_of_threads, std::vector<unsigned long long int>(1, comp_time)));
    else
        threadStat.find(num_of_threads)->second.push_back(comp_time);
}

std::string ThreadStat::toString() {
    std::string ret = "For " + std::to_string(num_of_games) + " games: \n" ;
    ret += "# of threads | computation time \n" ;
    for(auto& [num_of_threads, mean_time] : timeMean) {
        ret +="   " + std::to_string(num_of_threads) + "\t" + std::to_string(mean_time) + "\n";
    }
    return ret;
}
