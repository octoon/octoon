#ifndef OCTOON_GAME_BASE_FEATURES_H_
#define OCTOON_GAME_BASE_FEATURES_H_

#include <octoon/game_feature.h>

namespace octoon
{
	class GameBaseFeature final : public GameFeature
	{
		OctoonDeclareSubClass(GameBaseFeature, GameFeature)
	public:
		GameBaseFeature() noexcept;
		~GameBaseFeature() noexcept;

	private:
		void onActivate() noexcept override;

		void onFrameBegin() noexcept override;
		void onFrame() noexcept override;
		void onFrameEnd() noexcept override;

		void onFixedUpdate(const runtime::any& data) noexcept;
	};
}

#endif