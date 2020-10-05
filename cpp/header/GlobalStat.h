#pragma once

#include "Stat.h"
#include "LocalStat.h"

#include <boost/serialization/base_object.hpp>

class GlobalStat : public Stat {
public:

    void feed(LocalStat stat);

    std::string toString();

    // SERIALIZATION --------------------------------------

    friend class boost::serialization::access;

    template <class Archive> void serialize(Archive & ar, const unsigned int version){
        ar & boost::serialization::base_object<Stat>(*this);
    }
};