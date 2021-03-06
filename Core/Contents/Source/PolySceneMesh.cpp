/*
 Copyright (C) 2011 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include "PolySceneMesh.h"

using namespace Polycode;

SceneMesh::SceneMesh(String fileName) : SceneEntity(), texture(NULL), material(NULL) {
	mesh = new Mesh(fileName);
	bBoxRadius = mesh->getRadius();
	bBox = mesh->calculateBBox();
	skeleton = NULL;
	lightmapIndex=0;
	showVertexNormals = false;
	useVertexBuffer = false;
}

SceneMesh::SceneMesh(Mesh *mesh) : SceneEntity(), texture(NULL), material(NULL) {
	this->mesh = mesh;
	bBoxRadius = mesh->getRadius();
	bBox = mesh->calculateBBox();
	skeleton = NULL;
	lightmapIndex=0;
	showVertexNormals = false;	
	useVertexBuffer = false;	
}

SceneMesh::SceneMesh(int meshType) : texture(NULL), material(NULL) {
	mesh = new Mesh(meshType);
	bBoxRadius = mesh->getRadius();
	bBox = mesh->calculateBBox();
	skeleton = NULL;
	lightmapIndex=0;
	showVertexNormals = false;	
	useVertexBuffer = false;	
}

void SceneMesh::setMesh(Mesh *mesh) {
	this->mesh = mesh;
	bBoxRadius = mesh->getRadius();
	bBox = mesh->calculateBBox();
	showVertexNormals = false;	
	useVertexBuffer = false;	
}


SceneMesh::~SceneMesh() {
}

Mesh *SceneMesh::getMesh() {
	return mesh;
}

void SceneMesh::setTexture(Texture *texture) {
	this->texture = texture;
}

void SceneMesh::setMaterial(Material *material) {
	this->material = material;
	localShaderOptions = material->getShader(0)->createBinding();
}

void SceneMesh::setMaterialByName(String materialName) {
	Material *material =  (Material*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_MATERIAL, materialName);
	if(!material)
		return;
	setMaterial(material);
}

Texture *SceneMesh::getTexture() {
	return texture;
}


void SceneMesh::loadTexture(String fileName,bool clamp) {
	texture = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(fileName, clamp);
}

ShaderBinding *SceneMesh::getLocalShaderOptions() {
	return localShaderOptions;
}

void SceneMesh::loadSkeleton(String fileName) {
	skeleton = new Skeleton(fileName);
	addEntity(skeleton);
	
	setSkeleton(skeleton);
}

void SceneMesh::setSkeleton(Skeleton *skeleton) {
	this->skeleton = skeleton;
	for(int i=0; i < mesh->getPolygonCount(); i++) {
		Polygon *polygon = mesh->getPolygon(i);
		unsigned int vCount = polygon->getVertexCount();
		for(int j=0; j < vCount; j++) {
			Vertex *vertex = polygon->getVertex(j);
			for(int k=0; k < vertex->getNumBoneAssignments(); k++) {
				vertex->getBoneAssignment(k)->bone = skeleton->getBone(vertex->getBoneAssignment(k)->boneID);
			}
		}
	}	
}

Material *SceneMesh::getMaterial() {
	return material;
}

Skeleton *SceneMesh::getSkeleton() {
	return skeleton;
}

void SceneMesh::renderMeshLocally() {
	Renderer *renderer = CoreServices::getInstance()->getRenderer();
	
	if(skeleton) {	
		for(int i=0; i < mesh->getPolygonCount(); i++) {
			Polygon *polygon = mesh->getPolygon(i);			
			unsigned int vCount = polygon->getVertexCount();			
			for(int j=0; j < vCount; j++) {
				Vertex *vert = polygon->getVertex(j);
				Vector3 norm;
				
					Vector3 aPos = vert->restPosition;
					Vector3 tPos;
				
					Number mult = 0;
					for(int b =0; b < vert->getNumBoneAssignments(); b++) {
						BoneAssignment *bas = vert->getBoneAssignment(b);
						mult += bas->weight;
					}
					mult = 1.0f/mult;
				
					for(int b =0; b < vert->getNumBoneAssignments(); b++) {
						BoneAssignment *bas = vert->getBoneAssignment(b);
						Bone *bone = bas->bone;
						if(bone) {
							
							Matrix4 restMatrix = bone->getRestMatrix();
							Matrix4 finalMatrix = bone->getFinalMatrix();
							
							Vector3 vec = restMatrix * aPos;
							tPos += finalMatrix * vec * (bas->weight*mult);
							
							Vector3 nvec = vert->restNormal;
							nvec = restMatrix.rotateVector(nvec);
							nvec = finalMatrix.rotateVector(nvec);
							
							norm += nvec * (bas->weight*mult);
						}
					}					
					
				
					vert->x = tPos.x;
					vert->y = tPos.y;
					vert->z = tPos.z;				
				
					norm.Normalize();
					vert->setNormal(norm.x, norm.y, norm.z);
				
			}
		}
		mesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;		
		mesh->arrayDirtyMap[RenderDataArray::NORMAL_DATA_ARRAY] = true;		
	}

	if(mesh->useVertexColors) {
		renderer->pushDataArrayForMesh(mesh, RenderDataArray::COLOR_DATA_ARRAY);
	}
	 
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::VERTEX_DATA_ARRAY);
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::NORMAL_DATA_ARRAY);		
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::TEXCOORD_DATA_ARRAY);	
	
	renderer->drawArrays(mesh->getMeshType());
}

void SceneMesh::cacheToVertexBuffer(bool cache) {

	if(cache && !mesh->hasVertexBuffer()) {
		CoreServices::getInstance()->getRenderer()->createVertexBufferForMesh(mesh);
	}
	useVertexBuffer = cache;
}

void SceneMesh::Render() {
	
	Renderer *renderer = CoreServices::getInstance()->getRenderer();
	
	if(material) {
		renderer->applyMaterial(material, localShaderOptions,0);
	} else {
		if(texture)
			renderer->setTexture(texture);
		else
			renderer->setTexture(NULL);
	}
	
	if(useVertexBuffer) {
		renderer->drawVertexBuffer(mesh->getVertexBuffer());
	} else {
		renderMeshLocally();
	}
	
	if(material) 
		renderer->clearShader();
	
	if(showVertexNormals) {	
		renderer->setTexture(NULL);
		/*
		for(int i=0; i < mesh->getPolygonCount(); i++) {
			Polygon *polygon = mesh->getPolygon(i);			
			unsigned int vCount = polygon->getVertexCount();
			for(int j=0; j < vCount; j++) {
				Vertex *vert = polygon->getVertex(j);
				Vector3 norm = *vert->normal;				
				CoreServices::getInstance()->getRenderer()->draw3DLine(*vert, norm, 0.4f, Color(0.0f,0.7f,1.0f,0.5f));				
			}
		}
		 */
	}	
}