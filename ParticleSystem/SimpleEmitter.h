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

#include <Scene/SearchTool.h>
#include <Scene/EmitterNode.h>

#include <Utils/PropertyTree.h>

namespace OpenEngine {
namespace ParticleSystem {

using Scene::TransformationNode;
using Scene::EmitterNode;
using Scene::SearchTool;
using Utils::PropertyTree;
using Utils::PropertyTreeNode;
using Utils::PropertiesChangedEventArg;
    
class SimpleEmitter: public IListener<ParticleEventArg>
                   , public EmitterNode
                   , public IListener<PropertiesChangedEventArg> {
public:
    typedef Forces < Life < Velocity < RenderParticle > > >  TYPE;
    ParticleCollection<TYPE>* GetParticles() { return particles; }
private:
    unsigned int totalEmits;
    SearchTool st;
protected:
    OpenEngine::ParticleSystem::ParticleSystem& system;
    unsigned int numParticles;
    ParticleCollection<TYPE>* particles;
    // emit attributes

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
    StaticForceModifier<TYPE> gravity;
    LinearValueModifier<TYPE,Vector<4,float> > colormod;
    LinearValueModifier<TYPE,float> sizemod;
    LifespanModifier<TYPE> lifemod;
    RandomGenerator randomgen;
    PropertyTree* ptree;

    inline void LoadPropertyTree() {
        if (ptree == NULL) return;
        
        if (ptree->HaveNode("init")) {
            PropertyTreeNode init = ptree->GetNode("init");
            
            unsigned int count = init.GetPath("particles", 200);
            if (numParticles != count) SetNumParticles(count);
            
            SetAngle(init.Get("angle", 0.0));
            SetLife(init.Get("life", 1.0));
            SetLifeVar(init.Get("lifevar", 0.0));
            spin = init.Get("spin", 0.0);
            spinVar = init.Get("spinvar", 0.0);
            SetSpeed(init.Get("speed", 45.0));
            SetSpeedVar(init.Get("speedvar", 10.0));
            SetSize(init.Get("size", 4.0));
            SetSizeVar(init.Get("size", 0.0));
            SetEmitInterval(init.Get("emitrate", 0.001));
            SetGravity(init.Get("gravity", Vector<3,float>()));
        }

        if (ptree->HaveNode("color")) {
            PropertyTreeNode color = ptree->GetNode("color");
            colormod.Clear();
            for (unsigned int i = 0; i < color.GetSize(); ++i) {
                PropertyTreeNode entry = color.GetNode(i);
                if (entry.HaveNode("time") && entry.HaveNode("value")) {
                    colormod.AddValue(entry.Get("time", 0.0f), entry.Get("value", Vector<4,float>()));
                }
            }
        }

        if (ptree->HaveNode("size")) {
            PropertyTreeNode sz = ptree->GetNode("size");
            sizemod.Clear();
            for (unsigned int i = 0; i < sz.GetSize(); ++i) {
                PropertyTreeNode entry = sz.GetNode(i);
                if (entry.HaveNode("time") && entry.HaveNode("value")) {
                    sizemod.AddValue(entry.Get("time", 0.0f), entry.Get("value", 0.0));
                }
            }
        }
    }
public:
    SimpleEmitter(OpenEngine::ParticleSystem::ParticleSystem& system,
                  PropertyTree* ptree)
        : EmitterNode(this)
        , system(system) 
        , particles(system.CreateParticles<TYPE>(200))
        , ptree(ptree)
    {
        
        randomgen.SeedWithTime();
        ptree->Reload();
        LoadPropertyTree();
        ptree->PropertiesChangedEvent().Attach(*this);
    }

    SimpleEmitter(OpenEngine::ParticleSystem::ParticleSystem& system,
                  unsigned int numParticles,
                  float emitRate,
                  // float number, float numberVar,
                  float life, float lifeVar,
                  float angle, 
                  float spin, float spinVar,
                  float speed, float speedVar,
                  float size, float sizeVar):
        EmitterNode(this),
        totalEmits(0),
        system(system),
        numParticles(numParticles),
        particles(system.CreateParticles<TYPE>(numParticles)),
        life(life), lifeVar(lifeVar),
        angle(angle),
        spin(spin), spinVar(spinVar),
        speed(speed), speedVar(speedVar),
        size(size), sizeVar(sizeVar),
        emitdt(0.0),
        emitRate(emitRate),
        active(true),
        ptree(NULL)
    {
        randomgen.SeedWithTime();
    }
    
    ~SimpleEmitter() {
        delete particles;
    }
    
    void Handle(PropertiesChangedEventArg arg) {
        LoadPropertyTree();
    }

    void Handle(ParticleEventArg arg) {
        // todo: maybe an initialize event would be better.
        // if (particles == NULL) 
        //     particles = arg.particleSystem.CreateParticles<TYPE>(numParticles);

        // only emit particles if we are active
        if (active) {
            if (emitRate <= 0.0) return;
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
        
            gravity.Process(arg.dt, particle);
            euler.Process(arg.dt, particle);
            sizemod.Process(arg.dt, particle, particle.size);
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
        TransformationNode* t = st.AncestorTransformationNode(this, true);
        if (t) t->GetAccumulatedTransformations(&position, &direction);    

        if (particles->GetSize() == particles->GetActiveParticles()) return 0;
        // const unsigned int emits = 1;
        
        //initialize particles
        // for (unsigned int i = 0; i < emits; i++) {
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
    // }
        return 1;
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

    // void SetTransformationNode(TransformationNode* node) {
    //     t = node;
    // }

    LinearValueModifier<TYPE,Vector<4,float> >& GetColorModifier() { return colormod; }
    LinearValueModifier<TYPE,float>&  GetSizeModifier() { return sizemod;}

    // Edit
    void SetLife(float l) { life = l; }
    float GetLife() { return life; }

    void SetLifeVar(float l) { lifeVar = l; }
    float GetLifeVar() { return lifeVar; }

    void SetSpeed(float l) { speed = l; }
    float GetSpeed() { return speed; }

    void SetSpeedVar(float l) { speedVar = l; }
    float GetSpeedVar() { return speedVar; }

    void SetGravity(Vector<3,float> l) { gravity.force = l; }
    Vector<3,float> GetGravity() { return gravity.force; }

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
