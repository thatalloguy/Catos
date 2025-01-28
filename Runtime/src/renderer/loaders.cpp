//
// Created by allos on 1/18/2025.
//

#include "loaders.h"
#include "stl/vector.h"


#include <fastgltf/tools.hpp>
#include <fastgltf/core.hpp>
#include <fastgltf/util.hpp>

namespace fastgltf {


    template<>
    struct fastgltf::ElementTraits<Vector3i> : ElementTraitsBase<Vector3i, AccessorType::Vec3, float> {};

    template<>
    struct fastgltf::ElementTraits<Vector2i> : ElementTraitsBase<Vector2i, AccessorType::Vec2, float> {};


}
/*

static bool loadMesh(fastgltf::Asset& asset, fastgltf::Mesh& mesh, catos::LoadedMesh& mesh_out) {

    catos::RawMesh raw_out{};

    raw_out.primitives.resize(mesh.primitives.size());

    for (auto it = mesh.primitives.begin(); it != mesh.primitives.end(); ++it) {

        auto position_iterator = it->findAttribute("POSITION");
        assert(position_iterator != it->attributes.end());
        assert(it->indicesAccessor.has_value());


        auto index = std::distance(mesh.primitives.begin(), it);
        spdlog::info("INDEX {} {}", index, raw_out.primitives.length());
        auto& primitive = raw_out.primitives[index];

        glGenVertexArrays(1, &primitive.VAO);
        glBindVertexArray( primitive.VAO);

        uint32_t base_col_texcoord_index = 0;


        primitive.primitive_type = fastgltf::to_underlying(it->type);

        primitive.mat_uniform_index = 0;

        {
            auto& position_accessor = asset.accessors[position_iterator->second];

            if (!position_accessor.bufferViewIndex.has_value())
                continue;

                glGenBuffers(1, &primitive.VBO);
                glBindBuffer(GL_ARRAY_BUFFER, primitive.EBO);


                primitive.vertices.resize(position_accessor.count);

                fastgltf::iterateAccessorWithIndex<Vector3i>(asset, position_accessor, [&](Vector3i position, size_t idx){
                    primitive.vertices[idx].x = position.x;
                    primitive.vertices[idx].y = position.y;
                    primitive.vertices[idx].z = position.z;

                    primitive.vertices[idx].r = 0.0f;
                    primitive.vertices[idx].g = 1.0f;
                    primitive.vertices[idx].b = 0.0f;

                    primitive.vertices[idx].uv_x = 0.0f;
                    primitive.vertices[idx].uv_y = 0.0f;

                });

                spdlog::info("U {} {}", primitive.vertices.length(), position_accessor.count);

                glBufferData(primitive.VBO, position_accessor.count * sizeof(catos::Vertex), primitive.vertices.data(), GL_STATIC_DRAW);



            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(catos::Vertex), (void*)0);
            glEnableVertexAttribArray(0);

            // normals
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(catos::Vertex), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // tex_coords
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(catos::Vertex), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

        }

        auto& draw = primitive.draw;
        draw.instance_count = 1;
        draw.base_instance = 0;
        draw.base_vertex = 0;
        draw.first_index = 0;

        auto& index_accessor = asset.accessors[it->indicesAccessor.value()];

        if (!index_accessor.bufferViewIndex.has_value())
            return false;

        draw.count = (uint32_t) index_accessor.count;

        glGenBuffers(1, &primitive.EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, primitive.EBO);

        primitive.indices.reserve(index_accessor.count);
        fastgltf::copyFromAccessor<uint32_t>(asset, index_accessor, primitive.indices.data());

        glBufferData(primitive.EBO, index_accessor.count * sizeof(uint32_t), primitive.indices.data(), GL_STATIC_DRAW);

        primitive.index_type = GL_UNSIGNED_INT;
    }

    mesh_out.meshes.push_back(raw_out);

    return true;
}
*/

