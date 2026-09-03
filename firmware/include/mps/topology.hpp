#pragma once
#include <cstdlib>
namespace mps {
class RingTopology{public: explicit RingTopology(int n):n_(n){} bool adjacent(int a,int b)const{int d=std::abs(a-b);return d==1||d==n_-1;} private:int n_;};
}
