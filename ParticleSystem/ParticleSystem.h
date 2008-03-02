#ifndef _PARTICLE_SYSTEM_MANAGER_H_
#define _PARTICLE_SYSTEM_MANAGER_H_

#include <vector>
#include <Core/IModule.h>
#include "IParticleSet.h"

namespace OpenEngine {
namespace ParticleSystem {

using OpenEngine::Core::IModule;
using std::vector;

class ParticleSystem : public IModule {
private:
    vector<IParticleSet*> particleSets;
public:
    ParticleSystem();
    ~ParticleSystem();

    void AddParticleSet(IParticleSet* particleSet);

    virtual void Initialize();
    virtual void Process(const float deltaTime, const float percent);
    virtual void Deinitialize();
    virtual bool IsTypeOf(const std::type_info& inf);
};

} //NS ParticleSystem
} //NS OpenEngine

#endif
