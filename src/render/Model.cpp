#include "Model.h"
#include "Log.h"

#include "glm/gtc/matrix_transform.hpp"

glm::mat4 Model::getModelMatrix()
{
	glm::mat4 res;

	res = glm::translate(res, pos);
	res = glm::scale(res, glm::vec3(scale));
	
	res = glm::rotate(res, glm::radians(rot.x), glm::vec3(1, 0, 0));
	res = glm::rotate(res, glm::radians(rot.y), glm::vec3(0, 1, 0));
	res = glm::rotate(res, glm::radians(rot.z), glm::vec3(0, 0, 1));

	return res;
}

void Model::loadModel(std::string path)
{
	log(LogLevel::INFO) << "loading model: " << path;

	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

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

/* TODO: move the stb_image stuff to an implementation file and
 * move the OpenGL stuff to a wrapper class */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
GLuint load_gl_texture(std::string path)
{
	int width, height, bpp;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &bpp, 3);
	std::cout << "path: " << path << ", image dimensions: " << width << ", " << height << "\n";

	GLuint texture_id;

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	stbi_image_free(data);

	return texture_id;
}

std::vector<std::string> loaded_textures;

std::vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);

		Texture texture;
		bool should_load_texture = true;
		std::string path = "res/model/tex/" + std::string(str.C_Str());

		for (int i = 0; i < loaded_textures.size(); i++) {
			if (loaded_textures[i] == path) {
				should_load_texture = false;
				break;
			}
		}

		if (should_load_texture) {
			GLuint texture_id = load_gl_texture(path);
			//std::cout << "requesting texture: " << std::string(str.C_Str()) << std::endl;
			std::cout << "texture_id: " << texture_id << std::endl;

			texture.id = texture_id;
			texture.type = typeName;
			textures.push_back(texture);
			loaded_textures.push_back(path);
		}
	}

	return textures;
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
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
