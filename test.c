#include "ray.h"
#include "camera.h"
#include "stdlib.h"
#include "string.h"
#include "colorType.h"
#include "shapes.h"
#include "vector.h"
#include <stdio.h>


int writeHeader(FILE* file, char* width, char* height){
    char* p3 = "P3\n";
    if(fwrite(p3, strlen(p3), 1, file) < 1){
        perror("failed to write header\n");
        return -1;
    }

    // concatenates all the strings together to make the header for the ppm file
    char widthAndHeight[30] = "";
    char* resultString = strcat(widthAndHeight, width);
    resultString = strcat(widthAndHeight, " ");
    resultString = strcat(widthAndHeight, height);
    resultString = strcat(widthAndHeight, "\n");
    resultString = strcat(widthAndHeight, "255");
    resultString = strcat(widthAndHeight, "\n");

    //writes the entire string to the file provided to the function
    if(fwrite(resultString, strlen(resultString), 1, file) < 1){
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
/// @return 
int writeBackground(FILE* file,Camera* camera, char* width, char* height, ColorType* backgroundColor, SphereType** sphereArray){
    int numWidth = atoi(width); 
    
    int numHeight = atoi(height);
   // printf("%d\n", numWidth);
    //printf("%d\n", numHeight);

    int r = (int) (backgroundColor->r * 255);
    int g = (int)(backgroundColor->g * 255);
    int b = (int)(backgroundColor->b * 255);



    Vector negOrigin = scalarVecMult(-1, &camera->viewOrigin);
        
    Vector negUL = scalarVecMult(-1, &camera->upperLeftCorner);
    Vector numerator = vectorAdd(&camera->upperRightCorner,&negUL);
    Vector changeH = scalarVecMult(1/((float)numWidth-1), &numerator);
    
    //changeH = normalize(&changeH);

            
    Vector numerator2 = vectorAdd(&camera->lowerLeftCorner,&negUL);
    Vector changeV = scalarVecMult(1/((float)numHeight-1), &numerator2);
    //changeV = normalize(&changeV);
    //printf("changeH: (%f, %f, %f)\n", changeH.dx, changeH.dy, changeH.dz);

    //printf("changeV:  (%f, %f, %f)\n", changeV.dx, changeV.dy, changeV.dz);
    // loops through the size of the image to set each pixel value and write to the file
    for(int i = 0; i < numHeight; i++){
        
        char numChar[15];

        for(int j = 0; j < numWidth; j++){

            
            RayType ray;
            initializeRayType(&ray, camera->viewOrigin.dx, camera->viewOrigin.dy, camera->viewOrigin.dz);

            Vector row = scalarVecMult(j, &changeH);
            
            //printf("row: (%f, %f, %f)\n", row.dx, row.dy, row.dz);

            Vector col = scalarVecMult(i, &changeV);
            Vector sum1 = vectorAdd(&camera->upperLeftCorner, &row);
            //printf("sum1: (%f, %f, %f)\n", sum1.dx, sum1.dy, sum1.dz);

            Vector viewingPoint = vectorAdd(&sum1, &col);
            Vector direction = vectorAdd(&viewingPoint, &negOrigin);
            direction = normalize(&direction);
            //printf("viewingPoint: (%f, %f, %f)\n", viewingPoint.dx, viewingPoint.dy, viewingPoint.dz);
            setDirection(&ray, direction.dx, direction.dy, direction.dz); 
             
            ColorType* intersectColor = traceRay(&ray, sphereArray[0], backgroundColor);

             
            //printColor(intersectColor);
            r = 255 * intersectColor->r;
            g = 255 * intersectColor->g;
            b = 255 * intersectColor->b; 


            printf("r: %d\n", r);
            printf("g: %d\n", g);
            printf("b: %d\n", b);
            if(j%9 == 0){
                if(sprintf(numChar, "%d %d %d\n", r, g, b) == -1){
                    printf("sprintf failed in writeRandomBody\n");
                    return -1;
                }
                //printf("%s\n", numChar);
                
            }else{
                if(sprintf(numChar, "%d %d %d ", r, g, b) == -1){
                    printf("sprintf failed in writeRandomBody\n");
                    return -1;
                }
                //printf("%s\n", numChar);
            }
            if(fwrite(numChar, strlen(numChar), 1, file) < 1){
                perror("failed to write in writeRandomBody\n");
                return -1; 
            }
        }
    }
    return 0;
}


int main(){
    Camera *camera = malloc(sizeof(Camera));
    ColorType *backgroundColor = malloc(sizeof(ColorType));
    

    char buf[20];
    char* delimiter1 = " ";
    char* delimiter2 = "\n";
    char* delimiter3 = "\n\n";
    int m = 0; //shape tag;
    SphereType* sphereArray[10];

    while(1){
        printf("input text file: ");
        scanf("%s", buf);
        if(strcmp(buf, "q") == 0){
            printf("quiting...\n");
            return 0; 
        }

        FILE* inputFile = fopen(buf, "r");

        if(inputFile == NULL){
            printf("this file doesn't exist\n");
            return 1;
        }

        char buf2[512];
        if(fread(buf2, 1, sizeof(buf2), inputFile) < 0){
            printf("failed to read");
            return 1;
        }


        // start big if statement here


        char* token = strtok(buf2, delimiter1);
        char* width;
        char* height;

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

        float cX;
        float cY;
        float cZ;

        float X;
        float Y;
        float Z;
        float r;       
        while(token != NULL){
            printf("%s\n", token);
            if(strcmp(token, "imsize") == 0){
                //width and height
                // width and height
                width = strtok(NULL, delimiter1);
                height = strtok(NULL, delimiter2);
            }
            else if(strcmp(token, "eye") == 0){
                eyeX = strtof(strtok(NULL, delimiter1), NULL);
                eyeY = strtof(strtok(NULL, delimiter1), NULL);
                eyeZ = strtof(strtok(NULL, delimiter2), NULL);
                
            }
            else if(strcmp(token, "viewdir") == 0){
                viewDirX = strtof(strtok(NULL, delimiter1), NULL);
                viewDirY = strtof(strtok(NULL, delimiter1), NULL);
                viewDirZ = strtof(strtok(NULL, delimiter2), NULL);
            }
            else if(strcmp(token, "vfov") == 0){
                vfov = strtof(strtok(NULL, delimiter2), NULL); 
            }
            else if(strcmp(token, "updir") == 0){
                updirX = strtof(strtok(NULL, delimiter1), NULL);
                updirY = strtof(strtok(NULL, delimiter1), NULL);
                updirZ = strtof(strtok(NULL, delimiter2), NULL);
            }
            else if(strcmp(token, "bkgcolor") == 0){
                bcX = strtof(strtok(NULL, delimiter1), NULL);
                bcY = strtof(strtok(NULL, delimiter1), NULL);
                bcZ = strtof(strtok(NULL, delimiter2), NULL);
            }
            else if((strcmp(token, "mtlcolor") == 0) || (strcmp(token, "\nmtlcolor") == 0)){
                cX = strtof(strtok(NULL, delimiter1), NULL);
                cY = strtof(strtok(NULL, delimiter1), NULL);
                cZ = strtof(strtok(NULL, delimiter2), NULL);
                printf("mtlColor: (%f, %f, %f)\n", cX, cY, cZ);
                token = strtok(NULL, delimiter1);
        

                if(strcmp(token, "sphere") == 0){
                    X = strtof(strtok(NULL, delimiter1), NULL);
                    Y = strtof(strtok(NULL, delimiter1), NULL);
                    Z = strtof(strtok(NULL, delimiter1), NULL);
                    r = strtof(strtok(NULL, delimiter2), NULL);

                    SphereType* sphere = malloc(sizeof(SphereType));
                    initializeSphere(sphere, X, Y, Z, r, m);
                    setColor(sphere, cX, cY, cZ);
                    sphereArray[m] = sphere;
                    m++;
                    printf("%d\n", m);

                }
                // token = strtok(NULL, delimiter2);
                // printf("hopefully a new line %s", token);
            }
            token = strtok(NULL, delimiter1);
            // printf("this is current token %s\n", token);
        }
        m = 0;


        initialize_camera(camera, eyeX, eyeY, eyeZ);
        setViewingDirection(camera, viewDirX, viewDirY, viewDirZ);
        setVericalFOV(camera, vfov);
        setUpVector(camera, updirX, updirY, updirZ);
        setAspectRatio(camera, strtof(width, NULL), strtof(height, NULL));
        defineImageCoordinates(camera);
        setViewingWindow(camera, 3);
        initializeColorType(backgroundColor, bcX, bcY, bcZ);

        // printSphere(sphereArray[0]);
        // printSphere(sphereArray[1]);


        // all the information has been collected to define image coordinates

        
        
        //****************************************************************** */
       
        
        char* ppm = strtok(buf, ".");
        ppm = strcat(ppm, ".ppm");
        printf("Your new file is : %s\n", ppm);
        
        FILE* ppmFile = fopen(ppm, "w");
        writeHeader(ppmFile, width, height);
        writeBackground(ppmFile, camera, width, height, backgroundColor, sphereArray);
        fclose(ppmFile);


        printCamera(camera);
        fclose(inputFile);
    }

    free(camera);
    free(backgroundColor);
}
