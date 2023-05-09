#pragma once
#include <string>
#include "Screens/UIHelpers.h"

namespace Characters
{
	enum class CharacterState
	{
		IDLE,
		ATTACK,
		DIE,
		SPELL,
		HEAL,
		BLOCK,
		HIT
	};

	class CharacterAnimator
	{
	public:
		bool IsNotPlayer = false;
		
	private:
		CharacterState mState;
		const std::string name;
		int mCurrentFrame = 0;
		int mFrameCounter = 0;
		bool mReverse = false;
		bool mAnimate = true;

		 static constexpr char* m_idle = "resources/Art/Idle/";
		 static constexpr char* m_attack = "resources/Art/Attack/";
		 static constexpr char* m_die = "resources/Art/Die/";
		 static constexpr char* m_spell = "resources/Art/Spell/";
		 static constexpr char* m_heal = "resources/Art/Heal/";
		 static constexpr char* m_block = "resources/Art/Block/";
		 static constexpr int m_frameSpeed = 60/8;

		Texture2D m_idleTexture;
		Texture2D m_attackTexture;
		Texture2D m_dieTexture;
		Texture2D m_spellTexture;
		Texture2D m_healTexture;
		Texture2D m_blockTexture;

		Vector2 mPosition;

	public:
		CharacterAnimator(const std::string name, bool notPlayer);
		~CharacterAnimator();

		void SetState(const CharacterState state);
		void AnimateCharacater(const Vector2& position);
		void DrawDefaultState(const Vector2& position) const;
		void DrawDeadState(const Vector2& position) const;
		static const std::string GetEnumName(const CharacterState state);

	private:
		void SetIdle();
		void UseAttack();
		void SetDead();
		void UseSpell();
		void UseHeal();
		void Block();
		void Hit();
		void DrawTexture(const Texture2D& target, const int currentFrame, const int maxFrames, Color colour) const;
		void DrawTexture(const Vector2& pos, const int size, const Texture2D& target, const int currentFrame, const int maxFrames, Color colour) const;
		void UpdateFrame(int maxFrames);
	};
}
