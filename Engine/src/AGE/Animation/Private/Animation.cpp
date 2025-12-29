#include "AGEpch.hpp"
#include "Animation/Public/Animation.h"



namespace AGE
{
	Animation::Animation()
	{
		m_CurrentFrame = 0;
		m_MaxFrames = 0;
		m_FrameInc = 1;

		m_FrameRate = 100;
		m_OldTime = 0;

		bOscillate = false;

		m_Timer = Timer();
	}


	void Animation::OnDestroy()
	{
	}
	void Animation::OnAnimate(TimeStep DeltaTime)
	{
		
		if (m_OldTime + (float)m_FrameRate > m_Timer.ElapsedMillis())
		{
			return;
		}

		m_OldTime = m_Timer.ElapsedMillis();

		m_CurrentFrame += m_FrameInc;

		if (bOscillate)
		{
			if (m_FrameInc > 0)
			{
				if (m_CurrentFrame >= m_MaxFrames)
				{
					m_FrameInc = -m_FrameInc;
				}
				else if (m_CurrentFrame <= 0)
				{
					m_FrameInc = -m_FrameInc;
				}
				else if (m_CurrentFrame >= m_MaxFrames)
				{
					m_CurrentFrame = 0;
				}
			}

		}
	}
	void Animation::SetCurrentFrame(int Frame)
	{
		if (Frame < 0 || Frame >= m_MaxFrames)
		{
			return;
		}

		m_CurrentFrame = Frame;
	}
	void Animation::LoadAnimation(const AnimationSpecification Anim)
	{
		m_AnimationTextures.emplace(std::make_pair(Anim.Status, Anim));
	}
	void Animation::LoadAnimations(const std::vector<AnimationSpecification>& Anims)
	{
		for (auto S : Anims)
		{
			m_AnimationTextures.emplace(std::make_pair(S.Status,  S));
		}
	}
	void Animation::SetCurrentTexture(CharMovementStatus Status)
	{
		m_CurrentTexture = AGE::SubTexture2D::CreateFromCoords(m_AnimationTextures[Status].Texture, AGE::Vector2((float)m_CurrentFrame, 0.f), AGE::Vector2(m_AnimationTextures[Status].Width / m_AnimationTextures[Status].NumberOfFrames, m_AnimationTextures[Status].Height));
	}
}