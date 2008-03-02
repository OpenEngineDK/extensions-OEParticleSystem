#ifndef _PARTICLE_SET_INTERFACE_H_
#define _PARTICLE_SET_INTERFACE_H_

namespace OpenEngine {
namespace ParticleSystem {

class IParticleSet {
public:
    virtual void Process(const float deltaTime, const float percent) = 0;
    virtual ~IParticleSet() {}
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
