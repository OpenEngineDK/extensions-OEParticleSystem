// Particle emitter node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include <Scene/EmitterNode.h>
#include <Core/Exceptions.h>
#include <ParticleSystem/SimpleEmitter.h>

namespace OpenEngine {
    namespace Scene {

using ParticleSystem::SimpleEmitter;

/**
 * Default constructor to satisfy scene node requirements.
 * Calling this constructor will throw an exception.
 * @throws Core::Exception
 */
EmitterNode::EmitterNode() {
    throw Core::Exception("Unable to create a particle emitter node with no emitter.");
}

/** 
 * Create a particle emitter node.
 * @param emitter the particle emitter to insert into the scene.
 */
EmitterNode::EmitterNode(SimpleEmitter* emitter) {
    this->emitter = emitter;
}

EmitterNode::~EmitterNode() {
}

SimpleEmitter* EmitterNode::GetEmitter() {
    return emitter;
}

}
}
