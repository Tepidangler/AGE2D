#include "AGEpch.hpp"
#include "Animation/Public/Animation.h"



namespace AGE
{
	/**
 * @brief Default constructor for the Animation class.
 * Initializes all member variables to default values.
 *
 * @param None
 *
 * @return None
 */
/**
 * @brief Constructor for the Animation class. Initializes all member variables to default values.
 * 
 * This constructor initializes m_CurrentFrame, m_MaxFrames, and m_FrameInc to 0 and 1 respectively. It also sets m_FrameRate to 100 and m_OldTime to 0. The boolean variable bOscillate is set to false. A Timer object is created and assigned to m_Timer.
 * 
 * @return Animation object with all member variables initialized to default values.
 */
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


	/**
 * @brief This function is called when the object is being destroyed.
 * 
 * @return void No return value.
 */
/**
 * @brief This function is called when the object is being destroyed.
 * 
 * @return void No return value.
 */
void Animation::OnDestroy()
	{
	}
	/**
 * @brief Updates the object's animation based on elapsed time.
 * 
 * This function checks if enough time has passed to move to the next frame of the animation. If it has, the current frame index is updated and oscillates between min and max frames if the animation should be oscillating.
 * 
 * @param DeltaTime The amount of time that has passed since the last update.
 */
/**
 * @brief This function is used to animate the object based on a time step.
 * 
 * The function checks if enough time has passed since the last frame update. If it has, the current frame index is updated and oscillates between min and max frames if the 'bOscillate' flag is set.
 * @param DeltaTime The time elapsed since the last frame in seconds.
 */
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
	/**
 * @brief Set the Current Animation Frame.
 *
 * This function sets the current frame of an animation. The frame number should be between 0 and m_MaxFrames - 1, inclusive. If the provided frame is outside this range, the function does nothing.
 *
 * @param Frame The new frame to set as the current frame.
 */
/**
 * @brief Set the Current Frame of Animation.
 *
 * This function sets the current frame of an animation to a specified value. If the provided frame number is negative or larger than or equal to the maximum frames, it will return without doing anything. 
 *
 * @param Frame The new frame number to set as the current frame.
 */
void Animation::SetCurrentFrame(int Frame)
	{
		if (Frame < 0 || Frame >= m_MaxFrames)
		{
			return;
		}

		m_CurrentFrame = Frame;
	}
	/**
 * @brief Loads an animation into the system based on the provided specification.
 * 
 * This function takes in a constant reference to an object of type `AnimationSpecification` and uses it to load an animation into the system. The animation is added to the member variable `m_AnimationTextures` as a pair with the key being the movement status from the AnimationSpecification.
 * 
 * @param Anim A constant reference to an object of type `AnimationSpecification` that contains all necessary information for loading an animation.
 * 
 * @return void No return value is expected.
 */
/** 
 * @brief Loads an animation into the system based on the provided specification.
 * @param Anim The AnimationSpecification containing details about the animation to be loaded.
 */
void Animation::LoadAnimation(const AnimationSpecification Anim)
	{
		m_AnimationTextures.emplace(std::make_pair(Anim.MovementStatus, Anim));
	}
	/**
 * @brief Loads a set of animations into the animation system.
 * 
 * This function takes in a vector of AnimationSpecification objects and loads them into the m_AnimationTextures map. Each element in the vector is added as a pair to the map, with the key being the MovementStatus from each AnimationSpecification object.
 * 
 * @param[in] Anims - A const reference to a vector of AnimationSpecification objects.
 * @return void
 */
/**
 * @brief Loads a list of animation specifications into the m_AnimationTextures map.
 *
 * This function takes in a vector of AnimationSpecification objects and adds them to the m_AnimationTextures map, using the MovementStatus field as the key for each entry. 
 * The AnimationSpecification object is then stored as the value associated with its corresponding MovementStatus key.
 *
 * @param Anims A vector of AnimationSpecification objects to be loaded into the m_AnimationTextures map.
 */
void Animation::LoadAnimations(const std::vector<AnimationSpecification>& Anims)
	{
		for (auto S : Anims)
		{
			m_AnimationTextures.emplace(std::make_pair(S.MovementStatus,  S));
		}
	}
	/**
 * @brief Sets the current texture based on the character movement status.
 *
 * This function sets the current texture of the animation object to a subtexture 
 * corresponding to the provided CharMovementStatus. The subtexture is chosen from 
 * the set of animation textures stored in m_AnimationTextures, and it's determined 
 * by the status parameter.
 *
 * @param status The current movement status of the character. This determines which 
 *               texture to use for rendering the animation.
 */
/**
 * @brief Sets the current texture based on the character movement status.
 *
 * This function sets the current texture of an animation object by taking a CharMovementStatus parameter which indicates the current state of the character. 
 * It uses this information to select and set the correct subtexture from the m_AnimationTextures array. The selected subtexture is then assigned to m_CurrentTexture.
 *
 * @param status The current movement status of the character. This can be any value defined in CharMovementStatus enum.
 */
void Animation::SetCurrentTexture(CharMovementStatus status)
	{
		m_CurrentTexture = AGE::SubTexture2D::CreateFromCoords(m_AnimationTextures[status].Texture, AGE::Vector2((float)m_CurrentFrame, 0.f), AGE::Vector2(m_AnimationTextures[status].Width / (float)m_AnimationTextures[status].NumberOfFrames, m_AnimationTextures[status].Height));
	}
}