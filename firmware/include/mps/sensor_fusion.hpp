#pragma once
#include <set>
#include <string>
#include <vector>
namespace mps {
struct Observation{std::string sensor_type; double confidence; long long at_ms;};
class SensorFusion{
 public:
  static double fuse(const std::vector<Observation>& obs,long long now,long long window_ms){
    std::set<std::string> types; double sum=0; int n=0;
    for(const auto&o:obs){if(now-o.at_ms>window_ms) continue; if(types.insert(o.sensor_type).second){sum+=o.confidence;++n;}}
    return n?sum/n:0.0;
  }
};
}
