#ifndef _SIZE_MODIFIER_H_
#define _SIZE_MODIFIER_H_

//#include <ParticleSystem/IModifier.h>
#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class SizeModifier { //: public IModifier<T> {
private:
    float timePassed;
public:
    SizeModifier() { timePassed = 0.0; }

    inline void Process(float deltaTime,T& particle) {
        particle.size += 0.2;
        float maxsize = 3;
        if (particle.size > maxsize)
            particle.size = maxsize;
                
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
