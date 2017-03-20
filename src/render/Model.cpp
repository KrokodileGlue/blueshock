#include "Model.h"
#include "Log.h"

void Model::loadModel(std::string path)
{
	log(LogLevel::INFO) << "loading model: " << path;

	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		log(LogLevel::WARNING) << "assimp failed to load model: " << import.GetErrorString();
		return;
	}

	processNode(scene->mRootNode, scene);
	
	log(LogLevel::INFO) << "finished loading model";
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		std::cout << "processing mesh with " << mesh->mNumVertices << " vertices.\n";
		meshes.push_back(processMesh(mesh, scene)); /* crash... */
	}
	
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	if (!(mesh->mNormals)) {
		log(LogLevel::WARNING) << "model does not contain normal data.";
	}

	for (int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.pos = vector;

		//std::cout << vector.x << ", " << vector.y << ", " << vector.z << std::endl;

		if (mesh->mNormals) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.tex_coord = vec;
		}
		else
			vertex.tex_coord = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	if (mesh->mMaterialIndex >= 0) {
		
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return Mesh(vertices, indices, textures);
}
