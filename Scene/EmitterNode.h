// Particle emitter node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _OE_EMITTER_NODE_H_
#define _OE_EMITTER_NODE_H_

#include <Scene/ISceneNode.h>

namespace OpenEngine {
    namespace ParticleSystem {
        class SimpleEmitter;
}
namespace Scene { 

using ParticleSystem::SimpleEmitter;

/**
 * Particle Emitter Node.
 *
 * Used to transform the position and direction of the emitter.
 *
 * @class EmitterNode EmitterNode.h Scene/EmitterNode.h
 */
class EmitterNode : public ISceneNode {
    OE_SCENE_NODE(EmitterNode, ISceneNode)
private:
    SimpleEmitter* emitter;
public:
    EmitterNode();
    EmitterNode(SimpleEmitter* emitter);
    ~EmitterNode();
    SimpleEmitter* GetEmitter();
};

} // NS Scene
} // NS OpenEngine

#endif // _OE_EMITTER_NODE_H_
