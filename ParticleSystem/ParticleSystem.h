#ifndef _PARTICLE_SYSTEM_MANAGER_H_
#define _PARTICLE_SYSTEM_MANAGER_H_

#include <ParticleSystem/ParticleCollection.h>
#include <Core/IModule.h>
#include <Core/Event.h>
#include <Core/IListener.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace ParticleSystem {

using OpenEngine::Core::IModule;
using OpenEngine::Core::Event;
using OpenEngine::Core::InitializeEventArg;
using OpenEngine::Core::ProcessEventArg;
using OpenEngine::Core::DeinitializeEventArg;
using OpenEngine::Core::IListener;

class ParticleSystem;

// the particle system event
struct ParticleEventArg {
    ParticleSystem& particleSystem;
    float dt;
ParticleEventArg(ParticleSystem& particleSystem, float dt): 
    particleSystem(particleSystem), dt(dt) {}
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
        ParticleEventArg parg(*this, (arg.approx/1000000.0));
//         logger.info << "approx: " << arg.approx << logger.end;
//         logger.info << "dt: " << parg.dt << logger.end;
        process.Notify(parg);
 
    }

    void Handle(DeinitializeEventArg arg) {
    }

};

class ParticleSystemTimer : public IListener<ProcessEventArg> {
    unsigned int time;
    const unsigned int interval;
    ParticleSystem& particleSystem;
public:
    ParticleSystemTimer(ParticleSystem& particleSystem, const unsigned int interval) : 
        time(0), 
        interval(interval),
        particleSystem(particleSystem) {
    }
    ParticleSystemTimer(ParticleSystem& particleSystem) : 
        time(0), 
        interval(30000),
        particleSystem(particleSystem) {
    }
    virtual void Handle(ProcessEventArg arg) {
        // call the particle systems with fixed time intervals
        time += arg.approx;

        //logger.info << "t is " << t << logger.end;
        while (time > interval) {
            particleSystem.Handle(arg);
            time -= interval;
        }
    }
};


} //NS ParticleSystem
} //NS OpenEngine

#endif
