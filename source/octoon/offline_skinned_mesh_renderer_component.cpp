#include <octoon/offline_skinned_mesh_renderer_component.h>
#include <octoon/offline_feature.h>
#include <octoon/skinned_morph_component.h>
#include <octoon/transform_component.h>

namespace octoon
{
	OctoonImplementSubClass(OfflineSkinnedMeshRendererComponent, OfflineRenderComponent, "OfflineMeshRenderer")

	OfflineSkinnedMeshRendererComponent::OfflineSkinnedMeshRendererComponent() noexcept
		: needUpdate_(true)
	{
	}

	OfflineSkinnedMeshRendererComponent::OfflineSkinnedMeshRendererComponent(model::Materials&& materials, GameObjects&& transforms) noexcept
		: OfflineSkinnedMeshRendererComponent()
	{
		this->setMaterials(std::move(materials));
		this->setTransforms(std::move(transforms));
	}

	OfflineSkinnedMeshRendererComponent::OfflineSkinnedMeshRendererComponent(model::MaterialPtr&& material, GameObjects&& transforms) noexcept
		: OfflineSkinnedMeshRendererComponent()
	{
		this->setMaterial(std::move(material));
		this->setTransforms(std::move(transforms));
	}

	OfflineSkinnedMeshRendererComponent::OfflineSkinnedMeshRendererComponent(const model::Materials& materials, const GameObjects& transforms) noexcept
		: OfflineSkinnedMeshRendererComponent()
	{
		this->setMaterials(materials);
		this->setTransforms(transforms);
	}

	OfflineSkinnedMeshRendererComponent::OfflineSkinnedMeshRendererComponent(const model::MaterialPtr& material, const GameObjects& transforms) noexcept
		: OfflineSkinnedMeshRendererComponent()
	{
		this->setMaterial(material);
		this->setTransforms(transforms);
	}

	OfflineSkinnedMeshRendererComponent::~OfflineSkinnedMeshRendererComponent() noexcept
	{
	}

	void
	OfflineSkinnedMeshRendererComponent::setTransforms(const GameObjects& transforms) noexcept
	{
		transforms_ = transforms;
	}

	void
	OfflineSkinnedMeshRendererComponent::setTransforms(GameObjects&& transforms) noexcept
	{
		transforms_ = std::move(transforms);
	}

	const GameObjects&
	OfflineSkinnedMeshRendererComponent::getTransforms() const noexcept
	{
		return transforms_;
	}

	void
	OfflineSkinnedMeshRendererComponent::setMorphBlendEnable(bool enable) noexcept
	{
		morphEnable_ = enable;
	}

	bool
	OfflineSkinnedMeshRendererComponent::getMorphBlendEnable() const noexcept
	{
		return morphEnable_;
	}

	void
	OfflineSkinnedMeshRendererComponent::uploadMeshData(const model::Mesh& mesh) noexcept
	{
		std::vector<math::float4x4> joints(transforms_.size());

		auto& bindposes = mesh.getBindposes();
		if (bindposes.size() != transforms_.size())
		{
			for (std::size_t i = 0; i < transforms_.size(); ++i)
				joints[i].makeIdentity();
		}
		else
		{
			for (std::size_t i = 0; i < transforms_.size(); ++i)
				joints[i] = math::transformMultiply(transforms_[i]->getComponent<TransformComponent>()->getTransform(), bindposes[i]);
		}

		auto& vertices = mesh.getVertexArray();
		auto& normals = mesh.getNormalArray();
		auto& weights = mesh.getWeightArray();

		auto& dstVertices = skinnedMesh_->getVertexArray();
		auto& dstNormals = skinnedMesh_->getNormalArray();

		auto numVertices = mesh.getNumVertices();

#if !defined(_DEBUG)
#		pragma omp parallel for num_threads(4)
#endif
		for (std::size_t i = 0; i < numVertices; i++)
		{
			math::float3 v = math::float3::Zero;
			math::float3 n = math::float3::Zero;

			for (std::uint8_t j = 0; j < 4; j++)
			{
				auto w = weights[i].weights[j];
				if (w > 0.0)
				{
					v += (joints[weights[i].bones[j]] * vertices[i]) * w;
					n += ((math::float3x3)joints[weights[i].bones[j]] * normals[i]) * w;
				}
			}

			dstVertices[i] = v;
			dstNormals[i] = n;
		}

		if (morphEnable_)
		{
			for (auto& it : skinnedComponents_)
			{
				auto control = it->getControl();
				if (control > 0.0f)
				{
					auto morph = it->downcast<SkinnedMorphComponent>();
					auto& indices = morph->getIndices();
					auto& offsets = morph->getOffsets();

					auto numIndices = indices.size();

					for (std::size_t i = 0; i < numIndices; i++)
					{
						auto offset = offsets[i];
						auto index = indices[i];

						dstVertices[index] += offset * control;
					}
				}
			}
		}

		OfflineMeshRendererComponent::uploadMeshData(*skinnedMesh_);
	}

