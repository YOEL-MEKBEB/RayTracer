#include "colorType.h"

#include "light.h"
#include "ray.h"
#include "shapes.h"
#include "stdlib.h"
#include "vecList.h"
#include "vector.h"
#include <math.h>
#include <string.h>

void initializeColorType(ColorType *color, float r, float g, float b) {
    color->r = r;
    color->g = g;
    color->b = b;
}

ColorType traceRay(RayType *ray, SphereType **sphereArray, int sizeOfArray,
                   ColorType *backgroundColor, Light** light, int numberOfLights, vec_list *vertices, tri_list *faces, vec_list* normals, tex_list *textures) {
    
    // printf("%d\n", sizeOfArray);
    //


    SphereType *sphere;
    float A;
    float B;
    float C;


    // fix issue where sizOfArray could affect it
    float t[sizeOfArray];
    float t_faces[faces->length];

    Vector pointOfintersection;
    // printRay(ray);

    ColorType color;
    int minIndex = 0;
    int minFaceIndex = 0;
    for (int i = 0; i < sizeOfArray; i++) {
        sphere = sphereArray[i];

        A = pow(ray->dx, 2) + pow(ray->dy, 2) + pow(ray->dz, 2);
        if (A == 0) {
            printf("ray has a 0 vector for it's direction");
            initializeColorType(&color, -1, -1, -1);
            return color;
        }
        B = 2 * (ray->x - sphere->x) * ray->dx + 2 * (ray->y - sphere->y) * ray->dy +
            2 * (ray->z - sphere->z) * ray->dz;
        C = pow((ray->x - sphere->x), 2) + pow((ray->y - sphere->y), 2) +
            pow((ray->z - sphere->z), 2) - pow((sphere->radius), 2);

        if ((pow(B, 2) - 4 * A * C) < 0) {
            t[i] = -1;
            continue;
            // return *backgroundColor;
        } else if ((pow(B, 2) - 4 * A * C) == 0) {
            t[i] = (-1 * B) / (2 * A);


        } else {
            float t1 = (-1 * B + sqrt((pow(B, 2) - 4 * A * C))) / (2 * A);
            float t2 = (-1 * B - sqrt((pow(B, 2) - 4 * A * C))) / (2 * A);

            if (t1 < 0 && t2 < 0) {
                t[i] = -1;
                continue;
            } else if (t1 < 0 && t2 > 0) {
                t[i] = t2;
            } else if (t1 > 0 && t2 < 0) {
                t[i] = t1;
            } else {
                if (t1 < t2) {
                    t[i] = t1;
                } else {
                    t[i] = t2;
                }
            }
 

        }
    }

    Vector normal;
    float alphaList[faces->length];
    float betaList[faces->length];
    float gammaList[faces->length];

    for (int i = 1; i < faces->length + 1; i++){
        // printf("entered faces loop\n");
        Triangle *triangle = tri_list_get(faces, i);

        int index1 = (int) triangle->face.dx;
        int index2 = (int) triangle->face.dy;
        int index3 = (int) triangle->face.dz;

        Vector *vertex1 = vec_list_get(vertices, index1);
        Vector *vertex2 = vec_list_get(vertices, index2);
        Vector *vertex3 = vec_list_get(vertices, index3);

        Vector negVertex1 = scalarVecMult(-1, vertex1);

        Vector vector1 = vectorAdd(vertex2, &negVertex1); 
        Vector vector2 = vectorAdd(vertex3, &negVertex1); 
        
        normal = crossProduct(&vector1, &vector2);

        // printVector(&normal);

        A = normal.dx;
        B = normal.dy;
        C = normal.dz;
        
        float D = -1 * (A * vertex1->dx + B * vertex1->dy + C * vertex1->dz);

        float denominator = A * ray->dx + B * ray->dy + C * ray->dz;

        if(denominator == 0){
            t_faces[i-1] = -1;
            continue;
        }

        float numerator = -1 * (A * ray->x + B * ray->y + C * ray->z + D);
        float t = numerator/denominator;

        // printf("t: %f\n", t);

        // calculating barycentric coordinates


        Vector tempPoint;
        
        if(initialize_vector(&tempPoint, ray->x + t * ray->dx, ray->y + t * ray->dy,
                              ray->z + t * ray->dz) == -1){
             printf("surface point creation in trace ray is not working");
        }


        
        // printf("tempPoint: ");
        // printVector(&tempPoint);
        Vector e_p = vectorAdd(&tempPoint, &negVertex1);

        // printf("e_p: ");
        // printVector(&e_p);
        
        float d11 = dotProduct(&vector1, &vector1);
        float d12 = dotProduct(&vector1, &vector2);
        float d22 = dotProduct(&vector2, &vector2);
        float d1p = dotProduct(&vector1, &e_p);
        float d2p = dotProduct(&vector2, &e_p);

        float det = (d11 * d22) - (d12 * d12);

        float beta = (d22*d1p - d12*d2p)/det;
        float gamma = (d11*d2p - d12*d1p)/det;
        float alpha = 1 - beta - gamma;

        // if(alpha >x 0 && beta > 0 && gamma > 0){
            
        // printf("alpha: %f\n", alpha);
        // printf("beta: %f\n", beta);
        // printf("gamma: %f\n", gamma);
        // }

        alphaList[i-1] = alpha;
        betaList[i-1] = beta;
        gammaList[i-1] = gamma;
        

        if(t < 0){
            t_faces[i-1] = -1;
        }else if(alpha < 0 || beta < 0 || gamma < 0){
            t_faces[i-1] = -1;
        }else{
            t_faces[i-1] = t;
        }
        
    } 
    normal = normalize(&normal);


    // printf("outside of loop\n" );
    
    // extracting the closest point of intersection of sphere
    for (int i = 0; i < sizeOfArray; i++) {
        if (t[i] > -1 && t[minIndex] == -1) {
            minIndex = i;
        }
    
        if (t[i] < t[minIndex] && t[i] > -1) {
            minIndex = i;
        }
    }

    // extracting the closest point of intersection of triangle
    for (int i = 0; i < faces->length; i++){
        if(t_faces[i] > -1 && t_faces[minFaceIndex] == -1){
            minFaceIndex = i;
        }
        if (t_faces[i] < t_faces[minFaceIndex] && t_faces[i] > -1){
            minFaceIndex = i;
        }
    }


    

    
     if ((t[minIndex] == -1 || sizeOfArray == 0) && t_faces[minFaceIndex] == -1) {
        return *backgroundColor;
    }else if(sizeOfArray == 0 && t_faces[minFaceIndex] != -1){



            Triangle *triangle = tri_list_get(faces, minFaceIndex + 1);

            if(triangle->isSmoothShaded){
                initialize_vector(&normal, alphaList[minFaceIndex], betaList[minFaceIndex], gammaList[minFaceIndex]);
            }        
            // printf("entered case 0\n");
            if(initialize_vector(&pointOfintersection, ray->x + t_faces[minFaceIndex] * ray->dx, ray->y + t_faces[minFaceIndex] * ray->dy,
                             ray->z + t_faces[minFaceIndex] * ray->dz) == -1){
                printf("surface point creation in trace ray is not working");
            }


            // printVector(&pointOfintersection);
        color = shadeRay("triangle", NULL, triangle, ray, &pointOfintersection, light, numberOfLights, sphereArray, sizeOfArray, &normal, normals, textures);
        
    }else if(faces->length <= 0){
            // printf("entered case 1\n");
            if(initialize_vector(&pointOfintersection, ray->x + t[minIndex] * ray->dx, ray->y + t[minIndex] * ray->dy,
                              ray->z + t[minIndex] * ray->dz) == -1){
                printf("surface point creation in trace ray is not working");
            }
            color = shadeRay("Sphere", sphereArray[minIndex], NULL, ray, &pointOfintersection, light, numberOfLights, sphereArray, sizeOfArray, &normal, normals, textures);
    } else if(t[minIndex] == -1 && t_faces[minFaceIndex] > -1){
        
            printf("entered case 2\n");
            if(initialize_vector(&pointOfintersection, ray->x + t_faces[minFaceIndex] * ray->dx, ray->y + t_faces[minFaceIndex] * ray->dy,
                             ray->z + t_faces[minFaceIndex] * ray->dz) == -1){
                printf("surface point creation in trace ray is not working");
            }


            printVector(&pointOfintersection);
        color = shadeRay("triangle", NULL, tri_list_get(faces, minIndex + 1), ray, &pointOfintersection, light, numberOfLights, sphereArray, sizeOfArray, &normal, normals, textures);
    }else if (t[minIndex] > -1 && t_faces[minFaceIndex] == -1){
        
            printf("entered case 3\n");
            // printf("%f\n", t[minIndex]);
            // printf("%f\n", t_faces[minFaceIndex]);
        if(initialize_vector(&pointOfintersection, ray->x + t[minIndex] * ray->dx, ray->y + t[minIndex] * ray->dy,
                              ray->z + t[minIndex] * ray->dz) == -1){
                printf("surface point creation in trace ray is not working");
        }
        color = shadeRay("Sphere", sphereArray[minIndex], NULL, ray, &pointOfintersection, light, numberOfLights, sphereArray, sizeOfArray, &normal, normals, textures);
    } else{
            printf("entered case 4\n");
        if(t[minIndex] < t_faces[minFaceIndex]){
        
            if(initialize_vector(&pointOfintersection, ray->x + t[minIndex] * ray->dx, ray->y + t[minIndex] * ray->dy,
                              ray->z + t[minIndex] * ray->dz) == -1){
                printf("surface point creation in trace ray is not working");
            }
            color = shadeRay("Sphere", sphereArray[minIndex], NULL, ray, &pointOfintersection, light, numberOfLights, sphereArray, sizeOfArray, &normal, normals,textures);
        }
    }
    return color;
}

