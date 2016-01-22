#include "Scene.h"


Scene::Scene(void)
{
	objects = ArrayList<ArrayList<GameObject>>();

	running = false;
	rendering = false;
}

Scene::~Scene(void)
{
}

Scene::Scene(const Scene &copy_me)
{
}

void Scene::operator = (const Scene &copy_me)
{
}

void Scene::Render()
{
	// For each layer...
	for(int i = 0; i < objects.GetLength(); i++)
	{
		// For each object....
		for(int j = 0; j < objects[i].GetLength(); j++)
		{
			// Render the object
			objects[i][j].Render(textures[objects[i][j].GetTextureID()].GetTextureID());
		}
	}
}

void Scene::Unload()
{
	for(int i = 0; i < textures.size(); i++)
	{
		textures[i].FreeTexture();
	}
	
	textures.clear();
}

void Scene::SetRenderLayers(int num_layers)
{
	objects = ArrayList<ArrayList<GameObject>>();

	// Fill the array with a number of empty layers
	for(int i = 0; i < num_layers; i++)
	{
		objects.Add(ArrayList<GameObject>());
	}

	return;
}