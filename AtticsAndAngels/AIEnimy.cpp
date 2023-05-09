#include "AIEnimy.h"

namespace Characters
{
	void AIEnimy::EnableAnimator()
	{
		if (animator != nullptr)
		{
			delete animator;
			animator = nullptr;
		}

		animator = new CharacterAnimator(GetClassData()->name, true);
	}
}