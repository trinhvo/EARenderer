//
//  DemoScene1.h
//  EARenderer
//
//  Created by Pavlo Muratov on 26.10.2017.
//  Copyright © 2017 MPO. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "DemoSceneComposing.h"

#import <glm/vec3.hpp>

@interface DemoScene1 : NSObject <DemoSceneComposing>

@property(assign, nonatomic, readonly) EARenderer::ID sphereMeshInstanceID;

@end
