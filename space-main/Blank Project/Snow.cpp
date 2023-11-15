#include "Snow.h"


Snow::Snow() {
	mesh = Mesh::LoadFromMeshFile("Sphere.msh");
	texture = SOIL_load_OGL_texture(TEXTUREDIR"snow.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);  //"https://www.pinterest.com/pin/snowflake-png-design-element--591941944777046557/"

	for (int i = 0; i < numParticles; i++) {
		Particle particle;
		particle.isAlive = true;
		particle.position = Vector3(rand() % 10000, 8000, rand() % 10000);
		float speed = (rand() % 30) + 8;
		particle.speed = Vector3(0, -speed, -3);
		particle_list.push_back(particle);
		SceneNode* rain_drop = new SceneNode();
		rain_drop->SetMesh(this->mesh);
		rain_drop->SetTexture(this->texture);
		rain_drop->SetTransform(Matrix4::Translation(particle.position));
		rain_drop->SetModelScale(Vector3(20, 20, 20));
		rain_drop->SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		rain_drop->SetBoundingRadius(5.0f);
		AddChild(rain_drop);
	}
}

void Snow::Update(float dt) {
	for (int i = 0; i < numParticles; i++) {
		if (children[i]->GetTransform().GetPositionVector().y <= 0) {
			children[i]->SetTransform(Matrix4::Translation(Vector3(rand() % 10000, 8000, rand() % 10000)));
			float speed = (rand() % 30) + 8;
			particle_list[i].speed = Vector3(0, -speed, 0);
		}
		children[i]->SetTransform(children[i]->GetTransform() * Matrix4::Translation(particle_list[i].speed));
	}
	SceneNode::Update(dt);
}