bool catos::loaders::loadGLTF(std::filesystem::path filePath, catos::LoadedMesh* out_mesh) {

    if (!exists(filePath)) {
        spdlog::error("Could not find gltf file: {}", filePath.string());
        return false;
    }

    spdlog::info("Starting to load: {}", filePath.string());

    static constexpr auto supportedExtensions =
            fastgltf::Extensions::KHR_mesh_quantization |
            fastgltf::Extensions::KHR_texture_transform |
            fastgltf::Extensions::KHR_materials_variants;

    fastgltf::Parser parser(supportedExtensions);

    constexpr auto gltfOptions =
            fastgltf::Options::DontRequireValidAssetMember |
            fastgltf::Options::AllowDouble |
            fastgltf::Options::LoadGLBBuffers |
            fastgltf::Options::LoadExternalBuffers |
            fastgltf::Options::LoadExternalImages |
            fastgltf::Options::GenerateMeshIndices;

    fastgltf::GltfDataBuffer data;
    data.loadFromFile(filePath);

    fastgltf::Asset gltf;

    auto type = fastgltf::determineGltfFileType(&data);

    if (type == fastgltf::GltfType::glTF) {
        auto load = parser.loadGltf(&data, filePath.parent_path(), gltfOptions);

        if (load) {
            gltf = std::move(load.get());
        } else {
            spdlog::error("Failed to load gltf: {}", fastgltf::to_underlying(load.error()));
            return false;
        }
    } else if (type == fastgltf::GltfType::GLB) {
        auto load = parser.loadGltfBinary(&data, filePath.parent_path(), gltfOptions);

        if (load) {
            gltf = std::move(load.get());
        } else {
            spdlog::error("Failed to load gltf: {}", fastgltf::to_underlying(load.error()));
            return false;
        }
    } else {
        spdlog::error("Failed to load gltf: could not determine gltf type");
        return false;
    }

    out_mesh->meshes.reserve(gltf.meshes.size() + 2);


    for (auto mesh: gltf.meshes) {

        RawMesh out{};

        catos::vector<uint32_t> indices{};
        catos::vector<Vertex> vertices{};

        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        for (auto primitive: mesh.primitives) {

            int initial_vtx = vertices.length();


            auto& index_accessor = gltf.accessors[primitive.indicesAccessor.value()];
            indices.reserve(index_accessor.count);

            spdlog::info("index_accessor.count {}", index_accessor.count);

            fastgltf::iterateAccessor<uint32_t>(gltf, index_accessor, [&](uint32_t id){
                    indices.push_back(id);
            });



            fastgltf::Accessor& pos_accessor = gltf.accessors[primitive.findAttribute("POSITION")->second];

            vertices.reserve(pos_accessor.count);

            fastgltf::iterateAccessorWithIndex<Vector3i>(gltf, pos_accessor, [&](Vector3i v, size_t index){
                Vertex new_vtx{};
                new_vtx.position = v;

                new_vtx.normal = { 0.0f, 1.0f, 0.0f};

                new_vtx.uv_x = 0.0f;
                new_vtx.uv_y = 0.0f;

                vertices[index] = new_vtx;
            });

            auto normal_accessor = primitive.findAttribute("NORMAL");
            if (normal_accessor != primitive.attributes.end()) {
                fastgltf::iterateAccessorWithIndex<Vector3i>(gltf, gltf.accessors[(*normal_accessor).second], [&](Vector3i n, size_t index) {
                    vertices[index].normal = n;
                });
            }

            auto uv_accessor = primitive.findAttribute("TEXCOORD_0");
            if (uv_accessor != primitive.attributes.end()) {

                fastgltf::iterateAccessorWithIndex<Vector2i>(gltf, gltf.accessors[(*uv_accessor).second], [&](Vector2i uv, size_t index) {
                    vertices[index].uv_x = uv.x;
                    vertices[index].uv_y = uv.y;
                });

            }

            {

                glGenVertexArrays(1, &VAO);
                glGenBuffers(1, &VBO);
                glGenBuffers(1, &EBO);

                glBindVertexArray(VAO);

                glBindBuffer(GL_ARRAY_BUFFER, VBO);

                glBufferData(GL_ARRAY_BUFFER, vertices.length() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.length() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
                glEnableVertexAttribArray(0);

                // normals
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
                glEnableVertexAttribArray(1);

                // tex_coords
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
                glEnableVertexAttribArray(2);

                glBindVertexArray(0);
            }

            out.count = vertices.length();
            out.indices_count = indices.length();
            out.VAO = VAO;
            out.VBO = VBO;
            out.EBO = EBO;

            out.vertices = vertices;
            out.indices = indices;
        }

        out_mesh->meshes.push_back(out);
    }
    spdlog::info("LOADED MESH :D");
    return true;
}
