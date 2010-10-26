#ifndef _OEPARTICLE_SIMPLE_EMITTER_H_
#define _OEPARTICLE_SIMPLE_EMITTER_H_

// base particle system
#include <ParticleSystem/ParticleSystem.h>
#include <ParticleSystem/ParticleCollection.h>

// particle types
#include <ParticleSystem/Particles/IParticle.h>
#include <ParticleSystem/Particles/Position.h>
#include <ParticleSystem/Particles/Life.h>
#include <ParticleSystem/Particles/Color.h>
#include <ParticleSystem/Particles/Size.h>
#include <ParticleSystem/Particles/Texture.h>
#include <ParticleSystem/Particles/Forces.h>
#include <ParticleSystem/Particles/Velocity.h>

// predefined modifiers
#include <ParticleSystem/StaticForceModifier.h>
#include <ParticleSystem/SizeModifier.h>
#include <ParticleSystem/LifespanModifier.h>
#include <ParticleSystem/EulerModifier.h>
// #include <ParticleSystem/TextureRotationModifier.h>
#include <ParticleSystem/LinearValueModifier.h>

// predefined initializers
#include <ParticleSystem/RandomTextureInitializer.h>

#include <Math/RandomGenerator.h>
#include <Scene/TransformationNode.h>
#include <ParticleSystem/Particles/RenderParticle.h>

#include <Core/IListener.h>
// #include <Utils/PropertyTree.h>

namespace OpenEngine {
namespace ParticleSystem {

using Scene::TransformationNode;
// using Utils::PropertyTree;
    
class SimpleEmitter: public IListener<ParticleEventArg> {
public:
    typedef Forces < Life < Velocity < RenderParticle > > >  TYPE;
    ParticleCollection<TYPE>* GetParticles() { return particles; }
private:
    unsigned int totalEmits;
protected:
    OpenEngine::ParticleSystem::ParticleSystem& system;
    unsigned int numParticles;
    ParticleCollection<TYPE>* particles;
    // emit attributes
    // float number;
    // float numberVar;

    float life;
    float lifeVar;
    
    // angle is the angular deviation from the direction of
    // the velocity
    float angle;
    
    float spin;
    float spinVar;
    
    float speed;
    float speedVar;

    float size;
    float sizeVar;

    float emitdt;
    float emitRate;

    ITexture2DPtr tex;

    bool active;

    //modifiers
    EulerModifier<TYPE> euler;
    StaticForceModifier<TYPE> antigravity;
    LinearValueModifier<TYPE,Vector<4,float> > colormod;
    LinearValueModifier<TYPE,float> sizem;
    LifespanModifier<TYPE> lifemod;
    RandomGenerator randomgen;
    TransformationNode* t;
    // PropertyTree* ptree;

    // void LoadPropertyTree() {
    //     if (ptree == NULL) return;
    // }
public:
    // SimpleEmitter(PropertyTree* ptree): ptree(ptree) {
    //     LoadPropertyTree();
    // }

    SimpleEmitter(OpenEngine::ParticleSystem::ParticleSystem& system,
                  unsigned int numParticles,
                  float emitRate,
                  // float number, float numberVar,
                  float life, float lifeVar,
                  float angle, 
                  float spin, float spinVar,
                  float speed, float speedVar,
                  float size, float sizeVar):
        totalEmits(0),
        system(system),
        numParticles(numParticles),
        particles(system.CreateParticles<TYPE>(numParticles)),
        // number(number), numberVar(numberVar),
        life(life), lifeVar(lifeVar),
        angle(angle),
        spin(spin), spinVar(spinVar),
        speed(speed), speedVar(speedVar),
        size(size), sizeVar(sizeVar),
        emitdt(0.0),
        emitRate(emitRate),
        active(true),
        antigravity(Vector<3,float>()),
        t(NULL)
        // ptree(NULL)
    {
        randomgen.SeedWithTime();
    }
    
    ~SimpleEmitter() {
        delete particles;
    }
    
