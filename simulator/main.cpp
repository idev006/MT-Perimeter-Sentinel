#include "mps/node_core.hpp"
#include "mps/queue.hpp"
#include <iostream>
#include <vector>
using namespace mps;
struct Tx: ITransport{bool up=false;std::vector<Event> sent;bool available()const override{return up;}bool send(const Event&e)override{if(!up)return false;sent.push_back(e);return true;}};
int main(){Tx t;BoundedQueue q(64);NodeCore n(t,q);for(int i=0;i<16;++i)n.submit(Event{"evt"+std::to_string(i),"N"+std::to_string(i+1),static_cast<unsigned long long>(i+1),Priority::P0,"INTRUSION",i});std::cout<<"pending_before="<<q.size()<<"\n";t.up=true;auto r=n.replay();std::cout<<"replayed="<<r<<" pending_after="<<q.size()<<" delivered="<<t.sent.size()<<"\n";return(q.size()==0&&t.sent.size()==16)?0:1;}
