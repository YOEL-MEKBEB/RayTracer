#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "camera.h"
#include "colorType.h"
#include "light.h"
#include "ppmReader.h"
#include "ray.h"
#include "shapes.h"
#include "stdlib.h"
#include "string.h"
#include "vecList.h"
#include "vector.h"

/// @brief writes the header of the ppm file
/// @param file
/// @param width
/// @param height
/// @return returns 0 on success and -1 on failure
int writeHeader(FILE *file, char *width, char *height) {
    char *p3 = "P3\n";
    if (fwrite(p3, strlen(p3), 1, file) < 1) {
        perror("failed to write header\n");
        return -1;
    }

    // concatenates all the strings together to make the header for the ppm file
    char widthAndHeight[30] = "";
    char *resultString = strcat(widthAndHeight, width);
    resultString = strcat(widthAndHeight, " ");
    resultString = strcat(widthAndHeight, height);
    resultString = strcat(widthAndHeight, "\n");
    resultString = strcat(widthAndHeight, "255");
    resultString = strcat(widthAndHeight, "\n");

    // writes the entire string to the file provided to the function
    if (fwrite(resultString, strlen(resultString), 1, file) < 1) {
        perror("failed to write header\n");
        return -1;
    }

    return 0;
}

/// @brief calculates the ray equation and writes it to a ppm file
/// @param file
/// @param width
/// @param height
/// @param color
/// @return returns 0 on success and -1 on failure
int writeImage(FILE *file, Camera *camera, char *width, char *height, ColorType *backgroundColor,
               SphereType **sphereArray, int lengthOfArray, vec_list *vertices, tri_list *faces,
               vec_list *normals, tex_list *textures, vec_list *texCoord, float bgIndexOfRefraction) {
    printf("entered writeImage\n");
    int numWidth = atoi(width);

    int numHeight = atoi(height);
    // printf("%d\n", numWidth);
    // printf("%d\n", numHeight);

    int r = (int) (backgroundColor->r * 255);
    int g = (int) (backgroundColor->g * 255);
    int b = (int) (backgroundColor->b * 255);

    Vector negOrigin = scalarVecMult(-1, &camera->viewOrigin);

    Vector negUL = scalarVecMult(-1, &camera->upperLeftCorner);
    Vector numerator = vectorAdd(&camera->upperRightCorner, &negUL);
    Vector changeH = scalarVecMult(1 / ((float) numWidth - 1), &numerator);

    // changeH = normalize(&changeH);

    Vector numerator2 = vectorAdd(&camera->lowerLeftCorner, &negUL);
    Vector changeV = scalarVecMult(1 / ((float) numHeight - 1), &numerator2);
    // changeV = normalize(&changeV);
    // printf("changeH: (%f, %f, %f)\n", changeH.dx, changeH.dy, changeH.dz);

    // printf("changeV:  (%f, %f, %f)\n", changeV.dx, changeV.dy, changeV.dz);
    //  loops through the size of the image to set each pixel value and write to the file
    for (int i = 0; i < numHeight; i++) {
        char numChar[15];

        for (int j = 0; j < numWidth; j++) {
            RayType ray;
            initializeRayType(&ray, camera->viewOrigin.dx, camera->viewOrigin.dy,
                              camera->viewOrigin.dz, bgIndexOfRefraction);
            setRayCurrentIdxOfRefraction(&ray, bgIndexOfRefraction);

            Vector row = scalarVecMult(j, &changeH);

            // printf("row: (%f, %f, %f)\n", row.dx, row.dy, row.dz);

            Vector col = scalarVecMult(i, &changeV);
            Vector sum1 = vectorAdd(&camera->upperLeftCorner, &row);
            // printf("sum1: (%f, %f, %f)\n", sum1.dx, sum1.dy, sum1.dz);

            Vector viewingPoint = vectorAdd(&sum1, &col);
            Vector direction = vectorAdd(&viewingPoint, &negOrigin);
            direction = normalize(&direction);
            // printf("viewingPoint: (%f, %f, %f)\n", viewingPoint.dx, viewingPoint.dy,
            // viewingPoint.dz);
            setDirection(&ray, direction.dx, direction.dy, direction.dz);
            setSphereIndex(&ray, -1);

            ColorType intersectColor =
                traceRay(&ray, sphereArray, lengthOfArray, backgroundColor, camera->light,
                         camera->numberOfLights, vertices, faces, normals, textures, texCoord, 0, 0);

            // printColor(&intersectColor);
            if (intersectColor.r < 0) {
                printColor(&intersectColor);
                printf("color returned is not valid\n");
                return -1;
            }

            // printColor(&intersectColor);
            r = 255 * intersectColor.r;
            g = 255 * intersectColor.g;
            b = 255 * intersectColor.b;

            if (j % 9 == 0) {
                if (sprintf(numChar, "%d %d %d\n", r, g, b) == -1) {
                    printf("sprintf failed in writeRandomBody\n");
                    return -1;
                }
                // printf("%s\n", numChar);

            } else {
                if (sprintf(numChar, "%d %d %d ", r, g, b) == -1) {
                    printf("sprintf failed in writeRandomBody\n");
                    return -1;
                }
                // printf("%s\n", numChar);
            }
            if (fwrite(numChar, strlen(numChar), 1, file) < 1) {
                perror("failed to write in writeRandomBody\n");
                return -1;
            }
        }
    }
    return 0;
}

