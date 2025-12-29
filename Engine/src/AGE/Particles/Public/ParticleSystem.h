#pragma once
#include <glm/glm.hpp>

#include "Core/Public/DeltaTime.h"
#include "Camera/Public/Camera.h"
#include "Math/Public/MathStructures.h"
#include "Math/Public/UtilityFunctions.h"

namespace AGE
{
	struct ParticleProps
	{
		Vector3 Position;
		Vector3 Velocity;
		Vector3 VelocityVariation;
		Vector4 ColorBegin;
		Vector4 ColorEnd;

		float SizeBegin;
		float SizeEnd;
		float SizeVariation;
		float LifeTime = 1.f;
	};

	class ParticleSystem
	{
	public:
		ParticleSystem(uint32_t MaxParticles = 100000);

		void OnUpdate(TimeStep DeltaTime);
		void OnRender(const Camera& Camera, const Matrix4D& Transform);

		void Emit(const ParticleProps& Properties);



	private:

		struct Particle : public QuadProperties
		{
			Vector3 Position;
			Vector3 Velocity;
			Vector4 ColorBegin;
			Vector4 ColorEnd;
			float Rotation = 0.f;
			float SizeBegin;
			float SizeEnd;

			float LifeTime = 1.f;
			float LifeRemaining = 0.f;

			bool Active = false;
			
		};

		std::vector<Particle> m_ParticlePool;

		uint32_t m_PoolIndex ;
	};
}
