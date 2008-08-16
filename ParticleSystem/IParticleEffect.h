#ifndef _INTERFACE_PARTICLE_EFFECT_H_
#define _INTERFACE_PARTICLE_EFFECT_H_

#include <ParticleSystem/ParticleSystem.h>
#include <Core/IListener.h>

namespace OpenEngine {
    //forward declaration
    namespace Scene {
        class ISceneNode;
    }
namespace ParticleSystem {

using OpenEngine::Core::IListener;
using OpenEngine::Scene::ISceneNode;

class IParticleEffect: public virtual IListener<ParticleEventArg> {
public:
    virtual ~IParticleEffect() {}

    virtual ISceneNode* GetSceneNode() = 0;
};

} //NS ParticleSystem
} //NS OpenEngine

#endif