    void Handle(ParticleEventArg arg) {
        // todo: maybe an initialize event would be better.
        // if (particles == NULL) 
        //     particles = arg.particleSystem.CreateParticles<TYPE>(numParticles);

        // only emit particles if we are active
        if (active) {
            // fixed emit rate
            emitdt += arg.dt;
            while (emitdt > emitRate) {
                emitdt -= emitRate;
                totalEmits += Emit();
            }
        }

        // always update live particles
        for (particles->iterator.Reset(); 
             particles->iterator.HasNext(); 
             particles->iterator.Next()) {
            TYPE& particle = particles->iterator.Element();
        
            antigravity.Process(arg.dt, particle);
            euler.Process(arg.dt, particle);
            sizem.Process(arg.dt, particle, particle.size);
            colormod.Process(arg.dt, particle, particle.color);
            lifemod.Process(arg.dt, particle);
        
            if (particle.life >= particle.maxlife)
                particles->iterator.Delete();
        }
    }

    inline float RandomAttribute(float base, float variance) {
        return base + randomgen.UniformFloat(-1.0,1.0) * variance;
    }

    unsigned int GetTotalEmits() {
        return totalEmits;
    }

    unsigned int inline Emit() {
        Vector<3,float> position;
        Quaternion<float> direction;
        if (t)
            t->GetAccumulatedTransformations(&position, &direction);    

        // unsigned int emits = min(unsigned(round(RandomAttribute(number, numberVar))),
        //                          particles->GetSize()-particles->GetActiveParticles());
        unsigned int emits = fmin(1.0,
                                 particles->GetSize()-particles->GetActiveParticles());
        
        //initialize particles
        for (unsigned int i = 0; i < emits; i++) {
            TYPE& particle = particles->NewParticle();
        
            // position based on transformation hierarchy (point emission)
            particle.position = position;
        
            particle.life = 0;
            particle.maxlife = RandomAttribute(life, lifeVar);
            particle.rotation = 0;
            particle.spin = RandomAttribute(spin, spinVar);
            particle.size = RandomAttribute(size, sizeVar);

            // texture
            particle.texture = tex;
            particle.rotation = 0;
            particle.spin = 0;
    
            // random direction
            float r = randomgen.UniformFloat(-1.0,1.0)*angle;
            float p = randomgen.UniformFloat(-1.0,1.0)*angle;
            float y = randomgen.UniformFloat(-1.0,1.0)*angle;
            Quaternion<float> q(r,p, y);
            q.Normalize();
    
            // set velocity and forces for use with euler integration
            particle.velocity = q.RotateVector(direction.RotateVector(Vector<3,float>(0.0,-1.0,0.0))
                                               *RandomAttribute(speed,speedVar));
            particle.forces = Vector<3,float>(0.0,0.0,0.0);
        }
        return emits;
    }

    void SetActive(bool active) {
        this->active = active;
        if (!active) emitdt = 0;
    }

    bool GetActive() {
        return active;
    }

    void Reset() {
        totalEmits = 0;
        emitdt = 0.0;
    }

    void SetTexture(ITexture2DPtr texr) {
#if OE_SAFE
        if (texr.get() == NULL) throw new Exception("SimpleEmitter got NULL texture"); 
#endif
        tex = texr;
    }

    TransformationNode* GetTransformationNode() {
        return t;
    }

    void SetTransformationNode(TransformationNode* node) {
        t = node;
    }

    LinearValueModifier<TYPE,Vector<4,float> >& GetColorModifier() { return colormod; }
    LinearValueModifier<TYPE,float>&  GetSizeModifier() { return sizem;}

    // Edit
    void SetLife(float l) { life = l; }
    float GetLife() { return life; }

    void SetLifeVar(float l) { lifeVar = l; }
    float GetLifeVar() { return lifeVar; }

    void SetSpeed(float l) { speed = l; }
    float GetSpeed() { return speed; }

    void SetSpeedVar(float l) { speedVar = l; }
    float GetSpeedVar() { return speedVar; }

    void SetGravity(Vector<3,float> l) { antigravity.force = l; }
    Vector<3,float> GetGravity() { return antigravity.force; }

    void SetNumParticles(unsigned int numParticles) {
        this->numParticles = numParticles;
        system.ResizeParticles(&particles, numParticles);
    }

    unsigned int GetNumParticles() {
        return numParticles;
    }

    void SetEmitInterval(float i) {
        emitRate = i;
    }

    float GetEmitInterval(){
        return emitRate;
    }

    void SetAngle(float angle) {
        this->angle = angle;
    }

    float GetAngle(){
        return angle;
    }

    void SetSize(float size) {
        this->size = size;
    }

    float GetSize(){
        return size;
    }

    void SetSizeVar(float size) {
        this->sizeVar = size;
    }

    float GetSizeVar(){
        return sizeVar;
    }

};

}
}
#endif
