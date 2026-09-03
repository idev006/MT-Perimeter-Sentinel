#pragma once
namespace mps { struct CoveragePolicy{static bool allow_disruptive_action(double projected,double minimum){return projected>=minimum;}}; }
