#include <Objects/GeometricObject.h>
#include <Objects/Triangle.h>

#include <vector>
#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

typedef std::vector<unsigned int> Index;

class Mesh : public GeometricObject 
{
public:
	Mesh(const std::string &modelPath);
	Mesh(const std::vector<Vertex> &vertex_list, const std::vector<Index>& index_list);
	void LoadObjFile(const std::string &modelPath);

	Mesh* clone() const override;

	bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
	bool shadow_hit(const Ray& ray, float& tmin) const override;
	BBox get_bounding_box() const override;

private:
	std::vector<Vertex> vertexList;
	std::vector<Index> indicesList;
	std::vector<GeometricObjectPtr> triangleList;

	class BVH* meshBVH;

	void ProcessNode(aiNode *node, const aiScene *scene);
	void ProcessMesh(aiMesh *mesh, const aiScene *scene);
	void SetupTriangleList();

};

typedef std::shared_ptr<Mesh> MeshPtr;