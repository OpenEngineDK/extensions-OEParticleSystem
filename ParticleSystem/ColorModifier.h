#ifndef _COLOR_MODIFIER_H_
#define _COLOR_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>
#include <Math/Vector.h>

#include <list>
#include <vector>

namespace OpenEngine {
namespace ParticleSystem {

using OpenEngine::Math::Vector;
using namespace std;

class TimeColorPair {
public:
    float time;
    Vector<4,float> color;
    TimeColorPair(): time(0) {} 
};

template <class T> class ColorModifier { 
private:
    list< TimeColorPair > tcs;

public:
    ColorModifier() { }
    
    /* Make particle have color at certain time in the 
     * particles lifespan
     */
    void AddColor(float time, Vector<4,float> color) {
        TimeColorPair tc;// = new TimeColorPair();
        tc.time = time;
        tc.color = color;
        
        ; 
        for (list< TimeColorPair >::iterator itr = tcs.begin(); 
             itr != tcs.end(); 
             itr++) {
            
            if ((*itr).time > time) {
                tcs.insert(itr, tc);
                return;
            }
        }
        tcs.push_back(tc);
    }
    
    inline void Process(float deltaTime, T& particle) {
        float time = particle.life / particle.maxlife;
        if (tcs.empty() || time >= tcs.back().time) 
            return;

        TimeColorPair tc;
        for (list< TimeColorPair >::iterator itr = tcs.begin(); 
             itr != tcs.end(); 
             itr++) 
            {
                tc = *itr;
                if (tc.time > time)
                    break;
            }
        Vector<4,float> dif = (tc.color - particle.color);
        dif.Normalize();
        particle.color += ((tc.time-time)/tc.time)*(dif);
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
