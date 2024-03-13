#pragma once


namespace SoulGraphics
{
	class Device;

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		void Initialize(const std::shared_ptr<Device>& device);

		void Finalize();

	private:
		std::shared_ptr<Device> _device;

	};


}