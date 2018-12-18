//
//  ResourcePool.cpp
//  EARenderer
//
//  Created by Pavlo Muratov on 26.10.2017.
//  Copyright © 2017 MPO. All rights reserved.
//

#include "ResourcePool.hpp"

namespace EARenderer {

#pragma mark - Lifecycle

    ResourcePool &ResourcePool::shared() {
        static ResourcePool pool;
        return pool;
    }

    ResourcePool::ResourcePool()
            :
            meshes(100),
            mCookTorranceMaterials(100),
            mEmissiveMaterials(100) {
    }

#pragma mark - Getters

    const GLVertexArray<Vertex1P1N2UV1T1BT> &ResourcePool::VAO() const {
        return mVAO;
    }

    int32_t ResourcePool::totalVertexCount() const {
        return mTotalVertexCount;
    }

#pragma mark -

    void ResourcePool::transferMeshesToGPU() {
        std::vector<Vertex1P1N2UV1T1BT> vertices;
        for (ID meshID : meshes) {
            Mesh &mesh = meshes[meshID];
            for (ID subMeshID : mesh.subMeshes()) {
                SubMesh &subMesh = mesh.subMeshes()[subMeshID];
                subMesh.setVBOOffset((int32_t) vertices.size());
                subMesh.setVertexCount((int32_t) subMesh.vertices().size());
                vertices.insert(vertices.end(), subMesh.vertices().begin(), subMesh.vertices().end());
            }
        }
        mVAO.initialize(vertices, {
                GLVertexAttribute::UniqueAttribute(sizeof(glm::vec4), glm::vec4::length()),
                GLVertexAttribute::UniqueAttribute(sizeof(glm::vec3), glm::vec3::length()),
                GLVertexAttribute::UniqueAttribute(sizeof(glm::vec2), glm::vec2::length()),
                GLVertexAttribute::UniqueAttribute(sizeof(glm::vec3), glm::vec3::length()),
                GLVertexAttribute::UniqueAttribute(sizeof(glm::vec3), glm::vec3::length()),
                GLVertexAttribute::UniqueAttribute(sizeof(glm::vec3), glm::vec3::length())
        });
    }

    MaterialReference ResourcePool::addMaterial(CookTorranceMaterial &&material) {
        ID id = mCookTorranceMaterials.insert(std::move(material));
        return std::make_pair(MaterialType::CookTorrance, id);
    }

    MaterialReference ResourcePool::addMaterial(EmissiveMaterial &&material) {
        ID id = mEmissiveMaterials.insert(std::move(material));
        return std::make_pair(MaterialType::Emissive, id);
    }

    const CookTorranceMaterial &ResourcePool::cookTorranceMaterial(ID materialID) const {
        return mCookTorranceMaterials[materialID];
    }

    const EmissiveMaterial &ResourcePool::emissiveMaterial(ID materialID) const {
        return mEmissiveMaterials[materialID];
    }

}
