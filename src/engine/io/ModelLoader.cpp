#include "ModelLoader.h"

#include "Texture.h"
#include "Log.h"
#include "stb_image.h"

std::vector<std::string> loaded_textures;

std::vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);

		bool should_load_texture = true;
		std::string path = "res/model/tex/" + std::string(str.C_Str());

		for (int i = 0; i < loaded_textures.size(); i++) {
			if (loaded_textures[i] == path) {
				should_load_texture = false;
				break;
			}
		}

		if (should_load_texture) {
			Texture texture(path);
			textures.push_back(texture);
			loaded_textures.push_back(path);
		}
	}

	return textures;
}

Mesh process_mesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	if (!(mesh->mNormals)) {
		log(LogLevel::WARNING) << "model does not contain normal data.";
	}

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
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
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return Mesh(vertices, indices, textures);
}

void process_node(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		log(LogLevel::DEBUG1) << "processing mesh with " << mesh->mNumVertices << " vertices.";
		meshes.push_back(process_mesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		process_node(node->mChildren[i], scene, meshes);
	}
}

std::vector<Mesh> load_model(const std::string& path)
{
	log(LogLevel::INFO) << "loading model: " << path;

	std::vector<Mesh> meshes;
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		log(LogLevel::WARNING) << "assimp failed to load model: " << import.GetErrorString();
		return meshes; /* use an exception? */
	}

	process_node(scene->mRootNode, scene, meshes);

	log(LogLevel::INFO) << "finished loading model";

	return meshes;
}
