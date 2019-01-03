//
//  SMAAEffect.hpp
//  EARenderer
//
//  Created by Pavlo Muratov on 10.10.2018.
//  Copyright © 2018 MPO. All rights reserved.
//

#ifndef SMAAEffect_hpp
#define SMAAEffect_hpp

#include "PostprocessEffect.hpp"
#include "GLTexture2D.hpp"
#include "GLSLSMAAEdgeDetection.hpp"
#include "GLSLSMAABlendingWeightCalculation.hpp"
#include "GLSLSMAANeighborhoodBlending.hpp"

namespace EARenderer {

    class SMAAEffect : public PostprocessEffect {
    private:
        GLNormalizedTexture2D<GLTexture::Normalized::RG> mAreaTexture;
        GLNormalizedTexture2D<GLTexture::Normalized::R> mSearchTexture;
        GLFloatTexture2D<GLTexture::Float::RG16F> mEdgesTexture;
        GLFloatTexture2D<GLTexture::Float::RGBA16F> mBlendTexture;

        GLSLSMAAEdgeDetection mEdgeDetectionShader;
        GLSLSMAABlendingWeightCalculation mBlendingWeightCalculationShader;
        GLSLSMAANeighborhoodBlending mNeighborhoodBlendingShader;

        void detectEdges(std::shared_ptr<const PostprocessTexturePool::PostprocessTexture> image);

        void calculateBlendingWeights();

        void blendNeighbors(std::shared_ptr<const PostprocessTexturePool::PostprocessTexture> image,
                std::shared_ptr<PostprocessTexturePool::PostprocessTexture> outputImage);

    public:
        SMAAEffect(std::shared_ptr<GLFramebuffer> sharedFramebuffer, std::shared_ptr<PostprocessTexturePool> sharedTexturePool);

        void antialise(std::shared_ptr<const PostprocessTexturePool::PostprocessTexture> inputImage,
                std::shared_ptr<PostprocessTexturePool::PostprocessTexture> outputImage);
    };

}

#endif /* SMAAEffect_hpp */
