#include "Graphics.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include "MainSystem.h"
#include "GBuffer.h"
#include "ShadowMapFBO.h"
#include "ssaobuffer.h"
#include "PPBuffer.h"
#include "PingPongFBO.h"
#include "Texture.h"
#include "Skybox.h"

using namespace std;

#define QUAD Asset.GetModel("QUAD")
#define SPHERE Asset.GetModel("SPHERE")
#define UNBINDTEXTURE glBindTexture(GL_TEXTURE_2D, 0);
#define UNBINDFB glBindFramebuffer(GL_FRAMEBUFFER, 0);

Graphics::Graphics() :
lightSystem(NULL),
gbuffer(NULL),
shadowMapFBO(NULL),
ssaoBuffer(NULL),
ppBuffer(NULL),
pingpongFBO(NULL)
{
	lightSystem = MainSystem::Instance().lightSystem;
}

Graphics::~Graphics()
{
	if (gbuffer != NULL)
	{
		delete gbuffer;
		gbuffer = NULL;
	}

	if (shadowMapFBO != NULL)
	{
		delete shadowMapFBO;
		shadowMapFBO = NULL;
	}

	if (ssaoBuffer != NULL)
	{
		delete ssaoBuffer;
		ssaoBuffer = NULL;
	}
}

void Graphics::Init(void)
{
	this->WindowWidth = App.WindowWidth();
	this->WindowHeight = App.WindowHeight();

	graphicSettings = GraphicSettings();

	InitBuffers();
	GetShaders();
	InitShaders();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Graphics::GetShaders()
{
	preProcessShader = ShaderStorage::Instance().shader;
	dirLightShader = ShaderStorage::Instance().dirLightShader;
	pointLightShader = ShaderStorage::Instance().pointLightShader;
	gPassShader = ShaderStorage::Instance().gPassShader;
	nullShader = ShaderStorage::Instance().nullShader;
	shadowShader = ShaderStorage::Instance().shadowShader;
	ssaoShader = ShaderStorage::Instance().ssaoShader;
	ssaoBlurShader = ShaderStorage::Instance().ssaoBlurShader;
	hdrShader = ShaderStorage::Instance().hdrShader;
	gaussianBlurShader = ShaderStorage::Instance().gaussianBlurShader;
	skyBoxShader = ShaderStorage::Instance().skyboxShader;
	forwardShader = ShaderStorage::Instance().forwardShader;
}

void Graphics::InitShaders()
{
	// Shaders
	gPassShader->Start();
	gPassShader->load_DiffuseTextureUnit(0);
	gPassShader->load_NormalTextureUnit(1);
	gPassShader->load_DispTextureUnit(2);
	gPassShader->Stop();

	preProcessShader->Start();
	preProcessShader->load_ScreenSize(WindowWidth, WindowHeight);
	preProcessShader->load_TextureUnit(POSITION_TEXTURE_UNIT_INDEX);
	preProcessShader->Stop();

	pointLightShader->Start();
	pointLightShader->load_ScreenSize(WindowWidth, WindowHeight);
	pointLightShader->load_TextureIndex(POSITION_TEXTURE_UNIT_INDEX, COLOR_TEXTURE_UNIT_INDEX, NORMAL_TEXTURE_UNIT_INDEX, 4);
	pointLightShader->Stop();

	dirLightShader->Start();
	dirLightShader->load_ScreenSize(WindowWidth, WindowHeight);
	dirLightShader->load_TextureIndex(POSITION_TEXTURE_UNIT_INDEX, COLOR_TEXTURE_UNIT_INDEX, NORMAL_TEXTURE_UNIT_INDEX);
	dirLightShader->load_ShadowMapTextureUnit(4);
	dirLightShader->load_AOTextureUnit(5);
	dirLightShader->load_EnableAO(graphicSettings.ssao);
	dirLightShader->load_EnableShadow(graphicSettings.shadow);
	dirLightShader->Stop();

	ssaoShader->Start();
	ssaoShader->load_ScreenSize((float)this->WindowWidth, (float)this->WindowHeight);
	ssaoShader->load_TextureUnit(0, 1, 2);
	ssaoShader->load_SampleKernel(ssaoBuffer->ssaoKernel);
	ssaoShader->Stop();

	ssaoBlurShader->Start();
	ssaoBlurShader->load_SSAOTexUnit(0);
	ssaoBlurShader->load_ScreenSize((float)this->WindowWidth, (float)this->WindowHeight);
	ssaoBlurShader->Stop();

	hdrShader->Start();
	hdrShader->load_TextureUnit(0);
	hdrShader->load_BloomBlurUnit(1);
	hdrShader->load_ScreenSize(this->WindowWidth, this->WindowHeight);
	hdrShader->Stop();

	gaussianBlurShader->Start();
	gaussianBlurShader->load_TextureUnit(0);
	gaussianBlurShader->load_ScreenSize(this->WindowWidth, this->WindowHeight);
	gaussianBlurShader->Stop();

	skyBoxShader->Start();
	skyBoxShader->load_TextureUnit(0);
	skyBoxShader->Stop();

	forwardShader->Start();
	forwardShader->load_CubeMapTextureUnit(1);
	forwardShader->Stop();
}

void Graphics::InitBuffers()
{
	// Create FBOs
	gbuffer = new GBuffer();
	gbuffer->Init(this->WindowWidth, this->WindowHeight);

	shadowMapFBO = new ShadowMapFBO();
	shadowMapFBO->Init(this->WindowWidth, this->WindowHeight);

	ssaoBuffer = new ssaobuffer();
	ssaoBuffer->Init(this->WindowWidth, this->WindowHeight);

	ppBuffer = new PPBuffer();
	ppBuffer->Init(this->WindowWidth, this->WindowHeight);

	pingpongFBO = new PingPongBuffer();
	pingpongFBO->Init(this->WindowWidth, this->WindowHeight);
}

void Graphics::Render(Camera* camera, vector<Entity*> entities)
{
	Matrix4f perspective;
	if (camera != NULL)
	{
		perspective.SetToPerspective(camera->fov, 4.0 / 3.0, camera->near, camera->far);
	}
	else
	{
		perspective.SetToPerspective(50.0, 4.0 / 3.0, 0.1, 1000.0);
	}

	Matrix4f Lightperspective;
	Lightperspective.SetToOrtho(-25.0f, 25.0f, -25.0f, 25.0f, 1.0f, 45.5f);
	
	if (graphicSettings.shadow)
	{
		ShadowMapPass(Lightperspective, entities);
	}

	gbuffer->StartFrame();

	// Geometry Pass
	GeometryPass(camera, perspective, entities);

	if (graphicSettings.ssao)
	{
		SSAOPass(perspective);
		SSAOBlurPass();
	}

	if (graphicSettings.pointLight)
	{
		// Point Light Pass
		vector<PointLight*> pointLights = lightSystem->GetPointLights();

		// Load before point light loop; efficiency
		nullShader->Start();
		nullShader->load_ViewMatrix(camera->ViewMat());
		nullShader->load_ProjectionMatrix(perspective);
		nullShader->Stop();

		pointLightShader->Start();
		pointLightShader->load_ViewPosition(camera->position);
		pointLightShader->load_ProjectionMatrix(perspective);
		pointLightShader->load_ViewMatrix(camera->ViewMat());
		//pointLightShader->load_InverseView(camera->ViewMat().GetInverse());
		pointLightShader->Stop();

		glEnable(GL_STENCIL_TEST);
		for (unsigned i = 0; i < pointLights.size(); ++i)
		{
			// Stencil Pass
			StencilPass(pointLights[i]);

			// Point Light Pass
			PointLightPass(pointLights[i]);
		}
		glDisable(GL_STENCIL_TEST);
	}

	// Dir Light Pass ( Last one )
	if (graphicSettings.directionalLight)
	{
		DirLightPass(camera, Lightperspective);
	}

	// Post processing from here
	// Forward pass
	ForwardPass(camera, perspective);

	if (graphicSettings.bloom)
	{
		BloomPass();
	}

	FinalPass();

	// UI ( final )
	UIPass(camera, perspective);
}

void Graphics::ShadowMapPass(Matrix4f Lightperspective, vector<Entity*> &entities)
{
	shadowMapFBO->BindForWriting();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	glClear(GL_DEPTH_BUFFER_BIT);

	shadowShader->Start();

	DirectionLight* dLight = lightSystem->GetDirLight();

	shadowShader->load_ProjectionMatrix(Lightperspective);
	shadowShader->load_ViewMatrix(dLight->GetViewMat());

	for (auto &e : entities)
	{
		shadowShader->load_ModelMatrix(e->transform->TransformMat());
		MeshRenderer* renderer = e->GetComponent<MeshRenderer>();
		if (renderer != NULL)
		{
			if (renderer->IsActive())
			{
				renderer->DrawMeshOnly();
			}
		}
	}

	shadowShader->Stop();
	glCullFace(GL_BACK);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);	
}

