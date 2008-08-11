#include "ParticleSystem.h"

namespace OpenEngine {
namespace ParticleSystem {

ParticleSystem::ParticleSystem() {
}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::AddParticleGroup(IParticleGroup* particleGroup) {
    particleGroups.push_back(particleGroup);
}


void ParticleSystem::Process(const float deltaTime, const float percent) {
    vector<IParticleGroup*>::iterator itr;
    for (itr = particleGroups.begin(); itr != particleGroups.end(); itr++) {
        IParticleGroup* particleGroup = *itr;
        particleGroup->Process(deltaTime,percent);
    }
}

void ParticleSystem::Initialize() {
}

void ParticleSystem::Deinitialize() {
    // @todo remember to delete the objects in the list
    particleGroups.clear();
}

bool ParticleSystem::IsTypeOf(const std::type_info& inf) {
    return (typeid(ParticleSystem) == inf);
}

} //NS ParticleSystem
} //NS OpenEngine
