#ifndef OCTOON_GAME_COMPONENT_H_
#define OCTOON_GAME_COMPONENT_H_

#include <octoon/game_object.h>

namespace octoon
{
	class OCTOON_EXPORT GameComponent : public runtime::RttiInterface
	{
		OctoonDeclareSubInterface(GameComponent, runtime::RttiInterface)
	public:
		GameComponent() noexcept;
		virtual ~GameComponent() noexcept;

		void setActive(bool active) except;
		bool getActive() const noexcept;

		void setName(const std::string& name) noexcept;
		void setName(std::string&& name) noexcept;
		const std::string& getName() const noexcept;

		GameObjectPtr getGameObject() const noexcept;

		template<typename T, typename = std::enable_if_t<std::is_base_of<GameComponent, T>::value>>
		std::shared_ptr<T> getComponent() const noexcept { return std::dynamic_pointer_cast<T>(this->getComponent(T::RTTI)); }
		GameComponentPtr getComponent(const runtime::Rtti* type) const noexcept;
		GameComponentPtr getComponent(const runtime::Rtti& type) const noexcept;

		template<typename T, typename = std::enable_if_t<std::is_base_of<GameComponent, T>::value>>
		void getComponents(GameComponents& components) const noexcept { this->getComponents(T::RTTI, components); }
		void getComponents(const runtime::Rtti* type, GameComponents& components) const noexcept;
		void getComponents(const runtime::Rtti& type, GameComponents& components) const noexcept;

		template<typename T, typename = std::enable_if_t<std::is_base_of<GameComponent, T>::value>>
		std::shared_ptr<T> getComponentInChildren() const noexcept { return std::dynamic_pointer_cast<T>(this->getComponentInChildren(T::RTTI)); }
		GameComponentPtr getComponentInChildren(const runtime::Rtti* type) const noexcept;
		GameComponentPtr getComponentInChildren(const runtime::Rtti& type) const noexcept;

		template<typename T, typename = std::enable_if_t<std::is_base_of<GameComponent, T>::value>>
		void getComponentsInChildren(GameComponents& components) const noexcept { this->getComponentsInChildren(T::RTTI, components); }
		void getComponentsInChildren(const runtime::Rtti* type, GameComponents& components) const noexcept;
		void getComponentsInChildren(const runtime::Rtti& type, GameComponents& components) const noexcept;

		const GameComponents& getComponents() const noexcept;

		static GameComponentPtr instantiate(const GameComponent* component) except;
		static GameComponentPtr instantiate(const GameComponent& component) except;

		virtual GameComponentPtr clone() const noexcept = 0;

	protected:
		void addComponentDispatch(GameDispatchTypes type) noexcept;
		void removeComponentDispatch(GameDispatchTypes type) noexcept;
		void removeComponentDispatchs() noexcept;

	private:
		virtual void onAttach() except;
		virtual void onDetach() noexcept;

		virtual void onAttachComponent(const GameComponentPtr& component) except;
		virtual void onDetachComponent(const GameComponentPtr& component) noexcept;

		virtual void onActivate() except;
		virtual void onDeactivate() noexcept;

		virtual void onFrameBegin() except;
		virtual void onFrame() except;
		virtual void onFrameEnd() except;

		virtual void onMoveBefore() except;
		virtual void onMoveAfter() except;

		virtual void onLayerChangeBefore() except;
		virtual void onLayerChangeAfter() except;

		virtual void onGui() except;

	private:
		friend GameObject;
		void _setGameObject(GameObject* gameobj) noexcept;

	private:
		bool active_;

		std::string name_;

		GameObject* gameObject_;
	};
}

#endif