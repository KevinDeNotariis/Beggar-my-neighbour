#pragma once

#include "Stat.h"

#include <boost/serialization/base_object.hpp>

class LocalStat : public Stat {
    std::pair<unsigned long long int, std::string>  computation_time;
public:
    void setCompTime(unsigned long long int, std::string);
    unsigned long long int getCompTime();

    std::string toString();

    friend class boost::serialization::access;

    template <class Archive> void serialize(Archive & ar, const unsigned int version){
        ar & boost::serialization::base_object<Stat>(*this);
        ar & computation_time;
    }
};