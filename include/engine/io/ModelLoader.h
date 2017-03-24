#ifndef MODELLOADER_H
#define MODELLODER_H

#include <string>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "engine/render/Mesh.h"

std::vector<Mesh> load_model(const std::string& path);

#endif
