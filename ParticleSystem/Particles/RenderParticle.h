#ifndef _RENDER_PARTICLE_
#define _RENDER_PARTICLE_

#include <ParticleSystem/Particles/IParticle.h>
#include <ParticleSystem/Particles/Position.h>
#include <ParticleSystem/Particles/Color.h>
#include <ParticleSystem/Particles/Size.h>
#include <ParticleSystem/Particles/Texture.h>

namespace OpenEngine {
namespace ParticleSystem {

typedef Color < Texture < Size < Position < IParticle > > > >  RenderParticle;

}
}
#endif