void Graphics::GeometryPass(Camera* camera, Matrix4f perspective, vector<Entity*> &entities)
{
	gbuffer->BindForGeoPass();

	glEnable(GL_DEPTH_TEST);

	glDepthMask(GL_TRUE);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_BLEND);

	glEnable(GL_CULL_FACE); 
	glCullFace(GL_BACK);

	gPassShader->Start();

	gPassShader->load_ProjectionMatrix(perspective);
	gPassShader->load_ViewMatrix(camera->ViewMat());
	gPassShader->load_ProjectionNear((float)camera->near);
	gPassShader->load_ProjectionFar((float)camera->far);
	gPassShader->load_ViewPosition(camera->position);

	gPassShader->load_Gamma(graphicSettings.gamma);

	for (auto &e : entities)
	{
		gPassShader->load_ModelMatrix(e->transform->TransformMat());
		// To Do: Calculate normal matrix in C++ and pass to shader
		// gPassShader->load_NormalMatrix(e->transform->TransformMat().mat)

		MeshRenderer* renderer = e->GetComponent<MeshRenderer>();
		if (renderer != NULL)
		{
			if (renderer->IsActive())
			{
				renderer->Draw(gPassShader);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}
	}

	gPassShader->Stop();

	glDepthMask(GL_FALSE);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	gbuffer->Unbind();
}

