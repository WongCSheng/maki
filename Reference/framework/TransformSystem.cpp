#include "TransformSystem.h"
#include "Entity.h"
#include "Transform.h"

TransformSystem::TransformSystem()
{
	root = new Entity();
}


TransformSystem::~TransformSystem()
{
}

void TransformSystem::RegisterComponents(const std::vector<Entity*> &entities)
{
	for (int i = 0; i < entities.size(); ++i)
	{
		Transform* transform = entities[i]->GetComponent<Transform>();
		if (transform != NULL)
		{
			// If entity does not have a parent, add it to the scene root
			if (transform->parent == NULL)
			{
				root->AddChild(entities[i]);
			}
		}
	}
}

void TransformSystem::Update(const double dt)
{
	UpdateTransformation(root->transform);
}

void TransformSystem::UpdateTransformation(Transform* trans)
{
	Transform *t = trans;

	if (trans->remove)
	{
		RemoveFromTree(t);
	}
	else
	{
		if (t->parent != NULL)
		{
			t->worldposition = t->localposition + t->parent->worldposition;
			t->worldrotation = t->localrotation * t->parent->worldrotation;
			t->worldscale.x = t->localscale.x * t->parent->worldscale.x;
			t->worldscale.y = t->localscale.y * t->parent->worldscale.y;
			t->worldscale.z = t->localscale.z * t->parent->worldscale.z;
		}
		else
		{
			t->worldposition = t->localposition;
			t->worldrotation = t->localrotation;
			t->worldscale = t->localscale;
		}

		t->T.SetToTranslation(t->worldposition.x, t->worldposition.y, t->worldposition.z);
		t->R = t->worldrotation.convertTomat4();
		t->S.SetToScale(t->worldscale.x, t->worldscale.y, t->worldscale.z);

		t->Top = t->T * t->R * t->S;

		//t->forward = (t->localrotation * DEFAULTFORWARD);

		for (int i = 0; i < trans->children.size(); ++i)
		{
			UpdateTransformation(trans->children[i]);
		}
	}
}

void TransformSystem::CheckForNewComponents(void)
{
	
}

void TransformSystem::RemoveFromTree(Transform* transform)
{
	for (int i = 0; i < transform->children.size(); ++i)
	{
		RemoveFromTree(transform->children[i]);
	}
	transform->parent->children.clear();
	delete transform;
	transform = NULL;
}
