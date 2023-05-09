#include "CharacterAnimator.h"
namespace Characters
{
	CharacterAnimator::CharacterAnimator(const std::string className, bool notPlayer)
		:name(className + ".png"), mState(CharacterState::IDLE), IsNotPlayer(notPlayer)
	{
		m_idleTexture = LoadTexture((m_idle + name).c_str());
		m_attackTexture = LoadTexture((m_attack + name).c_str());
		m_dieTexture = LoadTexture((m_die + name).c_str());
		m_spellTexture = LoadTexture((m_spell + name).c_str());
		m_healTexture = LoadTexture((m_heal + name).c_str());
		m_blockTexture = LoadTexture((m_block + name).c_str());
	}
	CharacterAnimator::~CharacterAnimator()
	{
		UnloadTexture(m_idleTexture);
		UnloadTexture(m_attackTexture);
		UnloadTexture(m_dieTexture);
		UnloadTexture(m_spellTexture);
		UnloadTexture(m_healTexture);
		UnloadTexture(m_blockTexture);
	}
	void CharacterAnimator::SetState(const CharacterState state)
	{
		mFrameCounter = 0;
		mCurrentFrame = 0;
		mReverse = false;
		mState = state;
	}
	void CharacterAnimator::AnimateCharacater(const Vector2& position)
	{
		mPosition = position;
		++mFrameCounter;

		if (mFrameCounter >= (m_frameSpeed))
		{
			mFrameCounter = 0;

			mAnimate = true;
		}

		switch (mState)
		{
		case CharacterState::IDLE:
			SetIdle();
			break;
		case CharacterState::ATTACK:
			UseAttack();
			break;
		case CharacterState::DIE:
			SetDead();
			break;
		case CharacterState::SPELL:
			UseSpell();
			break;
		case CharacterState::HEAL:
			UseHeal();
			break;
		case CharacterState::BLOCK:
			Block();
			break;
		case CharacterState::HIT:
			Hit();
			break;
		}

		mAnimate = false;
	}
	void CharacterAnimator::DrawDefaultState(const Vector2& position) const
	{
		DrawTexture(position, 1, m_idleTexture, 0, 2, WHITE);
	}
	void CharacterAnimator::DrawDeadState(const Vector2& position) const
	{
		DrawTexture(position, 1, m_dieTexture, 5, 6, WHITE);
	}

	const  std::string CharacterAnimator::GetEnumName(const CharacterState state)
	{
		switch (state)
		{
		case CharacterState::IDLE:
			return "IDLE";
			break;
		case CharacterState::ATTACK:
			return "ATTACK";
			break;
		case CharacterState::DIE:
			return "DIE";
			break;
		case CharacterState::SPELL:
			return "SPELL";
			break;
		case CharacterState::HEAL:
			return "HEAL";
			break;
		case CharacterState::BLOCK:
			return "BLOCK";
			break;
		case CharacterState::HIT:
			return "HIT";
			break;
		}
	}
	void CharacterAnimator::SetIdle()
	{
		DrawTexture(m_idleTexture, mCurrentFrame, 2, WHITE);
		UpdateFrame(2);
	}
	void CharacterAnimator::UseAttack()
	{
		DrawTexture(m_attackTexture, mCurrentFrame, 7, WHITE);
		UpdateFrame(7);

		if (mCurrentFrame <= 0 && mAnimate)
		{
			mState = CharacterState::IDLE;
		}
	}
	void CharacterAnimator::SetDead()
	{
		DrawTexture(m_dieTexture, mCurrentFrame, 6, WHITE);
		if (mAnimate)
		{
			if (mCurrentFrame < 5)
			{
				++mCurrentFrame;
			}
		}
	}
	void CharacterAnimator::UseSpell()
	{
		DrawTexture(m_spellTexture, mCurrentFrame, 8, WHITE);
		UpdateFrame(8);

		if (mCurrentFrame <= 0 && mAnimate)
		{
			mState = CharacterState::IDLE;
		}
	}
	void CharacterAnimator::UseHeal()
	{
		DrawTexture(m_healTexture, mCurrentFrame, 3, WHITE);
		UpdateFrame(3);

		if (mCurrentFrame <= 0 && mAnimate)
		{
			mState = CharacterState::IDLE;
		}
	}
	void CharacterAnimator::Block()
	{
		DrawTexture(m_blockTexture, mCurrentFrame, 2, WHITE);
		UpdateFrame(2);
	}
	void CharacterAnimator::Hit()
	{
		DrawTexture(m_blockTexture, mCurrentFrame, 2, RED);
		UpdateFrame(2);

		if (mCurrentFrame <= 0 && mAnimate)
		{
			mState = CharacterState::IDLE;
		}
	}
	void CharacterAnimator::DrawTexture(const Texture2D& target, const int currentFrame, const int maxFrames, Color colour) const
	{
		DrawTexture(mPosition, 3, target, currentFrame, maxFrames, colour);
	}

	void CharacterAnimator::DrawTexture(const Vector2& pos, const int size, const Texture2D& target, const int currentFrame, const int maxFrames, Color colour) const
	{
		Rectangle frameRec = { (float)currentFrame * target.width / maxFrames,0,(float)target.width / maxFrames,(float)target.height };
		Rectangle dest = { pos.x, pos.y, fabsf(frameRec.width) * size, fabsf(frameRec.height) * size };
		if (IsNotPlayer)
		{
			frameRec.width = -frameRec.width;
		}

		Vector2 origin = { 0.0f, 0.0f };

		DrawTexturePro(target, frameRec, dest, origin, 0.0f, colour);
	}
	void CharacterAnimator::UpdateFrame(int maxFrames)
	{
		if (mAnimate)
		{
			if (mCurrentFrame < (maxFrames - 1) && !mReverse)
			{
				++mCurrentFrame;
			}
			else
			{
				mReverse = true;
				--mCurrentFrame;
				if (mCurrentFrame <= 0)
				{
					mCurrentFrame = 0;
					mReverse = false;
				}
			}
		}
	}
}