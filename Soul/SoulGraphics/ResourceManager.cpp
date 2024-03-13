#include "SoulGraphicsPCH.h"
#include "ResourceManager.h"

SoulGraphics::ResourceManager::ResourceManager()
	:_device(nullptr)
{}

SoulGraphics::ResourceManager::~ResourceManager()
{

}

void SoulGraphics::ResourceManager::Initialize(const std::shared_ptr<Device>& device)
{
	_device = device;
}

void SoulGraphics::ResourceManager::Finalize()
{

}