#include "camera.h"

int initialize_camera(Camera *camera, float viewOriginX, float viewOriginY, float viewOriginZ) {
    // camera->viewOriginX = viewOriginX;
    // camera->viewOriginY = viewOriginY;
    // camera->viewOriginZ = viewOriginZ;
    return initialize_vector(&camera->viewOrigin, viewOriginX, viewOriginY, viewOriginZ);
}

int setUpVector(Camera *camera, float upX, float upY, float upZ) {
    // camera->upX = upX;
    // camera->upY = upY;
    // camera->upZ = upZ;
    Vector up;
    if(initialize_vector(&up, upX, upY, upZ) == -1){
      printf("up Vector contains a non number value\n");
      return -1;
    }
    if (vectorLength(&up) == 0) {
        return -1;
    }
    camera->upVector = normalize(&up);
    return 0;
}

int setViewingDirection(Camera *camera, float viewDirectionX, float viewDirectionY,
                        float viewDirectionZ) {
    // camera->viewDirectionX = viewDirectionX;
    // camera->viewDirectionY = viewDirectionY;
    // camera->viewDirectionZ = viewDirectionZ;
    Vector view;
    if(initialize_vector(&view, viewDirectionX, viewDirectionY, viewDirectionZ)==-1){
      printf("up vector conatains a non number value\n");
      return -1;
    }
    if (vectorLength(&view) == 0) {
        return -1;
    }
    camera->viewDirection = normalize(&view);
    return 0;
}

// set the horizontal field of view in degrees
int setHorizontalFOV(Camera *camera, float horizontalFOV) {
    if(isnan(horizontalFOV)){
      return -1;
    }
    camera->horizontalFOV = horizontalFOV;
    return 0;
}

// set the vertical field of view in degrees
int setVericalFOV(Camera *camera, float verticalFOV) {
    if(isnan(verticalFOV)){
      return -1;
    }
    camera->verticalFOV = verticalFOV;
    return 0;
}

void defineImageCoordinates(Camera *camera) {
    Vector horizontal = crossProduct(&camera->viewDirection, &camera->upVector);
    camera->u = normalize(&horizontal);

    // still don't understand why positive viewing direction works?
    Vector w = scalarVecMult(1.0, &camera->viewDirection);
    Vector vertical = crossProduct(&camera->u, &w);
    camera->v = normalize(&vertical);
}

int setAspectRatio(Camera *camera, float width, float height) {
    if(width == NAN || height == NAN){
      return -1;
    }
    camera->aspectRatio = width / height;
    return 0;
}

void setViewingWindow(Camera *camera, float d) {
    float height = 2 * d * tan(camera->verticalFOV / 2);

    float width = camera->aspectRatio * height;

    Vector distance = scalarVecMult(d, &camera->viewDirection);
    Vector forward = vectorAdd(&camera->viewOrigin, &distance);

    Vector negWidth = scalarVecMult(-1 * width / 2, &camera->u);
    Vector posWidth = scalarVecMult(width / 2, &camera->u);
    Vector negHeight = scalarVecMult(-1 * height / 2, &camera->v);
    Vector posHeight = scalarVecMult(height / 2, &camera->v);

    // printf("negWidth: (%f, %f, %f)\n", negWidth.dx, negWidth.dy, negWidth.dz);

    Vector ULside = vectorAdd(&negWidth, &posHeight);
    Vector URside = vectorAdd(&posWidth, &posHeight);
    Vector LLside = vectorAdd(&negWidth, &negHeight);
    Vector LRside = vectorAdd(&posWidth, &negHeight);
    camera->upperLeftCorner = vectorAdd(&forward, &ULside);
    camera->upperRightCorner = vectorAdd(&forward, &URside);
    camera->lowerLeftCorner = vectorAdd(&forward, &LLside);
    camera->lowerRightCorner = vectorAdd(&forward, &LRside);
}

void printCamera(Camera *camera) {
    printf("View Origin: (%f, %f, %f)\n", camera->viewOrigin.dx, camera->viewOrigin.dy,
           camera->viewOrigin.dz);
    printf("View Direction: (%f, %f, %f)\n", camera->viewDirection.dx, camera->viewDirection.dy,
           camera->viewDirection.dz);
    printf("Up Vector: (%f, %f, %f)\n", camera->upVector.dx, camera->upVector.dy,
           camera->upVector.dz);
    printf("horizontal field of view: %f\n", camera->horizontalFOV);
    printf("vertical field of view: %f\n", camera->verticalFOV);
    printf("horizontal direction of image: (%f, %f, %f)\n", camera->u.dx, camera->u.dy,
           camera->u.dz);
    printf("vertical direction of image: (%f, %f, %f)\n", camera->v.dx, camera->v.dy, camera->v.dz);

    printf("upperLeftCorner: (%f, %f, %f)\n", camera->upperLeftCorner.dx,
           camera->upperLeftCorner.dy, camera->upperLeftCorner.dz);
    printf("upperRightCorner: (%f, %f, %f)\n", camera->upperRightCorner.dx,
           camera->upperRightCorner.dy, camera->upperRightCorner.dz);
    printf("lowerLeftCorner: (%f, %f, %f)\n", camera->lowerLeftCorner.dx,
           camera->lowerLeftCorner.dy, camera->lowerLeftCorner.dz);
    printf("lowerRightCorner: (%f, %f, %f)\n", camera->lowerRightCorner.dx,
           camera->lowerRightCorner.dy, camera->lowerRightCorner.dz);
}
