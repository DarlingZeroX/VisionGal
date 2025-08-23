#pragma once
#include <vector>
#include "Mesh.h"

VISIONGAL_GFX_NAMESPACE_BEGIN

class Sprite
{
public:
	Sprite();
	Sprite(Sprite& mesh) = delete;
	Sprite& operator=(Sprite& mesh) = delete;
	virtual ~Sprite() = default;

	StaticMesh* GetMesh() { return m_Mesh.get(); }

private:
	void Initialize();
private:
	std::vector<float> m_Vertices;

	std::unique_ptr<StaticMesh> m_Mesh;
};

VISIONGAL_GFX_NAMESPACE_END
