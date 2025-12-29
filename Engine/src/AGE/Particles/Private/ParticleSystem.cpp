#include "AGEpch.hpp"
#include "Particles/Public/ParticleSystem.h"
#include "RNG/Public/RNG.h"
#include "Render/Public/Renderer2D.h"



#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>


namespace AGE
{

	ParticleSystem::ParticleSystem(uint32_t MaxParticles)
		:m_PoolIndex(MaxParticles -1)
	{
		m_ParticlePool.resize(MaxParticles);
		SquirrelRNG::Init(m_PoolIndex);

	}

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

		m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
	}
}