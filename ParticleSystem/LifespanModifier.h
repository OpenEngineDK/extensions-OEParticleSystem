#ifndef _LIFESPAN_MODIFIER_H_
#define _LIFESPAN_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class LifespanModifier {
private:
public:
    LifespanModifier() { }

    inline void Process(float deltaTime, ParticleIterator<T>& iterator) {
        T& particle = iterator.Element();
        particle.lifespan -= deltaTime;
        if (particle.lifespan <= 0) 
            iterator.Delete();
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