void Graphics::SSAOPass(Matrix4f &Projection)
{
	ssaoShader->Start();

	ssaoBuffer->BindSSAO();

	//gbuffer->BindForSSAOPass();		// texture binding -- position and normal

	ssaoShader->load_TextureUnit(0, 1, 2);
	gbuffer->BindTexture(GL_TEXTURE0, GBuffer::GBUFFER_TEXTURE_TYPE_POSITIONVIEW);	// bind position in view space
	gbuffer->BindTexture(GL_TEXTURE1, GBuffer::GBUFFER_TEXTURE_TYPE_NORMALVIEW);	// bind normal in view space
	ssaoBuffer->BindForSSAOPass();		// bind noise texture

	ssaoShader->load_ProjectionMatrix(Projection);

	QUAD->RenderMeshOnly();

	ssaoShader->Stop();

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Graphics::SSAOBlurPass(void)
{
	ssaoBuffer->BindSSAOBlur();
	ssaoBlurShader->Start();
	ssaoBuffer->BindSSAOColor();
	QUAD->RenderMeshOnly();
	ssaoBlurShader->Stop();

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Graphics::StencilPass(PointLight* pointLight)
{
	nullShader->Start();

	gbuffer->BindForStencilPass();

	glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

	glClear(GL_STENCIL_BUFFER_BIT);

	glStencilFunc(GL_ALWAYS, 0, 0);

	glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

	nullShader->load_ModelMatrix(pointLight->GetTransformMat());

	Asset.GetModel("SPHERE")->RenderMeshOnly();

	gbuffer->Unbind();
	nullShader->Stop();
}

void Graphics::PointLightPass(PointLight* pointLight)
{
	gbuffer->BindForLightPass();

	// Point Light Pass
	pointLightShader->Start();

	glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	pointLightShader->load_PointLight(pointLight);

	pointLightShader->load_ModelMatrix(pointLight->GetTransformMat());
	//pointLightShader->load_MatSpecularIntensity(material->specularIntensity);
	//pointLightShader->load_MatSpecularPower(material->specularPower);
	ssaoBuffer->BindSSAOColorBlur();

	Asset.GetModel("SPHERE")->RenderMeshOnly();

	glCullFace(GL_BACK);

	glDisable(GL_BLEND);

	gbuffer->Unbind();
	pointLightShader->Stop();
}

void Graphics::DirLightPass(Camera* camera, Matrix4f Lightperspective)
{
	dirLightShader->Start();
	gbuffer->BindForLightPass();

	if (graphicSettings.shadow)
	{
		dirLightShader->load_EnableShadow(true);
		dirLightShader->load_ShadowMapTextureUnit(3);
		shadowMapFBO->BindForReading(GL_TEXTURE3);
	}
	else
	{
		dirLightShader->load_EnableShadow(false);
	}

	if (graphicSettings.ssao)
	{
		dirLightShader->load_EnableAO(true);
		dirLightShader->load_AOTextureUnit(4);
		ssaoBuffer->BindSSAOColorBlur();
	}
	else
	{
		dirLightShader->load_EnableAO(false);
	}

	dirLightShader->load_ViewPosition(camera->position);
	DirectionLight* dLight = lightSystem->GetDirLight();
	if (dLight != NULL)
	{
		dirLightShader->load_DirectionalLight(dLight);
	}

	dirLightShader->load_InverseViewMatrix(camera->ViewMat().GetInverse());

	dirLightShader->load_LightViewMatrix(dLight->GetViewMat());
	dirLightShader->load_LightProjectionMatrix(Lightperspective);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	QUAD->RenderMeshOnly();

	glDisable(GL_BLEND);

	gbuffer->Unbind();
	dirLightShader->Stop();
}

void Graphics::ForwardPass(Camera* camera, Matrix4f perspective)
{
	// Forward Rendering
	gbuffer->BindForForwardPass();
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
	// Render Objects
	forwardShader->Start();

	vector<PointLight*> pointLights = lightSystem->GetPointLights();

	forwardShader->load_ProjectionMatrix(perspective);
	forwardShader->load_ViewMatrix(camera->ViewMat());
	forwardShader->load_ViewPos(camera->position);

	// Render Point Lights
	forwardShader->load_ColorEnabled(true);
	
	for (unsigned i = 0; i < pointLights.size(); ++i)
	{
		Vector3 translate = pointLights[i]->transform->worldposition;
		Matrix4f t;
		t.SetToTranslation(translate.x, translate.y, translate.z);
		forwardShader->load_ModelMatrix(t);
		forwardShader->load_Color(pointLights[i]->color * 10.f);

		//Asset.GetModel("CUBE")->RenderMeshOnly();
	}

	forwardShader->load_ColorEnabled(false);

	// Then Render other forward objects
	Matrix4f t;
	t.SetToTranslation(0, -5, -30);
	forwardShader->load_ModelMatrix(t);
	Asset.GetTexture("SKYBOX_TEXTURE")->Bind(GL_TEXTURE1);
	Asset.GetModel("NANOSUIT")->RenderMeshOnly();

	forwardShader->Stop();

	// Render skybox
	skyBoxShader->Start();
	glDisable(GL_CULL_FACE);
	Matrix4f id, scale;
	id.SetToIdentity();
	id.SetToScale(800, 800, 800);
	skyBoxShader->load_ModelMatrix(id);
	skyBoxShader->load_ViewMatrix(camera->ViewMat());
	skyBoxShader->load_ProjectionMatrix(perspective);

	Asset.GetTexture("SKYBOX_TEXTURE")->Bind(GL_TEXTURE0);

	Asset.GetSkyboxModel()->Render();

	skyBoxShader->Stop();

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Render to post process buffer for post processing
	ppBuffer->StartFrame();

	preProcessShader->Start();
	gbuffer->BindForFinalPass();
	//gbuffer->BindTexture(GL_TEXTURE0, GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	//shadowMapFBO->BindForReading(GL_TEXTURE0);
	//blurBuffer->BindForReading(GL_TEXTURE0);
	//ssaoBuffer->BindSSAOColor();
	//ssaoBuffer->BindForSSAOPass();

	QUAD->RenderMeshOnly();

	preProcessShader->Stop();

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Old Blit Method
	/*gbuffer->BindForFinalPass();
	glBlitFramebuffer(0, 0, WindowWidth, WindowHeight,
		0, 0, WindowWidth, WindowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);*/
}

void Graphics::BloomPass()
{
	// Bloom Blur
	bool horizontal = true;
	bool firstIteration = true;
	unsigned amount = 10;

	gaussianBlurShader->Start();

	gaussianBlurShader->load_TextureUnit(0);

	for (unsigned i = 0; i < amount; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO->pingpongFBO[horizontal]);

		gaussianBlurShader->load_HorizontalBlur(horizontal);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, firstIteration ? ppBuffer->GetBrightTexture() : pingpongFBO->pingpongBuffer[!horizontal]); 

		QUAD->RenderMeshOnly();
		horizontal = !horizontal;

		if (firstIteration)
		{
			firstIteration = false;
		}
	}

	gaussianBlurShader->Stop();

	UNBINDTEXTURE;
	UNBINDFB;
}

