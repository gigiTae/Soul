#include "SoulGraphicsPCH.h"
#include "Animator.h"
#include "AnimaitonClip.h"

SoulGraphics::Animator::Animator()
{

}

SoulGraphics::Animator::~Animator()
{

}

void SoulGraphics::Animator::AddAnimationClip(const std::shared_ptr<AnimaitonClip>& clip)
{
	_animationClips.push_back(clip);
}
