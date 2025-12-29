#pragma once
#include "Texture/Public/SubTexture.h"
#include "Core/Public/DeltaTime.h"
#include "Structs/Public/DataStructures.h"
#include "Core/Public/Timer.h"


namespace AGE
{

	struct AnimationSpecification
	{
	public:

		std::string Name = "";
		int NumberOfFrames = 0;
		float Width, Height;
		CharMovementStatus Status = CharMovementStatus::UNDEFINED;
		Ref<Texture2D> Texture;

		bool bIsReadyToLoad = false;

		bool IsReadyToLoad()
		{
			if (!bIsReadyToLoad)
			{
				return false;
			}
			if (Name.empty())
			{
				CoreLogger::Error("Animation must have a Name!");
				bIsReadyToLoad = false;
				return false;
			}
			if (!(NumberOfFrames > 1))
			{
				CoreLogger::Error("Animations must have more than 1 frame");
				bIsReadyToLoad = false;
				return false;
			}
			if (Status == CharMovementStatus::UNDEFINED)
			{
				CoreLogger::Error("Animation must correlate to a movement status");
				bIsReadyToLoad = false;
				return false;
			}
			return true;
		}

		void SetIsReadyToLoad(bool Value)
		{
			bIsReadyToLoad = Value;
		}
	};

	class Animation
	{
	public:

		Animation();
		Animation(const Animation&) = default;
		~Animation() = default;

		void OnDestroy();

		void OnAnimate(TimeStep DeltaTime);


		int GetFrameRate() { return m_FrameRate; }
		void SetFrameRate(int Rate) { m_FrameRate = Rate; }

		int GetMaxFrames() { return m_MaxFrames; }
		void SetMaxFrames(int Frames) { m_MaxFrames = Frames; }

		int GetCurrentFrame() { return m_CurrentFrame; }
		void SetCurrentFrame(int Frame);

		bool GetOscillate() { return bOscillate; }
		void SetOscillate(bool Osc) { bOscillate = Osc; }

		Ref<SubTexture2D> GetCurrentTexture() { return m_CurrentTexture; }
		void LoadAnimation(const AnimationSpecification Anim);
		void LoadAnimations(const std::vector<AnimationSpecification>& Anims);
		void SetCurrentTexture(CharMovementStatus Status);

	private:

		int m_CurrentFrame, m_FrameInc, m_MaxFrames, m_FrameRate;

		float m_OldTime;

		bool bOscillate;

		std::unordered_map<CharMovementStatus, AnimationSpecification> m_AnimationTextures;
		Ref<SubTexture2D> m_CurrentTexture;

		Timer m_Timer;
	};
}
