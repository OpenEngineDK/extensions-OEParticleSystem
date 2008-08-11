#ifndef _PARTICLE_GROUP_INTERFACE_H_
#define _PARTICLE_GROUP_INTERFACE_H_

namespace OpenEngine {
namespace ParticleSystem {

class IParticleGroup {
public:
    virtual void Process(const float deltaTime, const float percent) = 0;
    virtual ~IParticleGroup() {}
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
