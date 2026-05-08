#include "AGEpch.hpp"
#include "Particles/Public/ParticleSystem.h"
#include "RNG/Public/RNG.h"
#include "Render/Public/Renderer2D.h"



#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>


namespace AGE
{

	/**
 * @brief Constructs a ParticleSystem object with the specified maximum number of particles.
 * 
 * This constructor initializes the particle pool to the given size and sets up the random number generator for the indices.
 * The m_PoolIndex is initialized as MaxParticles - 1, ensuring that the first call to GetNextFreeParticle() will return 0.
 * @param MaxParticles The maximum number of particles that can be stored in the particle pool.
 */
ParticleSystem::ParticleSystem(uint32_t MaxParticles)
		:m_PoolIndex(MaxParticles -1)
	{
		m_ParticlePool.resize(MaxParticles);
		SquirrelRNG::Init(m_PoolIndex);

	}

	/**
 * @brief This function updates the state of each particle in the system over a given time step.
 *
 * The function iterates through all particles in the system and performs several operations on them based on their current state. 
 * If a particle is not active, it will be skipped. For active particles, if their life remaining is less than or equal to zero, they are deactivated. 
 * Otherwise, their lifespan is reduced by the time step and their position is updated by adding their velocity times the time step. The rotation of the particle remains unaffected in this case.
 *
 * @param ts The time step over which to update the particles.
 */
void ParticleSystem::OnUpdate(TimeStep ts)
	{
		for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active)
				continue;

			if (particle.LifeRemaining <= 0.0f)
			{
				particle.Active = false;
				continue;
			}

			particle.LifeRemaining -= ts;
			particle.Position += particle.Velocity * (float)ts;
			particle.Rotation += 0.01f * ts;
		}
	}

	"This function renders the particle system using a provided camera and transformation matrix."
void ParticleSystem::OnRender(const Camera& Camera, const Matrix4D& Transform)
	{
		Renderer2D::BeginScene(Camera, Transform);

		for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active)
				continue;

			// Fade away particles
			float life = particle.LifeRemaining / particle.LifeTime;
			Vector4 color = (Vector4)glm::lerp(Convert::ToGLM(particle.ColorEnd), Convert::ToGLM(particle.ColorBegin), life);
			//color.a = color.a * life;
			particle.TintColor = color;
			float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
			particle.Size = { size, size };
			//Renderer2D::DrawRotatedQuad(particle.Position, particle, particle.Rotation);
		}
		Renderer2D::EndScene();
	}

	/**
 * @brief Emit a new particle with the given properties.
 *
 * This function creates a new particle and initializes its properties based on the provided ParticleProps object. The position, rotation, velocity, color, lifetime, size of the particle are set according to the values in the ParticleProps object. 
 *
 * @param[in] particleProps Properties for the new particle.
 */
void ParticleSystem::Emit(const ParticleProps& particleProps)
	{
		Particle& particle = m_ParticlePool[m_PoolIndex];
		particle.Active = true;
		particle.Position = particleProps.Position;
		particle.Rotation = SquirrelRNG::RollRandomRotationFloat();

		// Velocity
		particle.Velocity = particleProps.Velocity;
		particle.Velocity[0] += particleProps.VelocityVariation[0] * (SquirrelRNG::RollRandomFloatInRange(1, 10) - 0.5f);
		particle.Velocity[1] += particleProps.VelocityVariation[1] * (SquirrelRNG::RollRandomFloatInRange(1, 10) - 0.5f);

		// Color
		particle.ColorBegin = particleProps.ColorBegin;
		particle.ColorEnd = particleProps.ColorEnd;

		particle.LifeTime = particleProps.LifeTime;
		particle.LifeRemaining = particleProps.LifeTime;
		particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (SquirrelRNG::RollRandomFloatZeroToOne() - 0.5f);
		particle.SizeEnd = particleProps.SizeEnd;

		m_PoolIndex = --m_PoolIndex % (uint32_t)m_ParticlePool.size();
	}
}