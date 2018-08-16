#include <Objects/Mesh.h>
#include<iostream>
#include <Objects/BVH.h>


Mesh::Mesh(const std::string & modelPath)
{
	LoadObjFile(modelPath);
}

Mesh::Mesh(const std::vector<Vertex> &vertex_list, const std::vector<Index>& index_list):
	vertexList(vertex_list), indicesList(index_list)
{
	SetupTriangleList();
}


void Mesh::LoadObjFile(const std::string& modelPath) 
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(modelPath,
		aiProcess_Triangulate |
		aiProcess_OptimizeMeshes |
		aiProcess_JoinIdenticalVertices |
		aiProcess_RemoveComponent);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		exit(1);
		//return;
	}

	// retrieve the directory path of the filepath
	std::string directory = modelPath.substr(0, modelPath.find_last_of('/'));

	// process ASSIMP's root node recursively
	ProcessNode(scene->mRootNode, scene);

	auto m_NumOfVert = static_cast<uint32_t >(vertexList.size());
	std::cout << "Num of Vertices : " << m_NumOfVert << std::endl;

	SetupTriangleList();
}

Mesh * Mesh::clone() const
{
	return (new Mesh(*this));
}

bool Mesh::hit(const Ray & ray, double & tmin, ShadeRec& sr) const
{
	bool meshHit = false;
	meshHit = meshBVH->hit(ray, tmin, sr);

//	for (const auto &i : triangleList)
//	{
//		double t = kHugeValue;
//		ShadeRec tempShaderRecord(sr.mW);
//		const bool triangleHit = i->hit(ray, t, tempShaderRecord);
//
//		if (triangleHit) {
//			if (t < tmin) {
//				tmin = t;
//			    sr = tempShaderRecord;
//				meshHit = true;
//			}
//		}
//	}
	return meshHit;
}

bool Mesh::shadow_hit(const Ray & ray, float & tmin) const
{
	bool triangleHit = false;
	triangleHit = meshBVH->shadow_hit(ray, tmin);
//	for (const auto &i : triangleList)
//	{
//		auto t = (float) kHugeValue;
//		auto hit = i->shadow_hit(ray, t);
//
//		if (hit) {
//			if (t < tmin) {
//				tmin = t;
//				triangleHit = true;
//			}
//		}
//	}
	return triangleHit;
}

BBox Mesh::get_bounding_box() const
{
	BBox bounding_box =  triangleList[0]->get_bounding_box();
	for (auto i = 1; i < triangleList.size(); i++)
	{
		bounding_box = bounding_box.expand(triangleList[i]->get_bounding_box());
	}

	return bounding_box;
}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void Mesh::ProcessNode(aiNode *node, const aiScene *scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene.
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

void Mesh::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex tempVertex;

		//Vertex vertex;
		Point3D tempVec; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first positions
		tempVec.x = mesh->mVertices[i].x;
		tempVec.y = mesh->mVertices[i].y;
		tempVec.z = mesh->mVertices[i].z;

		tempVertex.position = tempVec;

		// normals
		if (mesh->mNormals) // does the mesh contain Normal
		{
			tempVec.x = mesh->mNormals[i].x;
			tempVec.y = mesh->mNormals[i].y;
			tempVec.z = mesh->mNormals[i].z;
			tempVertex.normal = tempVec;
		}
		else
		{
			tempVertex.normal = tempVertex.position - Point3D(0, 0, 0);
			tempVertex.normal.normalize();
		}

		vertexList.push_back(tempVertex);
	}

	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		Index faceIndex;
		for (uint32_t j = 0; j < face.mNumIndices; j++) {
			faceIndex.push_back(face.mIndices[j]);
		}
		indicesList.push_back(faceIndex);
	}
}

void Mesh::SetupTriangleList()
{
	for (auto &i : indicesList)
	{
		TrianglePtr tempTriangle(new Triangle(vertexList[i[0]], vertexList[i[1]], vertexList[i[2]]));
        tempTriangle->set_material(material_ptr);
		triangleList.push_back(tempTriangle);
	}

	meshBVH = new BVH(&triangleList[0], static_cast<int>(triangleList.size()));
}
