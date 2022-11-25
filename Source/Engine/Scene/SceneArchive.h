#pragma once
#include "Scene.h"
#include "SceneNode.h"
#include "Component/DirectionalLight.h"
#include "Component/Landscape.h"
#include "Component/Light.h"
#include "Component/StaticMesh.h"
#include "Component/PMXComponent.h"
#include "Component/SpotLight.h"
#include "Component/Transform.h"


#include "../Version.h"

#define MAKE_VERSION_SCENE(ClassType) CEREAL_CLASS_VERSION(ClassType, SCENE_VERSION_CONTROL)

#define SCENE_ARCHIVE_IMPL_BASIC(CompNameXX) \
MAKE_VERSION_SCENE(Flower::CompNameXX); \
CEREAL_REGISTER_TYPE_WITH_NAME(Flower::CompNameXX, "Flower::"#CompNameXX);

#define SCENE_ARCHIVE_IMPL(CompNameXX) \
SCENE_ARCHIVE_IMPL_BASIC(CompNameXX); \
template<class Archive> \
void Flower::CompNameXX::serialize(Archive& archive, std::uint32_t const version)

#define SCENE_ARCHIVE_IMPL_INHERIT(CompNameXX, CompNamePP) \
SCENE_ARCHIVE_IMPL_BASIC(CompNameXX); \
CEREAL_REGISTER_POLYMORPHIC_RELATION(Flower::CompNamePP, Flower::CompNameXX)\
template<class Archive> \
void Flower::CompNameXX::serialize(Archive& archive, std::uint32_t const version) { \
archive(cereal::base_class<Flower::CompNamePP>(this));

#define SCENE_ARCHIVE_IMPL_INHERIT_END }


SCENE_ARCHIVE_IMPL(Component)
{
	archive(m_node);
}

SCENE_ARCHIVE_IMPL_INHERIT(Transform, Component)
{
	archive(m_translation);
	archive(m_rotation);
	archive(m_scale);
}
SCENE_ARCHIVE_IMPL_INHERIT_END

SCENE_ARCHIVE_IMPL_INHERIT(LightComponent, Component)
{
	archive(m_color);
	archive(m_forward);
	archive(m_intensity);
}
SCENE_ARCHIVE_IMPL_INHERIT_END

SCENE_ARCHIVE_IMPL_INHERIT(SpotLightComponent, LightComponent)
{

}
SCENE_ARCHIVE_IMPL_INHERIT_END

SCENE_ARCHIVE_IMPL_INHERIT(DirectionalLightComponent, LightComponent)
{
	archive(m_percascadeDimXY);
	archive(m_cascadeCount);
	archive(m_shadowFilterSize);
	archive(m_maxFilterSize);
	archive(m_cascadeSplitLambda);
	archive(m_shadowBiasConst);
	archive(m_shadowBiasSlope);
	archive(m_cascadeBorderAdopt);
	archive(m_cascadeEdgeLerpThreshold);
	archive(m_maxDrawDepthDistance);
}
SCENE_ARCHIVE_IMPL_INHERIT_END

SCENE_ARCHIVE_IMPL_INHERIT(StaticMeshComponent, Component)
{
	archive(m_staticMeshUUID);
}
SCENE_ARCHIVE_IMPL_INHERIT_END

SCENE_ARCHIVE_IMPL_INHERIT(LandscapeComponent, Component)
{

}
SCENE_ARCHIVE_IMPL_INHERIT_END

SCENE_ARCHIVE_IMPL_INHERIT(PMXComponent, Component)
{

}
SCENE_ARCHIVE_IMPL_INHERIT_END

SCENE_ARCHIVE_IMPL(SceneNode)
{
	archive(m_bVisibility);
	archive(m_bStatic);
	archive(m_id);
	archive(m_runTimeIdName);
	archive(m_depth);
	archive(m_name);
	archive(m_parent);
	archive(m_scene);
	archive(m_components);
	archive(m_children);
}

SCENE_ARCHIVE_IMPL(Scene)
{
	archive(m_currentId);
	archive(m_root);
	archive(m_initName);
	archive(m_cacheSceneComponents);
	archive(m_nodeCount);
	archive(m_savePath);
}