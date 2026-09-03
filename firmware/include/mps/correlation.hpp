#pragma once
#include "topology.hpp"
#include <vector>
namespace mps {
enum class Direction{UNKNOWN,CLOCKWISE,COUNTER_CLOCKWISE};
class Correlator{public: explicit Correlator(RingTopology t):topo_(t){} Direction direction(const std::vector<int>& p)const{if(p.size()<2) return Direction::UNKNOWN; for(size_t i=1;i<p.size();++i) if(!topo_.adjacent(p[i-1],p[i])) return Direction::UNKNOWN; int cw=0,ccw=0; for(size_t i=1;i<p.size();++i){int a=p[i-1],b=p[i]; if((b==a+1)||(a==16&&b==1))++cw; else ++ccw;} return cw>ccw?Direction::CLOCKWISE:ccw>cw?Direction::COUNTER_CLOCKWISE:Direction::UNKNOWN;} private:RingTopology topo_;};
}
