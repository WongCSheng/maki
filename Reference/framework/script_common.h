#include "Asset.h"
#include "Input.h"
#include "Entity.h"
#include "App.h"
#include "Debugger.h"

// Components
#include "Transform.h"
#include "Mesh.h"
#include "MeshF.h"
#include "FirstPersonCamera.h"
#include "Material.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "MeshRenderer.h"

#include "Quaternion.h"
#include "Matrix4f.h"

#define Asset Asset::Instance()
#define Input Input::Instance()
#define App App::Instance()
#define Debug Debugger::Instance()

#define POSITION_TEXTURE_UNIT_INDEX 0
#define COLOR_TEXTURE_UNIT_INDEX 1
#define NORMAL_TEXTURE_UNIT_INDEX 2

#define POSITION_TEXTURE_UNIT GL_TEXTURE0
#define COLOR_TEXTURE_UNIT GL_TEXTURE1
#define NORMAL_TEXTURE_UNIT GL_TEXTURE2

// Shadow Texture Unit Index for Directional Light Pass
#define SHADOW_TEXTURE_UNIT_INDEX 3
// Shadow Texture Unit for Directional Light Pass
#define SHADOW_TEXTURE_UNIT GL_TEXTURE3

// SSAO Texture Unit Index for Directional Light Pass
#define SSAO_TEXTURE_UNIT_INDEX 4
// SSAO Texture Unit for Directional Light Pass
#define SSAO_TEXTURE_UNIT GL_TEXTURE4

// Noise Texture Unit Index for SSAO Pass
#define NOISE_TEXTURE_UNIT_INDEX 2
// Noise Texture Unit for SSAO Pass
#define NOISE_TEXTURE_UNIT GL_TEXTURE2