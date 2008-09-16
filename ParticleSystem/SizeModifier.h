#ifndef _SIZE_MODIFIER_H_
#define _SIZE_MODIFIER_H_

//#include <ParticleSystem/IModifier.h>
#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class SizeModifier { 
private:
    float maxsizevar;
public:
    SizeModifier(float maxsizevar): maxsizevar(maxsizevar) { }

    inline void Process(T& particle) {
        particle.size = particle.startsize + maxsizevar * particle.life / particle.maxlife;
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
