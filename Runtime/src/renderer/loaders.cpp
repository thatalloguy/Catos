////
//// Created by allos on 1/18/2025.
////
//
//#include "loaders.h"
//#include "stl/vector.h"
//
//#include <fastgltf/core.hpp>
//#include <fastgltf/util.hpp>
//
//
//
//static catos::Texture* loadTexture(fastgltf::Asset& gltf, fastgltf::Image& image, std::filesystem::path full_path ) {
//
//    catos::Texture* out = new catos::Texture{};
//
//    catos::TextureCreationInfo out_create{};
//
//    std::visit(fastgltf::visitor {
//            [](auto& arg) { spdlog::warn("Unknown image prod."); },
//            [&](fastgltf::sources::URI& filePath) {
//                assert(filePath.fileByteOffset == 0);
//                assert(filePath.uri.isLocalPath());
//
//
//                std::string path(filePath.uri.path().begin(), filePath.uri.path().end());
//
//                auto rel_path = full_path.string() + "/" + path;
//
//                spdlog::info("TEX: {}", rel_path.c_str());
//
//                out_create.source.path = rel_path.c_str();
//                out->init(out_create);
//            },
//            [&](fastgltf::sources::Array& vector) {
//
//                out_create.source.buffer = vector.bytes.data();
//                out_create.source.buf_len = vector.bytes.size();
//
//                out->init(out_create);
//            },
//            [&](fastgltf::sources::BufferView& view) {
//                auto& bufferView = gltf.bufferViews[view.bufferViewIndex];
//                auto& buffer = gltf.buffers[bufferView.bufferIndex];
//                std::visit(fastgltf::visitor {
//                        [](auto& arg) { spdlog::warn("Unknown image prod."); },
//                        [&](fastgltf::sources::Array& vector) {
//
//                            out_create.source.buffer = vector.bytes.data() + bufferView.byteOffset;
//                            out_create.source.buf_len = (int) bufferView.byteLength;
//
//                            out->init(out_create);
//                        }
//                }, buffer.data);
//            },
//    }, image.data);
//
//    return out;
//}
//
//bool catos::loaders::loadGLTF(std::filesystem::path filePath, catos::LoadedMesh* out_mesh) {
//
//    if (!exists(filePath)) {
//        spdlog::error("Could not find gltf file: {}", filePath.string());
//        return false;
//    }
//
//    spdlog::info("Starting to load: {}", filePath.string());
//
//    static constexpr auto supportedExtensions =
//            fastgltf::Extensions::KHR_mesh_quantization |
//            fastgltf::Extensions::KHR_texture_transform |
//            fastgltf::Extensions::KHR_materials_variants;
//
//    fastgltf::Parser parser{};
//
//    constexpr auto gltfOptions = fastgltf::Options::DontRequireValidAssetMember |
//                                 fastgltf::Options::AllowDouble |
//                                 fastgltf::Options::LoadGLBBuffers |
//                                 fastgltf::Options::LoadExternalBuffers;
//
//    fastgltf::GltfDataBuffer data;
//    data.loadFromFile(filePath);
//
//    fastgltf::Asset gltf;
//
//    auto type = fastgltf::determineGltfFileType(&data);
//
//    if (type == fastgltf::GltfType::glTF) {
//        auto load = parser.loadGltf(&data, filePath.parent_path(), gltfOptions);
//
//        if (load) {
//            gltf = std::move(load.get());
//        } else {
//            spdlog::error("Failed to load gltf: {}", fastgltf::to_underlying(load.error()));
//            return false;
//        }
//    } else if (type == fastgltf::GltfType::GLB) {
//        auto load = parser.loadGltfBinary(&data, filePath.parent_path(), gltfOptions);
//
//        if (load) {
//            gltf = std::move(load.get());
//        } else {
//            spdlog::error("Failed to load gltf: {}", fastgltf::to_underlying(load.error()));
//            return false;
//        }
//    } else {
//        spdlog::error("Failed to load gltf: could not determine gltf type");
//        return false;
//    }
//
//    out_mesh->meshes.reserve(gltf.meshes.size() + 2);
//    for (auto& image: gltf.images) {
//
//        Texture* tex  = loadTexture(gltf, gltf.images.front(), filePath.parent_path());
//
//        if (tex->getSize().getX() <= 0) {
//            spdlog::warn("Invalid texture");
//        }
//
//        if (out_mesh->tex != nullptr) {
//            delete out_mesh->tex;
//        }
//
//
//        out_mesh->tex = tex;
//
//    }
//
//
//    for (auto mesh: gltf.meshes) {
//
//        RawMesh out{};
//
//        catos::vector<std::uint32_t> indices{};
//        catos::vector<Vertex> vertices{};
//
//        unsigned int VAO;
//        unsigned int VBO;
//        unsigned int EBO;
//
//        for (auto primitive: mesh.primitives) {
//
//            int initial_vtx = vertices.length();
//
//
//            auto& index_accessor = gltf.accessors[primitive.indicesAccessor.value()];
//            indices.reserve(index_accessor.count);
//
//
//            fastgltf::iterateAccessor<std::uint32_t>(gltf, index_accessor, [&](std::uint32_t id){
//                indices.push_back(id);
//            });
//
//
//
//            fastgltf::Accessor& pos_accessor = gltf.accessors[primitive.findAttribute("POSITION")->second];
//
//            vertices.reserve(pos_accessor.count);
//
//            fastgltf::iterateAccessorWithIndex<Vector3i>(gltf, pos_accessor, [&](Vector3i v, size_t index){
//                Vertex new_vtx{};
//                new_vtx.position = v;
//
//                new_vtx.normal = { 0.0f, 1.0f, 0.0f};
//
//                new_vtx.uv = {0.0f, 0.0f};
//
//                vertices[index] = new_vtx;
//            });
//
//            auto normal_accessor = primitive.findAttribute("NORMAL");
//            if (normal_accessor != primitive.attributes.end()) {
//                fastgltf::iterateAccessorWithIndex<Vector3i>(gltf, gltf.accessors[(*normal_accessor).second], [&](Vector3i n, size_t index) {
//                    vertices[index].normal = n;
//                });
//            }
//
//            auto uv_accessor = primitive.findAttribute("TEXCOORD_0");
//            if (uv_accessor != primitive.attributes.end()) {
//
//                fastgltf::iterateAccessorWithIndex<Vector2i>(gltf, gltf.accessors[(*uv_accessor).second], [&](Vector2i uv, size_t index) {
//                    vertices[index].uv = uv;
//                    spdlog::info("UV {} | {} {}", index, vertices[index].uv.x, vertices[index].uv.y);
//                });
//
//            }
//
//            {
//
//                glGenVertexArrays(1, &VAO);
//                glGenBuffers(1, &VBO);
//                glGenBuffers(1, &EBO);
//
//                glBindVertexArray(VAO);
//
//                glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//                glBufferData(GL_ARRAY_BUFFER, vertices.length() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
//
//                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.length() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//
//                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//                glEnableVertexAttribArray(0);
//
//                // normals
//                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
//                glEnableVertexAttribArray(1);
//
//                // tex_coords
//                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
//                glEnableVertexAttribArray(2);
//
//                glBindVertexArray(0);
//            }
//
//            out.count = vertices.length();
//            out.indices_count = indices.length();
//            out.VAO = VAO;
//            out.VBO = VBO;
//            out.EBO = EBO;
//
//            out.vertices = vertices;
//            out.indices = indices;
//        }
//
//        out_mesh->meshes.push_back(out);
//    }
//    spdlog::debug("LOADED MESH :D");
//    return true;
//}