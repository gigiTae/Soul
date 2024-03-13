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

		std::shared_ptr<Device> GetDevice()const { return _device; }

	private:
		std::shared_ptr<Device> _device;

	};


}