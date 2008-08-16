#ifndef _INTERFACE_PARTICLE_MODIFIER_H_
#define _INTERFACE_PARTICLE_MODIFIER_H_

#include <ParticleSystem/ParticleCollection.h>

namespace OpenEngine {
namespace ParticleSystem {

// forward declaration

template <class T> 
class IModifier {
public:
    virtual void Process(float deltaTime, 
                         ParticleIterator<T>& iterator) = 0;
    virtual ~IModifier() {}
};

} //NS ParticleSystem
} //NS OpenEngine

#endif

