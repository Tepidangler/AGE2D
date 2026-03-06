/**

    @file      ScriptableEntity.h
    @brief     
    @details   ~
    @author    De'Lano Wilcox
    @date      29.05.2025
    @copyright � Alcoy Game Studios, 2025. All right reserved.

**/
#pragma once
#include "Scene/Public/Entity.h"
#include "Structs/Public/Functions.h"
#include <rttr/type>
#ifdef __clang__
#pragma clang diagnostic push
#ifdef AG_PLATFORM_LINUX
#pragma clang diagnostic ignored "-Wunused-function"
#endif
#include "rttr/registration_friend.h"
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#include "rttr/registration_friend.h"
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include "rttr/registration_friend.h"
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif



namespace AGE
{
	enum class MetaDataType
	{
		Scriptable,
	};
	struct AGENode;

	class ScriptableEntity : public std::enable_shared_from_this<ScriptableEntity>
	{
	public:

		virtual ~ScriptableEntity() {};

  /**
      @brief  
      @retval - bool 
      @author De'Lano Wilcox
  **/
		virtual bool IsCharacter()
		{
			return GetScriptableEntityType() == "Character";
		}
  /**
      @brief  
      @tparam T - Represents Component within the Entity Component System
      @retval   - T
      @author De'Lano Wilcox
  **/
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

		template<typename T, typename ... Args>
		T& AddComponent(Args&& ... args)
		{
			return m_Entity.AddComponent<T>();
		}

		virtual std::string GetScriptableEntityType() { return ""; }
		virtual void OnEvent(Event& E) {};
		virtual void OnOverlapStart() {}
		virtual void OnOverlapStop() {}
		virtual void OnHit() {}

		virtual void AddBeginPlayFunctions(AGEFunction< AGENode, ScriptableEntity> Func) {};
		virtual void AddTickFunctions(AGEFunction< AGENode, ScriptableEntity> Func) {};

		virtual void ClearFunctions() {};
		virtual std::string GetName() { return ""; };
		virtual Vector3 GetLocation() { return {}; }
		virtual void SetLocation(const AGE::Vector3& Location) {}

		virtual UUID GetID() { return m_Entity.GetUUID(); }

	protected:
		virtual void OnCreate() {};
		virtual void OnBeginPlay() {};
		virtual void OnDestroy() {};
		virtual void OnUpdate(TimeStep DeltaTime) {};
		virtual void Reset() {};
		virtual Entity& GetEntityHandle() { return m_Entity; }
		virtual void PushComp();

	private:
		Entity m_Entity;
		friend class Scene;
		RTTR_ENABLE()
		RTTR_REGISTRATION_FRIEND
	};
}
