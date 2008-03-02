#include "ParticleSystem.h"

namespace OpenEngine {
namespace ParticleSystem {

ParticleSystem::ParticleSystem() {
}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::AddParticleSet(IParticleSet* particleSet) {
    particleSets.push_back(particleSet);
}


void ParticleSystem::Process(const float deltaTime, const float percent) {
    vector<IParticleSet*>::iterator itr;
    for (itr = particleSets.begin(); itr != particleSets.end(); itr++) {
        IParticleSet* particleSet = *itr;
        particleSet->Process(deltaTime,percent);
    }
}

void ParticleSystem::Initialize() {

}

void ParticleSystem::Deinitialize() {
    // @todo remember to delete the objects in the list
    particleSets.clear();
}

bool ParticleSystem::IsTypeOf(const std::type_info& inf) {
    return (typeid(ParticleSystem) == inf);
}

} //NS ParticleSystem
} //NS OpenEngine
