#ifndef _OEPARTICLE_FIRE_EFFECT_H_
#define _OEPARTICLE_FIRE_EFFECT_H_

#include <ParticleSystem/IParticleEffect.h>
#include <ParticleSystem/SimpleEmitter.h>

#include <Resources/ResourceManager.h>
namespace OpenEngine {
    namespace Effects {

using namespace ParticleSystem;
using namespace Resources;

class FireEffect : public IParticleEffect {
private:
    OpenEngine::ParticleSystem::ParticleSystem& system;
    SimpleEmitter* emitter;
public:
    typedef SimpleEmitter::TYPE TYPE;
    FireEffect(OpenEngine::ParticleSystem::ParticleSystem& system): system(system) {
        emitter = new SimpleEmitter(
                                    30,     //numParticles
                                    0.04,    //emitRate
                                    8.0,     //number 
                                    2.0,     //numberVar
                                    .8,      //life
                                    0.2,     //lifeVar
                                    2*OpenEngine::Math::PI,    //angle
                                    0.0,     //spin
                                    0.0,     //spinVar
                                    10.0,    //speed
                                    1.0      //speedVar
                                    );
        // hack: create the particles
        emitter->Handle(ParticleEventArg(system, 0));
        system.ProcessEvent().Attach(*emitter);
        
        LinearValueModifier<TYPE,Vector<4,float> >& colormod = emitter->GetColorModifier();
        LinearValueModifier<TYPE,float>&  sizem = emitter->GetSizeModifier();

        // color modifier
        colormod.AddValue( .9, Vector<4,float>(0.1, 0.01, .01, .4)); // blackish
        colormod.AddValue( .7, Vector<4,float>( .7,  0.3,  .1, .6)); // redish
        colormod.AddValue( .6, Vector<4,float>( .9, 0.75,  .2, .7)); // orangeish
        colormod.AddValue( .0, Vector<4,float>(0.1,  0.1,  .3, .1)); // blueish
        
        // size variations 
        sizem.AddValue(1.0, 30); 
        // sizem.AddValue(.65, 7);
        // sizem.AddValue( .18, 6);    
        sizem.AddValue( .0, 20);    
        
        ITexture2DPtr tex1 = 
            // ResourceManager<ITexture2D>::Create("Smoke/smoke01.tga");
            // ResourceManager<ITexture2D>::Create("fire.jpg");
            //ResourceManager<ITexture2D>::Create("RealFlame_02.png");
            ResourceManager<ITexture2D>::Create("star.jpg");
        emitter->SetTexture(tex1);
    }

~FireEffect() {
    system.ProcessEvent().Detach(*emitter);
    delete emitter;
}

void SetActive(bool active) {
    emitter->SetActive(active);
}

bool GetActive() {
    return emitter->GetActive();
}

void Reset() {
    emitter->Reset();
}

ParticleCollection<TYPE>* GetParticles() { return emitter->GetParticles(); }

};

}
}
#endif
