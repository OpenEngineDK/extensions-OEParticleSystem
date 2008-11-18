#ifndef _PARTICLE_SYSTEM_MANAGER_H_
#define _PARTICLE_SYSTEM_MANAGER_H_

#include <ParticleSystem/ParticleCollection.h>
#include <Core/IModule.h>
#include <Core/Event.h>
#include <Core/IListener.h>
#include <Utils/Timer.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace ParticleSystem {

using OpenEngine::Core::IModule;
using OpenEngine::Core::Event;
using OpenEngine::Core::InitializeEventArg;
using OpenEngine::Core::ProcessEventArg;
using OpenEngine::Core::DeinitializeEventArg;
using OpenEngine::Core::IListener;
using OpenEngine::Utils::Timer;

class ParticleSystem;

// the particle system event
struct ParticleEventArg {
    ParticleSystem& particleSystem;
    float dt;
ParticleEventArg(ParticleSystem& particleSystem, float dt): 
    particleSystem(particleSystem),dt(dt) {}
};

class ParticleSystem : public IModule {
private:
    Event<ParticleEventArg> process;
public:
    ParticleSystem() {};
    virtual ~ParticleSystem() {};


    //@todo Reference  count particlecollections
    template<class T> ParticleCollection<T>* CreateParticles(unsigned int size) {
        T* particles = new T[size];
        return new ParticleCollection<T>(particles, size);
    }

    Event<ParticleEventArg>& ProcessEvent() {
        return process;
    }

    void Handle(InitializeEventArg arg) {
    }

    void Handle(ProcessEventArg arg) {
        ParticleEventArg parg(*this, 50000/1000);
        process.Notify(parg);
 
    }

    void Handle(DeinitializeEventArg arg) {
    }

};

class ParticleSystemTimer : public IListener<ProcessEventArg> {
    Timer timer;
    ParticleSystem& particleSystem;
public:
    ParticleSystemTimer(ParticleSystem& particleSystem) : particleSystem(particleSystem) {
        timer.Start();
    }
    virtual void Handle(ProcessEventArg arg) {
        // call the particle systems with fixed time intervals
        unsigned int t = timer.GetElapsedIntervalsAndReset(50000);
        //logger.info << "t is " << t << logger.end;
        while (t--) particleSystem.Handle(arg);
    }
};


} //NS ParticleSystem
} //NS OpenEngine

#endif
