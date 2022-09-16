#ifndef MATERIAL_H
#define MATERIAL_H

#include "Component.h"
#include "Vector3.h"

#include <map>
#include <string>
#include <vector>

class Texture;
class Material :
	public Component
{
public:
	Material();
	virtual ~Material();

	void SetManualDiffuse(Texture* diffuse_texture);
	void SetManualNormal(Texture* normal_texture);
	void SetManualDisp(Texture* disp_texture);
	void SetManualSpec(Texture* spec_texture);
	void SetManualColor(Vector3 color);

	//bool BindAll
	bool BindDiffuse(int index = 0);
	bool BindNormal(int index = 0);
	bool BindDisp(int index = 0);
	bool BindSpec(int index = 0);

	void CopySettings(Material* other);

	Vector3 color;
	bool colorOnly;
	float shininess;
	bool lighting;
	int tessel;

	bool normalMapEnable;
	bool parallaxMapEnable;
	bool specMapEnable;

	bool handledByMesh;

	std::vector<Texture*> diffuseTextures;
	std::vector<Texture*> normalTextures;
	std::vector<Texture*> dispTextures;
	std::vector<Texture*> specTextures;
	std::vector<Vector3> diffuseColors;
	std::vector<bool> diffuseOnly;
};

#endif