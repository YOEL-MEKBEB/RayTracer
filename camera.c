#include "camera.h"

void initialize_camera(Camera *camera, float viewOriginX, float viewOriginY, float viewOriginZ){
    // camera->viewOriginX = viewOriginX;
    // camera->viewOriginY = viewOriginY;
    // camera->viewOriginZ = viewOriginZ;
    initialize_vector(&camera->viewOrigin, viewOriginX, viewOriginY, viewOriginZ);
}

void setUpVector(Camera *camera, float upX, float upY, float upZ){
    // camera->upX = upX;
    // camera->upY = upY;
    // camera->upZ = upZ;
    Vector up;
    initialize_vector(&up, upX, upY, upZ);
    camera->upVector = normalize(&up);

}


void setViewingDirection(Camera *camera, float viewDirectionX, float viewDirectionY, float viewDirectionZ){
    // camera->viewDirectionX = viewDirectionX;
    // camera->viewDirectionY = viewDirectionY;
    // camera->viewDirectionZ = viewDirectionZ;
    Vector view;
    initialize_vector(&view, viewDirectionX, viewDirectionY, viewDirectionZ);
    camera->viewDirection = normalize(&view);
}

// set the horizontal field of view in degrees
void setHorizontalFOV(Camera* camera, float horizontalFOV){
    camera->horizontalFOV = horizontalFOV;
}

// set the vertical field of view in degrees
void setVericalFOV(Camera* camera, float verticalFOV){
    camera->verticalFOV = verticalFOV;
}

void defineImageCoordinates(Camera* camera){
    Vector horizontal = crossProduct(&camera->viewDirection, &camera->upVector);
    camera->u = normalize(&horizontal);

    Vector w = scalarVecMult(-1.0, &camera->viewDirection);
    Vector vertical = crossProduct(&camera->u, &w);
    camera->v = normalize(&vertical);

}

void setAspectRatio(Camera* camera, float width, float height){
    camera->aspectRatio = width/height;
}

void setViewingWindow(Camera* camera, float d){
    float width = 2*d*tan(camera->horizontalFOV/2);
    float height = 2*d*tan(camera->verticalFOV/2);

    Vector distance = scalarVecMult(d, &camera->viewDirection);
    Vector forward = vectorAdd(&camera->viewOrigin, &distance);
    
    Vector negWidth = scalarVecMult(-1* width/2, &camera->u);
    Vector posWidth = scalarVecMult(width/2, &camera->u);
    Vector negHeight = scalarVecMult(-1*height/2, &camera->v);
    Vector posHeight = scalarVecMult(height/2, &camera->v);




    Vector ULside = vectorAdd(&negWidth, &posHeight);
    Vector URside = vectorAdd(&posWidth, &posHeight);
    Vector LLside = vectorAdd(&negWidth, &negHeight);
    Vector LRside = vectorAdd(&posWidth, &negHeight);
    camera->upperLeftCorner = vectorAdd(&forward, &ULside);
    camera->upperRightCorner = vectorAdd(&forward, &URside);
    camera->lowerLeftCorner = vectorAdd(&forward, &LLside);
    camera->lowerRightCorner = vectorAdd(&forward, &LRside);
}

void printCamera(Camera* camera){
    printf("View Origin: (%f, %f, %f)\n", camera->viewOrigin.dx, camera->viewOrigin.dy, camera->viewOrigin.dz);
    printf("View Direction: (%f, %f, %f)\n", camera->viewDirection.dx,camera->viewDirection.dy,camera->viewDirection.dz);
    printf("Up Vector: (%f, %f, %f)\n", camera->upVector.dx, camera->upVector.dy, camera->upVector.dz);
    printf("horizontal field of view: %f\n", camera->horizontalFOV);
    printf("vertical field of view: %f\n", camera->verticalFOV);
    printf("horizontal direction of image: (%f, %f, %f)\n", camera->u.dx, camera->u.dy, camera->u.dz);
    printf("vertical direction of image: (%f, %f, %f)\n", camera->v.dx, camera->v.dy, camera->v.dz);

    printf("upperLeftCorner: (%f, %f, %f)\n", camera->upperLeftCorner.dx, camera->upperLeftCorner.dy, camera->upperLeftCorner.dz);
    printf("upperRightCorner: (%f, %f, %f)\n", camera->upperRightCorner.dx, camera->upperRightCorner.dy, camera->upperRightCorner.dz);
    printf("lowerLeftCorner: (%f, %f, %f)\n", camera->lowerLeftCorner.dx, camera->lowerLeftCorner.dy, camera->lowerLeftCorner.dz);
    printf("lowerRightCorner: (%f, %f, %f)\n", camera->lowerRightCorner.dx, camera->lowerRightCorner.dy, camera->lowerRightCorner.dz);
    
}