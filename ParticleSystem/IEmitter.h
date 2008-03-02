#ifndef _INTERFACE_EMITTER_H_
#define _INTERFACE_EMITTER_H_

#include <Math/Vector.h>

namespace OpenEngine {
namespace ParticleSystem {

using OpenEngine::Math::Vector;

class IEmitter {
public:
    virtual Vector<3,float> GetParticlePosition() = 0;
    virtual ~IEmitter() {}
};

} //NS ParticleSystem
} //NS OpenEngine

#endif