	GameComponentPtr
	OfflineSkinnedMeshRendererComponent::clone() const noexcept
	{
		auto instance = std::make_shared<OfflineSkinnedMeshRendererComponent>();
		instance->setName(this->getName());
		instance->setTransforms(this->getTransforms());
		instance->setMaterial(this->getMaterial() ? (this->isSharedMaterial() ? this->getMaterial() : this->getMaterial()->clone()) : nullptr, this->isSharedMaterial());

		return instance;
	}

	void
	OfflineSkinnedMeshRendererComponent::onActivate() noexcept
	{
		this->addMessageListener("octoon:animation:update", std::bind(&OfflineSkinnedMeshRendererComponent::onAnimationUpdate, this, std::placeholders::_1));
		OfflineMeshRendererComponent::onActivate();
	}

	void
	OfflineSkinnedMeshRendererComponent::onDeactivate() noexcept
	{
		this->removeMessageListener("octoon:animation:update", std::bind(&OfflineSkinnedMeshRendererComponent::onAnimationUpdate, this, std::placeholders::_1));
		OfflineMeshRendererComponent::onDeactivate();
	}

	void
	OfflineSkinnedMeshRendererComponent::onAnimationUpdate(const runtime::any& data) noexcept
	{
		auto offlineFeature = this->getFeature<OfflineFeature>();
		if (offlineFeature)
			offlineFeature->setFramebufferDirty(true);

		this->needUpdate_ = true;
	}

	void
	OfflineSkinnedMeshRendererComponent::onMeshReplace(const runtime::any& data) noexcept
	{
		auto mesh = runtime::any_cast<model::MeshPtr>(data);
		if (mesh)
		{
			mesh_ = mesh;
			skinnedMesh_ = mesh->clone();
		}

		auto offlineFeature = this->getFeature<OfflineFeature>();
		if (offlineFeature)
			offlineFeature->setFramebufferDirty(true);

		needUpdate_ = true;
	}

	void
	OfflineSkinnedMeshRendererComponent::onAttachComponent(const GameComponentPtr& component) noexcept
	{
		if (component->isInstanceOf<SkinnedMorphComponent>())
			skinnedComponents_.push_back(component.get()->downcast<SkinnedComponent>());
	}

	void
	OfflineSkinnedMeshRendererComponent::onDetachComponent(const GameComponentPtr& component) noexcept
	{
		if (component->isInstanceOf<SkinnedMorphComponent>())
		{
			auto it = std::find(skinnedComponents_.begin(), skinnedComponents_.end(), component.get());
			if (it != skinnedComponents_.end())
				skinnedComponents_.erase(it);
		}
	}

	void
	OfflineSkinnedMeshRendererComponent::onPreRender() noexcept
	{
		if (mesh_ && needUpdate_)
		{
			this->uploadMeshData(*mesh_);
			needUpdate_ = false;
		}
	}
}