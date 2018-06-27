#include <octoon/film_camera_component.h>

namespace octoon
{
	OctoonImplementSubClass(FilmCameraComponent, CameraComponent, "FilmCameraComponent")

	FilmCameraComponent::FilmCameraComponent() noexcept
		: CameraComponent(std::make_shared<video::FilmCamera>())
	{
		camera_ = dynamic_cast<video::FilmCamera*>(CameraComponent::camera_.get());
	}

	FilmCameraComponent::FilmCameraComponent(float zoom, float ratio, float znear, float zfar) noexcept
		: FilmCameraComponent()
	{
		this->setZoom(zoom);
		this->setRatio(ratio);
		this->setNear(znear);
		this->setFar(zfar);
	}

	FilmCameraComponent::~FilmCameraComponent() noexcept
	{
	}

	void
	FilmCameraComponent::setNear(float znear) noexcept
	{
		camera_->setNear(znear);
	}

	void
	FilmCameraComponent::setFar(float zfar) noexcept
	{
		camera_->setFar(zfar);
	}

	void
	FilmCameraComponent::setRatio(float ratio) noexcept
	{
		camera_->setRatio(ratio);
	}

	void
	FilmCameraComponent::setZoom(float zoom) noexcept
	{
		camera_->setZoom(zoom);
	}
	
	void
	FilmCameraComponent::setAperture(float fov) noexcept
	{
		camera_->setAperture(fov);
	}

	void 
	FilmCameraComponent::setFilmSize(float width) noexcept
	{
		camera_->setFilmSize(width);
	}

	void
	FilmCameraComponent::setFocalLength(float length) noexcept
	{
		camera_->setFocalLength(length);
	}

	float
	FilmCameraComponent::getNear() const noexcept
	{
		return camera_->getNear();
	}

	float
	FilmCameraComponent::getFar() const noexcept
	{
		return camera_->getFar();
	}

	float
	FilmCameraComponent::getRatio() const noexcept
	{
		return camera_->getRatio();
	}

	float
	FilmCameraComponent::getZoom() const noexcept
	{
		return camera_->getZoom();
	}

	float
	FilmCameraComponent::getAperture() const noexcept
	{
		return camera_->getAperture();
	}

	float
	FilmCameraComponent::getFilmSize() const noexcept
	{
		return camera_->getFilmSize();
	}

	float
	FilmCameraComponent::getFocalLength() const noexcept
	{
		return camera_->getFocalLength();
	}

	GameComponentPtr
	FilmCameraComponent::clone() const noexcept
	{
		auto instance = std::make_shared<FilmCameraComponent>();
		instance->setName(this->getName());
		instance->setNear(this->getNear());
		instance->setFar(this->getFar());
		instance->setAperture(this->getAperture());
		instance->setRatio(this->getRatio());
		instance->setClearColor(this->getClearColor());
		instance->setViewport(this->getViewport());
		instance->setCameraOrder(this->getCameraOrder());
		instance->setClearFlags(this->getClearFlags());

		return instance;
	}
}