ColorType shadeRay(char* objectType, SphereType* sphere, Triangle *triangle, RayType *ray,  Vector *surfacePoint,  Light** lightArray, int numberOfLights, SphereType** sphereArray, int sizeOfArray, Vector *normalCoord, vec_list* normals, tex_list* textures){


    ColorType color;
    if(strcmp(objectType, "triangle") == 0){
        color = shadeTriangle(triangle, ray, surfacePoint, lightArray, numberOfLights, normalCoord, normals);
        return color;
    }
    Vector intrinsicColor;
    Vector specularColor;
    Vector negSphereCenter;
    // Vector sphereSurface;
    Vector rayOrigin;
    Vector diffuseTerm;
    Vector V;
    Vector L[numberOfLights];
    Vector H[numberOfLights];
    float attenuationFactor[numberOfLights];

    



    if(initialize_vector(&negSphereCenter, -1 * sphere->x, -1 * sphere->y, -1 * sphere->z) == -1){
        printf("it died");
    }
    
    Vector rN = vectorAdd(surfacePoint, &negSphereCenter);
    Vector N = scalarVecMult(1.0/sphere->radius, &rN);

    if(initialize_vector(&rayOrigin, ray->x, ray->y, ray->z) == -1){
        printf("rayOrigin vector creation ruined in shadeRay");
            initializeColorType(&color, -1, -1, -1);
            return color;
    }
    Vector negSphereSurface = scalarVecMult(-1.0, surfacePoint);


    for(int i = 0; i < numberOfLights; i++){
        if(lightArray[i]->isPoint){
            L[i] = vectorAdd(&lightArray[i]->lightLocation, &negSphereSurface);
            float distance = vectorLength(&L[i]);
            if(lightArray[i]->isAttenuated){
                attenuationFactor[i] = 1/(lightArray[i]->c1 + lightArray[i]->c2 * distance + lightArray[i]->c3 * pow(distance, 2));
            }else{
                attenuationFactor[i] = 1.0;
            }

            L[i] = normalize(&L[i]);
        }else{
            L[i] = scalarVecMult(-1, &lightArray[i]->lightLocation);
            attenuationFactor[i] = 1.0;
            L[i] = normalize(&L[i]);
        }
        
    }  

    int shadowFlag[numberOfLights];
    for(int j=0; j<numberOfLights; j++){
    
        RayType lightRay;
        initializeRayType(&lightRay, surfacePoint->dx,surfacePoint->dy,  surfacePoint->dz);
        setDirection(&lightRay, L[j].dx, L[j].dy, L[j].dz);
        
        float A = 0.0; 
        float B = 0.0;
        float C = 0.0;
        SphereType* obstructingSphere;
        float t;
        shadowFlag[j] = 1;
        for (int i = 0; i < sizeOfArray; i++){

            obstructingSphere = sphereArray[i];
            A = pow(lightRay.dx, 2) + pow(lightRay.dy, 2) + pow(lightRay.dz, 2);
            if (A == 0) {
                printf("light has a 0 vector for it's direction");
                initializeColorType(&color, -1, -1, -1);
                return color;
            }
            B = 2 * (lightRay.x - obstructingSphere->x) * lightRay.dx + 2 * (lightRay.y - obstructingSphere->y) * lightRay.dy +
                2 * (lightRay.z - obstructingSphere->z) * lightRay.dz;
            C = pow((lightRay.x - obstructingSphere->x), 2) + pow((lightRay.y - obstructingSphere->y), 2) +
                pow((lightRay.z - obstructingSphere->z), 2) - pow((obstructingSphere->radius), 2);

            if ((pow(B, 2) - 4 * A * C) < 0) {
                    continue;
                // return *backgroundColor;
            } else if ((pow(B, 2) - 4 * A * C) == 0) {
                t = (-1 * B) / (2 * A);
                
                                
            } else {
                float t1 = (-1 * B + sqrt((pow(B, 2) - 4 * A * C))) / (2 * A);
                float t2 = (-1 * B - sqrt((pow(B, 2) - 4 * A * C))) / (2 * A);
                if(t1 < t2){
                    t = t1;
                }else{
                    t = t2;
                }
            }

            if(t <= 0){
                continue;
            }else{
                shadowFlag[j] = 0;
                break;
            }
        }

    }

    // printf("L: ");
    // printVector(&L);
    
    Vector sumOfLights;
    initialize_vector(&sumOfLights, 0.0, 0.0, 0.0);
    V = vectorAdd(&rayOrigin, &negSphereSurface);
    V = normalize(&V);

    // printf("V: ");
    // printVector(&V);
    //
    //
    if(sphere->useTexture){

        // parametrize sphere for use with texture map
        float phi = acos((surfacePoint->dz - sphere->z)/sphere->radius);
        float theta = atan2(surfacePoint->dy - sphere->y, surfacePoint->dx - sphere->x);



        // ensures theta is from 0 to 2pi
        if(theta < 0){
            theta += (2 *M_PI);
        }
        
        float v = phi/M_PI;
        float u = theta/(2*M_PI);
        
        Texture *tex = tex_list_get(textures, sphere->useTexture);
        int row = (int) (v * tex->height);
        
        vec_list *list = tex->data[row];

        int column = (int) (u * list->length);
        Vector *texColor = vec_list_get(list, column+1);
        if(texColor == NULL){
            printf("it's over\n");
            initializeColorType(&color, -1, -1, -1);
            return color;
            
        }

        if(initialize_vector(&intrinsicColor, texColor->dx, texColor->dy, texColor->dz) == -1){
            printf("intrinsic color couldn't be created in shadeRay\n");
                initializeColorType(&color, -1, -1, -1);
                return color;
        }

        
    }else{
        
        if(initialize_vector(&intrinsicColor, sphere->Odr, sphere->Odg, sphere->Odb) == -1){
            printf("intrinsic color couldn't be created in shadeRay\n");
                initializeColorType(&color, -1, -1, -1);
                return color;
        }
    }

    if(initialize_vector(&specularColor, sphere->Osr, sphere->Osg, sphere->Osb) == -1){
        printf("specular Color couldn't be created in shadeRay\n");
            initializeColorType(&color, -1, -1, -1);
            return color;
    }

    Vector ambientTerm = scalarVecMult(sphere->ka, &intrinsicColor);
    for(int i = 0; i<numberOfLights; i++){
        
        H[i] = vectorAdd(&L[i], &V);
        H[i] = normalize(&H[i]);

        float nDotL = dotProduct(&N, &L[i]);
        float nDotH = dotProduct(&N, &H[i]);
        if(acos(nDotL) > M_PI/2){
            initialize_vector(&diffuseTerm, 0.0, 0.0, 0.0);
        }else{
            diffuseTerm = scalarVecMult(sphere->kd * nDotL, &intrinsicColor);
        }
        
        Vector specularTerm = scalarVecMult(sphere->ks * pow(fmax(0.0, nDotH),sphere->shinyFactor), &specularColor);
        Vector sum1 = vectorAdd(&specularTerm, &diffuseTerm);
        sum1 = scalarVecMult(lightArray[i]->lightIntensity * shadowFlag[i] * attenuationFactor[i], &sum1);
        sumOfLights = vectorAdd(&sumOfLights, &sum1);
    }

    


    // printf("nDOtL: %f\n", nDotL);


    
    Vector sum2 = vectorAdd(&sumOfLights, &ambientTerm);
    initializeColorType(&color, sum2.dx, sum2.dy, sum2.dz);

    if(color.r > 1){
        color.r = 1;
    }
    if(color.g > 1){
        color.g = 1;
    }
    if(color.b > 1){
        color.b = 1;
    }    
    
    return color;

}


