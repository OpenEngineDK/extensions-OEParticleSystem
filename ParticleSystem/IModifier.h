#ifndef _INTERFACE_PARTICLE_MODIFIER_H_
#define _INTERFACE_PARTICLE_MODIFIER_H_

namespace OpenEngine {
namespace ParticleSystem {

// forward declaration
template <class T> class ParticleGroup;

template <class T> class IModifier {
public:
    virtual void Process(float deltaTime, float percent, 
			 ParticleGroup<T>* particleGroup) = 0;
    virtual ~IModifier() {}
};

} //NS ParticleSystem
} //NS OpenEngine

#endif