int main() {
    Camera *camera = malloc(sizeof(Camera));
    ColorType *backgroundColor = malloc(sizeof(ColorType));

    char buf[20];
    char *delimiter1 = " ";
    char *delimiter2 = "\n";
    char *delimiter3 = "/";
    char *delimiter = " \n/";
    int m = 0;    // shape tag;
    SphereType *sphereArray[10];
    Light *lightArray[10];
    int lightIndex = 0;

    while (1) {
        vec_list *vertices = malloc(sizeof(vec_list));
        tri_list *faces = malloc(sizeof(tri_list));
        vec_list *normals = malloc(sizeof(vec_list));
        vec_list *textureCoord = malloc(sizeof(vec_list));
        tex_list *textures = malloc(sizeof(tex_list));

        tex_list_init(textures);
        tri_list_init(faces);
        vec_list_init(vertices);
        vec_list_init(normals);
        vec_list_init(textureCoord);

        printf("input text file: ");
        scanf("%s", buf);
        if (strcmp(buf, "q") == 0) {
            printf("quiting...\n");
            return 0;
        }

        FILE *inputFile = fopen(buf, "r");

        if (inputFile == NULL) {
            printf("this file doesn't exist\n");
            return 1;
        }

        int isNormalAcquired = 0;
        int useTexture = 0;
        int isTexCoord = 0;

        char buf2[100];
        char *token;
        char width[5];
        char height[5];

        float eyeX;
        float eyeY;
        float eyeZ;

        float viewDirX;
        float viewDirY;
        float viewDirZ;

        float vfov;

        float updirX;
        float updirY;
        float updirZ;

        float bcX;
        float bcY;
        float bcZ;
        float bcRefracion;

        float Odr;
        float Odg;
        float Odb;

        float Osr;
        float Osg;
        float Osb;

        float ka;
        float kd;
        float ks;

        int n;
        float opacity;
        float idxOfRefraction;

        float lightX, lightY, lightZ;
        int isPointLight;
        float lightIntensity;
        float c1, c2, c3;

        float X;
        float Y;
        float Z;
        float r;

        float vectorX;
        float vectorY;
        float vectorZ;

        // initialized to 0 for flat triangle
        float normal1 = 0;
        float normal2 = 0;
        float normal3 = 0;

        float vt1 = 0;
        float vt2 = 0;
        float vt3 = 0;

        float u;
        float v;

        while (fgets(buf2, 100, inputFile) != NULL) {
            token = strtok(buf2, delimiter1);

            // printf("%s\n", token);

            if (strcmp(token, "imsize") == 0) {
                printf("entered\n");

                strcpy(width, strtok(NULL, delimiter1));
                strcpy(height, strtok(NULL, delimiter2));

            } else if (strcmp(token, "eye") == 0) {
                eyeX = protectedStrToF(strtok(NULL, delimiter1));
                eyeY = protectedStrToF(strtok(NULL, delimiter1));
                eyeZ = protectedStrToF(strtok(NULL, delimiter2));
                printf("eyeZ: %f\n", eyeZ);
            } else if (strcmp(token, "viewdir") == 0) {
                viewDirX = protectedStrToF(strtok(NULL, delimiter1));
                viewDirY = protectedStrToF(strtok(NULL, delimiter1));
                viewDirZ = protectedStrToF(strtok(NULL, delimiter2));
            } else if (strcmp(token, "vfov") == 0) {
                vfov = protectedStrToF(strtok(NULL, delimiter2));
            } else if (strcmp(token, "updir") == 0) {
                updirX = protectedStrToF(strtok(NULL, delimiter1));
                updirY = protectedStrToF(strtok(NULL, delimiter1));
                updirZ = protectedStrToF(strtok(NULL, delimiter2));
                printf("%f\n", updirZ);
            } else if (strcmp(token, "bkgcolor") == 0) {
                bcX = protectedStrToF(strtok(NULL, delimiter1));
                bcY = protectedStrToF(strtok(NULL, delimiter1));
                bcZ = protectedStrToF(strtok(NULL, delimiter1));
                bcRefracion = protectedStrToF(strtok(NULL, delimiter2));

            } else if ((strcmp(token, "mtlcolor") == 0)) {
                Odr = protectedStrToF(strtok(NULL, delimiter1));
                Odg = protectedStrToF(strtok(NULL, delimiter1));
                Odb = protectedStrToF(strtok(NULL, delimiter1));
                printf("mtlColor: (%f, %f, %f)\n", Odr, Odg, Odb);

                Osr = protectedStrToF(strtok(NULL, delimiter1));
                Osg = protectedStrToF(strtok(NULL, delimiter1));
                Osb = protectedStrToF(strtok(NULL, delimiter1));

                printf("specularColor: (%f, %f, %f)\n", Osr, Osg, Osb);

                ka = protectedStrToF(strtok(NULL, delimiter1));
                kd = protectedStrToF(strtok(NULL, delimiter1));
                ks = protectedStrToF(strtok(NULL, delimiter1));

                printf("weights: (%f, %f, %f)\n", ka, kd, ks);
                n = atoi(strtok(NULL, delimiter1));

                opacity = protectedStrToF(strtok(NULL, delimiter1));
                idxOfRefraction = protectedStrToF(strtok(NULL, delimiter2));

            } else if ((strcmp(token, "sphere") == 0)) {
                X = protectedStrToF(strtok(NULL, delimiter1));
                Y = protectedStrToF(strtok(NULL, delimiter1));
                Z = protectedStrToF(strtok(NULL, delimiter1));
                r = protectedStrToF(strtok(NULL, delimiter2));
                // printf("in Sphere: %f\n", r);

                SphereType *sphere = malloc(sizeof(SphereType));
                // SphereType sphere;
                if (initializeSphere(sphere, X, Y, Z, r, m, useTexture, bcRefracion) == -1) {
                    return 1;
                }
                if (setIntrinsicColor(sphere, Odr, Odg, Odb) == -1) {
                    return 1;
                }
                if (setSpecularColor(sphere, Osr, Osg, Osb) == -1) {
                    return 1;
                }
                if (setWeight(sphere, ka, kd, ks) == -1) {
                    return 1;
                }
                if (setShinyFactor(sphere, n) == -1) {
                    return 1;
                }
                if (setOpacityAndRefraction(sphere, opacity, idxOfRefraction) == -1){
                    return 1;
                }

                printSphere(sphere);
                sphereArray[m] = sphere;
                m++;
                printf("%d\n", m);

            } else if (strcmp(token, "light") == 0) {
                lightX = protectedStrToF(strtok(NULL, delimiter1));
                lightY = protectedStrToF(strtok(NULL, delimiter1));
                lightZ = protectedStrToF(strtok(NULL, delimiter1));
                isPointLight = atoi(strtok(NULL, delimiter1));
                lightIntensity = protectedStrToF(strtok(NULL, delimiter2));
                c1 = 0.0;
                c2 = 0.0;
                c3 = 0.0;
                printf("setting non attenuated light\n");
                Light *light = malloc(sizeof(Light));
                if (setLightParameters(light, lightX, lightY, lightZ, isPointLight,
                                       lightIntensity) == -1) {
                    return 1;
                }
                lightArray[lightIndex] = light;
                lightIndex++;
            } else if (strcmp(token, "attlight") == 0) {
                lightX = protectedStrToF(strtok(NULL, delimiter1));
                lightY = protectedStrToF(strtok(NULL, delimiter1));
                lightZ = protectedStrToF(strtok(NULL, delimiter1));
                isPointLight = atoi(strtok(NULL, delimiter1));
                lightIntensity = protectedStrToF(strtok(NULL, delimiter1));
                c1 = protectedStrToF(strtok(NULL, delimiter1));
                c2 = protectedStrToF(strtok(NULL, delimiter1));
                c3 = protectedStrToF(strtok(NULL, delimiter2));
                printf("setting Attenuated light\n");
                Light *light = malloc(sizeof(Light));
                if (setAttLightParameters(light, lightX, lightY, lightZ, isPointLight,
                                          lightIntensity, c1, c2, c3) == -1) {
                    return 1;
                }
                lightArray[lightIndex] = light;
                printLight(lightArray[lightIndex]);
                lightIndex++;
            } else if (strcmp(token, "v") == 0) {
                vectorX = protectedStrToF(strtok(NULL, delimiter1));
                vectorY = protectedStrToF(strtok(NULL, delimiter1));
                vectorZ = protectedStrToF(strtok(NULL, delimiter2));

                Vector vertex;
                if (initialize_vector(&vertex, vectorX, vectorY, vectorZ) == -1) {
                    printf("the vertex coordinates are not a number\n");
                    return 1;
                }

                if (vec_list_add(vertices, &vertex) == -1) {
                    printf("failed to add vertices to list\n");
                    return 1;
                }

            } else if (strcmp(token, "f") == 0) {
                if (!isNormalAcquired && !useTexture) {
                    vectorX = protectedStrToF(strtok(NULL, delimiter1));
                    vectorY = protectedStrToF(strtok(NULL, delimiter1));
                    vectorZ = protectedStrToF(strtok(NULL, delimiter2));
                } else if (isNormalAcquired && !useTexture) {
                    vectorX = protectedStrToF(strtok(NULL, delimiter3));

                    char *temp = strtok(NULL, delimiter1);
                    temp = &temp[1];

                    normal1 = protectedStrToF(temp);

                    vectorY = protectedStrToF(strtok(NULL, delimiter3));

                    temp = strtok(NULL, delimiter1);
                    temp = &temp[1];

                    normal2 = protectedStrToF(temp);

                    vectorZ = protectedStrToF(strtok(NULL, delimiter3));
                    temp = strtok(NULL, delimiter2);
                    temp = &temp[1];

                    normal3 = protectedStrToF(temp);

                } else if (!isNormalAcquired && useTexture) {
                    vectorX = protectedStrToF(strtok(NULL, delimiter3));
                    vt1 = protectedStrToF(strtok(NULL, delimiter1));
                    vectorY = protectedStrToF(strtok(NULL, delimiter3));
                    vt2 = protectedStrToF(strtok(NULL, delimiter1));
                    vectorZ = protectedStrToF(strtok(NULL, delimiter3));
                    vt3 = protectedStrToF(strtok(NULL, delimiter2));
                } else if (isNormalAcquired && useTexture) {
                    vectorX = protectedStrToF(strtok(NULL, delimiter3));
                    vt1 = protectedStrToF(strtok(NULL, delimiter3));
                    normal1 = protectedStrToF(strtok(NULL, delimiter1));
                    vectorY = protectedStrToF(strtok(NULL, delimiter3));
                    vt2 = protectedStrToF(strtok(NULL, delimiter3));
                    normal2 = protectedStrToF(strtok(NULL, delimiter1));
                    vectorZ = protectedStrToF(strtok(NULL, delimiter3));
                    vt3 = protectedStrToF(strtok(NULL, delimiter3));
                    normal3 = protectedStrToF(strtok(NULL, delimiter2));
                }

                printf("use texture: %d\n", useTexture);

                Triangle triangle;
                if (initializeTriangle(&triangle, vectorX, vectorY, vectorZ, isNormalAcquired,
                                       useTexture, bcRefracion) == -1) {
                    printf("triangle couldn't be initialized\n");
                    return 1;
                }
                if (setTriangleNormal(&triangle, normal1, normal2, normal3) == -1) {
                    printf("triangle normal not a number\n");
                    printf("%f\n", normal1);
                    printf("%f\n", normal2);                    printf("%f\n", normal3);
                    return 1;
                }

                if (setTriangleTexture(&triangle, vt1, vt2, vt3) == -1) {
                    printf("triangle texture not a number\n");
                    printf("%f\n", vt1);
                    printf("%f\n", vt2);
                    printf("%f\n", vt3);
                    return 1;
                }

                if (setIntrinsicTriangle(&triangle, Odr, Odg, Odb) == -1) {
                    return 1;
                }
                if (setSpecularTriangle(&triangle, Osr, Osg, Osb) == -1) {
                    return 1;
                }
                if (setTriangleWeight(&triangle, ka, kd, ks) == -1) {
                    return 1;
                }
                if (setTriangleShinyFactor(&triangle, n) == -1) {
                    return 1;
                }
                if (setOpacityAndRefractionTriangle(&triangle, opacity, idxOfRefraction) == -1){
                    return 1;
                }
                // printf("triangle initialization: ");
                // printTriangle(&triangle);

                if (tri_list_add(faces, &triangle) == -1) {
                    return 1;
                }
            } else if (strcmp(token, "vn") == 0) {
                isNormalAcquired = 1;

                printf("entered the vector normal condition \n");
                vectorX = protectedStrToF(strtok(NULL, delimiter1));
                vectorY = protectedStrToF(strtok(NULL, delimiter1));
                vectorZ = protectedStrToF(strtok(NULL, delimiter2));

                Vector vertex;
                if (initialize_vector(&vertex, vectorX, vectorY, vectorZ) == -1) {
                    printf("the vertex coordinates are not a number\n");
                    return 1;
                }
                if (vec_list_add(normals, &vertex) == -1) {
                    return 1;
                }

            } else if (strcmp(token, "texture") == 0) {
                useTexture++;

                Texture *image = malloc(sizeof(Texture));

                char *fileName = strtok(NULL, delimiter2);

                char texture[100] = "texture/";
                char *filePath = strcat(texture, fileName);
                printf("%s\n", filePath);

                FILE *ppmFile = fopen(filePath, "r");
                if (ppmFile == NULL) {
                    printf("failed to open ppm file\n");
                    return 1;
                }
                char ppmbuf[100];
                fgets(ppmbuf, 100, ppmFile);

                printf("in texture section\n");
                char *last;
                char *header = strtok_r(ppmbuf, delimiter1, &last);
                if (strcmp(header, "P3") != 0) {
                    printf("not proper ppm file\n");
                    continue;
                }

                int ppmWidth = atoi(strtok_r(last, delimiter1, &last));
                int ppmHeight = atoi(strtok_r(last, delimiter1, &last));

                image->data = malloc(ppmHeight * sizeof(vec_list *));
                image->height = ppmHeight;
                if (ppmRead(image->data, ppmFile, ppmWidth, ppmHeight) == -1) {
                    printf("failed to read ppm\n");
                    fclose(ppmFile);
                    return -1;
                }

                fclose(ppmFile);

                tex_list_add(textures, image);

            } else if (strcmp(token, "vt") == 0) {
                printf("entered vt section\n");
                isTexCoord = 1;
                u = protectedStrToF(strtok(NULL, delimiter1));
                v = protectedStrToF(strtok(NULL, delimiter2));

                Vector texCoord;
                if (initialize_vector(&texCoord, u, v, 0.0) == -1) {
                    printf("texture coordinate array not created properly\n");
                    return 1;
                }
                if (vec_list_add(textureCoord, &texCoord) == -1) {
                    return 1;
                }
            }
        }

        int length = m;
        int lengthOfLight = lightIndex;
        lightIndex = 0;
        m = 0;

        if (initialize_camera(camera, eyeX, eyeY, eyeZ) == -1) {
            printf("camera coordinates are not numbers\n");
            continue;
        }
        if (setViewingDirection(camera, viewDirX, viewDirY, viewDirZ) == -1) {
            printf("viewing direction coordinates are not numbers\n");
            continue;
        }
        if (setVericalFOV(camera, vfov) == -1) {
            printf("vertical fov is not a number\n");
            continue;
        }
        if (setUpVector(camera, updirX, updirY, updirZ) == -1) {
            printf("up vector coordinates are not numbers\n");
            continue;
        }
        if (setAspectRatio(camera, strtof(width, NULL), strtof(height, NULL)) == -1) {
            printf("width and height are not numbers\n");
            continue;
        }
        defineImageCoordinates(camera);
        setViewingWindow(camera, 3);
        setLight(camera, lightArray, lengthOfLight);

        initializeColorType(backgroundColor, bcX, bcY, bcZ);


        // all the information has been collected to define image coordinates

        //****************************************************************** */

        char *ppm = strtok(buf, ".");
        ppm = strcat(ppm, ".ppm");
        printf("Your new file is : %s\n", ppm);

        FILE *ppmFile = fopen(ppm, "w");

        if (ppmFile == NULL) {
            printf("failed to create ppm file");
            fclose(ppmFile);
            fclose(inputFile);
            free(camera);
            free(backgroundColor);
            return 1;
        }

        if (writeHeader(ppmFile, width, height) == -1) {
            printf("failed to write the header of the ppm");
            fclose(ppmFile);
            fclose(inputFile);
            free(camera);
            free(backgroundColor);
            return 1;
        }
        if (writeImage(ppmFile, camera, width, height, backgroundColor, sphereArray, length,
                       vertices, faces, normals, textures, textureCoord, bcRefracion) == -1) {
            fclose(ppmFile);
            fclose(inputFile);
            free(camera);
            free(backgroundColor);
            printf("writeImage failed\n");
            return 1;
        }
        fclose(ppmFile);

        printCamera(camera);
        fclose(inputFile);
        for (int i = 0; i < length; i++) {
            free(sphereArray[i]);
        }
        for (int i = 0; i < lengthOfLight; i++) {
            free(lightArray[i]);
        }
        for (int i = 1; i < textures->length + 1; i++) {
            Texture *temp = tex_list_get(textures, i);
            for (int j = 0; j < temp->height; j++) {
                vec_list *list = temp->data[j];

                // for(int k = 1; k<list->length; k++){
                //     printVector(vec_list_get(list, k));
                // }
                vec_list_clear(list);
            }
        }

        vec_list_clear(vertices);
        tri_list_clear(faces);
        vec_list_clear(normals);
        tex_list_clear(textures);
        vec_list_clear(textureCoord);
    }

    free(camera);
    free(backgroundColor);
    return 0;
}
