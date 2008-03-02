#ifndef _INTERFACE_PARTICLE_MODIFIER_H_
#define _INTERFACE_PARTICLE_MODIFIER_H_

namespace OpenEngine {
namespace ParticleSystem {

template <class T> class ParticleSet; // forward decleration

template <class T>
class IModifier {
public:
    virtual void Process(float deltaTime, float percent, ParticleSet<T>* particleSet) = 0;
    virtual ~IModifier() {}
};

} //NS ParticleSystem
} //NS OpenEngine

#endif