ColorType shadeTriangle(Triangle *triangle, RayType *ray, Vector *surfacePoint, Light **lightArray, int numberOfLights, Vector *normalCoord, vec_list* normals){
    
    Vector intrinsicColor;
    Vector specularColor;
    Vector rayOrigin;
    Vector diffuseTerm;
    Vector V;
    Vector L[numberOfLights];
    Vector H[numberOfLights];
    float attenuationFactor[numberOfLights];
    ColorType color;
    
    Vector negSurfacePoint = scalarVecMult(-1, surfacePoint);

    Vector planeNormal;
    if(triangle->isSmoothShaded){

    // within this if statement normalCoord contains the barycentric coordinates
        
        int normalIndex1 = triangle->normal.dx;
        int normalIndex2 = triangle->normal.dy;
        int normalIndex3 = triangle->normal.dz;
    
        Vector* normal1 = vec_list_get(normals, normalIndex1);
        Vector* normal2 = vec_list_get(normals, normalIndex2);
        Vector* normal3 = vec_list_get(normals, normalIndex3);

        Vector alphaNormal1 = scalarVecMult(normalCoord->dx, normal1);
        Vector betaNormal2 = scalarVecMult(normalCoord->dy, normal2);
        Vector gammaNormal3 = scalarVecMult(normalCoord->dz, normal3);


        planeNormal = vectorAdd(&alphaNormal1, &betaNormal2);
        planeNormal = vectorAdd(&planeNormal, &gammaNormal3);
    
        planeNormal = normalize(&planeNormal);
    }else{

        // within this if statement normalCoord contains the coordinates of the plane normal
        initialize_vector(&planeNormal, normalCoord->dx, normalCoord->dy, normalCoord->dz);
    }

    

    if(initialize_vector(&intrinsicColor, triangle->Odr, triangle->Odg, triangle->Odb) == -1){
        
        printf("intrinsic color couldn't be created in triangle shadeRay\n");
        initializeColorType(&color, -1, -1, -1);
        return color;
    }
    

    if(initialize_vector(&specularColor, triangle->Osr, triangle->Osg, triangle->Osb) == -1){
        printf("specular Color couldn't be created in triangle shadeRay\n");
            initializeColorType(&color, -1, -1, -1);
            return color;
    }
    
    
    if(initialize_vector(&rayOrigin, ray->x, ray->y, ray->z) == -1){
        printf("rayOrigin vector creation ruined in shadeRay");
            initializeColorType(&color, -1, -1, -1);
            return color;
    }

    for(int i = 0; i < numberOfLights; i++){
        if(lightArray[i]->isPoint){
            L[i] = vectorAdd(&lightArray[i]->lightLocation, &negSurfacePoint);
            float distance = vectorLength(&L[i]);
            if(lightArray[i]->isAttenuated){
                attenuationFactor[i] = 1/(lightArray[i]->c1 + lightArray[i]->c2 * distance + lightArray[i]->c3 * pow(distance, 2));
            }else{
                attenuationFactor[i] = 1.0;
            }

            L[i] = normalize(&L[i]);
        }else{
            L[i] = scalarVecMult(-1, &lightArray[i]->lightLocation);
            attenuationFactor[i] = 1.0;
            L[i] = normalize(&L[i]);
        }
        
    }  


    Vector sumOfLights;
    initialize_vector(&sumOfLights, 0.0, 0.0, 0.0);
    V = vectorAdd(&rayOrigin, &negSurfacePoint);
    V = normalize(&V);
        
    
    Vector ambientTerm = scalarVecMult(triangle->ka, &intrinsicColor);
    


    for(int i = 0; i<numberOfLights; i++){
        printf("%d\n", numberOfLights);
        
        H[i] = vectorAdd(&L[i], &V);
        H[i] = normalize(&H[i]);

        printf("plane normal\n");
        printVector(&planeNormal);
        float nDotL = dotProduct(&planeNormal, &L[i]);
        printf("nDotL: %f\n", nDotL);
        float nDotH = dotProduct(&planeNormal, &H[i]);
        if(acos(nDotL) > M_PI/2){
            initialize_vector(&diffuseTerm, 0.0, 0.0, 0.0);
        }else{
            diffuseTerm = scalarVecMult(triangle->kd * nDotL, &intrinsicColor);
            
        }
        // printTriangle(triangle);

        printVector(&diffuseTerm);
        
        Vector specularTerm = scalarVecMult(triangle->ks * pow(fmax(0.0, nDotH),triangle->shinyFactor), &specularColor);
        Vector sum1 = vectorAdd(&specularTerm, &diffuseTerm);
        sum1 = scalarVecMult(lightArray[i]->lightIntensity  * attenuationFactor[i], &sum1);
        // printLight(lightArray[i]);
        sumOfLights = vectorAdd(&sumOfLights, &sum1);
    }


    printVector(&sumOfLights);

    Vector sum2 = vectorAdd(&sumOfLights, &ambientTerm);
    initializeColorType(&color, sum2.dx, sum2.dy, sum2.dz);

    if(color.r > 1){
        color.r = 1;
    }
    if(color.g > 1){
        color.g = 1;
    }
    if(color.b > 1){
        color.b = 1;
    }    
    
    return color;
    
}

void printColor(ColorType *color) {
    printf("color: (%f, %f, %f)\n", color->r, color->g, color->b);
}
