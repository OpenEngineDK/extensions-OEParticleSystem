#ifndef _COLOR_MODIFIER_H_
#define _COLOR_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class ColorModifier { 
private:
public:
    ColorModifier() { }

    inline void Process(float deltaTime, T& particle) {
        float height = particle.position[1];
        float c = 1.0-(height/40.0);
        particle.color = Vector<4,float>(c,c/4.0,0.0,c*2.0);
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