void Graphics::FinalPass(void)
{
	hdrShader->Start();

	hdrShader->load_TextureUnit(0);
	ppBuffer->BindTexture(GL_TEXTURE0, PPBuffer::PPBUFFER_TEXTURE_TYPE_COLOR);
	//gbuffer->BindTexture(GL_TEXTURE0, GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	hdrShader->load_BloomBlurUnit(1);
	pingpongFBO->BindFinalBlur(GL_TEXTURE1);

	hdrShader->load_Gamma(graphicSettings.gamma);
	hdrShader->load_Bloom(graphicSettings.bloom);
	hdrShader->load_Exposure(graphicSettings.exposure);

	QUAD->RenderMeshOnly();

	hdrShader->Stop();

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Graphics::UIPass(Camera* camera, Matrix4f perspective)
{
	/*gbuffer->BindForForwardBlit();
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, WindowWidth, WindowHeight, 0, 0, WindowWidth, WindowHeight,
		GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glEnable(GL_DEPTH_TEST);

	skyBoxShader->Start();
	glDisable(GL_CULL_FACE);
	Matrix4f id, scale;
	id.SetToIdentity();
	id.SetToScale(1, 1, 1);
	skyBoxShader->load_ModelMatrix(id);
	skyBoxShader->load_ViewMatrix(camera->ViewMat());
	skyBoxShader->load_ProjectionMatrix(perspective);

	Asset.GetTexture("SKYBOX_TEXTURE")->Bind(GL_TEXTURE0);
	
	Asset.GetSkyboxModel()->Render();

	skyBoxShader->Stop();*/
}
