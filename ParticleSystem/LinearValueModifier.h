#ifndef _LINEAR_VALUE_MODIFIER_H_
#define _LINEAR_VALUE_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>

#include <list>
//#include <vector>

namespace OpenEngine {
namespace ParticleSystem {

using namespace std;

    
template <class T, class U> 
class LinearValueModifier { 
private:
    class TimeValuePair {
    public:
        float time;
        U value;
        TimeValuePair(): time(0) {} 
        TimeValuePair(float time, U value): 
            time(time), value(value) {} 
    };
    list<TimeValuePair > tvs;

public:
    LinearValueModifier() { }
    
    /* Make particle have color at certain time in the 
     * particles lifespan
     */
    void AddValue(float time, U value) {
        TimeValuePair tv;
        tv.time = time;
        tv.value = value;
        
        for (typename list<TimeValuePair>::iterator itr = tvs.begin(); 
             itr != tvs.end(); 
             itr++) {
            
            if ((*itr).time > time) {
                tvs.insert(itr, tv);
                return;
            }
        }
        tvs.push_back(tv);
    }
    
    inline void Process(float dt, T& particle, U& val) {
        float time = particle.life / particle.maxlife;
        if (tvs.empty() || time > tvs.back().time) 
            return;

        TimeValuePair tvnext;
        TimeValuePair tvbefore;
        for (typename list<TimeValuePair>::iterator itr = tvs.begin(); 
             itr != tvs.end(); 
             itr++) 
            {
                tvnext = *itr;
                if (tvnext.time > time)
                    break;
                tvbefore = tvnext;
            }
        U dif = (tvnext.value - tvbefore.value);
        val = tvbefore.value + dif*((time-tvbefore.time)/(tvnext.time-tvbefore.time));
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
