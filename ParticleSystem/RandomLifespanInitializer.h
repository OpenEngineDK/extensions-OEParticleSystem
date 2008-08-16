#ifndef _RANDOM_LIFESPAN_INITIALIZER_H_
#define _RANDOM_LIFESPAN_INITIALIZER_H_

//#include "IInitializer.h"
//#include "ParticleGroup.h"
#include <Core/Exceptions.h>


namespace OpenEngine {
namespace ParticleSystem {


template <class T>
class RandomLifespanInitializer {//: public IInitializer<T> {
private:
    float base, variance;
public:
    RandomLifespanInitializer(float base, float variance) : base(base), variance(variance) {
    }

    void Process(T* particle) {
        particle->lifespan = base + ((rand()/(float)RAND_MAX)*2 - 1.0) * variance;
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
