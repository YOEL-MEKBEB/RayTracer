#include "ray.h"
#include "camera.h"
#include "stdlib.h"
#include "string.h"
#include "colorType.h"
#include "shapes.h"


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
int writeBackground(FILE* file, char* width, char* height, ColorType* backgroundColor){
    int numWidth = atoi(width);
    
    int numHeight = atoi(height);
    printf("%d\n", numWidth);
    printf("%d\n", numHeight);

    int r = (int) (backgroundColor->r * 255);
    int g = (int)(backgroundColor->g * 255);
    int b = (int)(backgroundColor->b * 255);

    // loops through the size of the image to set each pixel value and write to the file
    for(int i = 0; i < numHeight; i++){
        
        char numChar[15];

        // j < 3 * numWidth because each pixel will have 3 number associated with it
        for(int j = 0; j < numWidth; j++){
            if(j%9 == 0){
                if(sprintf(numChar, "%d %d %d\n", r, g, b) == -1){
                    printf("sprintf failed in writeRandomBody\n");
                    return -1;
                }
                printf("%s\n", numChar);
                
            }else{
                if(sprintf(numChar, "%d %d %d ", r, g, b) == -1){
                    printf("sprintf failed in writeRandomBody\n");
                    return -1;
                }
                printf("%s\n", numChar);
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

        char *token = strtok(buf2, delimiter1);
        if(strcmp(token, "imsize") != 0){
            printf("invalid text format\n");
            return 1;
        }

        //width and height
        char *width = strtok(NULL, delimiter1);
        char *height = strtok(NULL, delimiter2);
        // width and height

        // eye location
        token = strtok(NULL, delimiter1);
        printf("%s\n", token);
        if(strcmp(token, "eye") != 0){
            printf("invalid text format\n");
            return 1;
        }
        float eyeX = strtof(strtok(NULL, delimiter1), NULL);
        float eyeY = strtof(strtok(NULL, delimiter1), NULL);
        float eyeZ = strtof(strtok(NULL, delimiter2), NULL);
        initialize_camera(camera, eyeX, eyeY, eyeZ);
        // eye location


        //view direction
        token = strtok(NULL, delimiter1);
        printf("%s\n", token);
        if(strcmp(token, "viewdir") != 0){
            printf("invalid text format\n");
            return 1;
        }
        float viewDirX = strtof(strtok(NULL, delimiter1), NULL);
        float viewDirY = strtof(strtok(NULL, delimiter1), NULL);
        float viewDirZ = strtof(strtok(NULL, delimiter2), NULL);
        setViewingDirection(camera, viewDirX, viewDirY, viewDirZ);
        //view direction

        //vFOV
        token = strtok(NULL, delimiter1);
        printf("%s\n", token);
        if(strcmp(token, "vfov") != 0){
            printf("invalid text format\n");
            return 1;
        }
        float vfov = strtof(strtok(NULL, delimiter2), NULL);
        setVericalFOV(camera, vfov);
        //vFOV

        //up vector
        token = strtok(NULL, delimiter1);
        printf("%s\n", token);
        if(strcmp(token, "updir") != 0){
            printf("invalid text format\n");
            return 1;
        }
        float updirx = strtof(strtok(NULL, delimiter1), NULL);
        float updirY = strtof(strtok(NULL, delimiter1), NULL);
        float updirZ = strtof(strtok(NULL, delimiter2), NULL);
        setUpVector(camera, updirx, updirY, updirZ);
        //up vector


        // all the information has been collected to define image coordinates

        defineImageCoordinates(camera);
        setViewingWindow(camera, 3);
        //****************************************************************** */

        //background color
        token = strtok(NULL, delimiter1);
        printf("%s\n", token);
        if(strcmp(token, "bkgcolor") != 0){
            printf("invalid text format\n");
            return 1;
        }
        float bcX = strtof(strtok(NULL, delimiter1), NULL);
        float bcY = strtof(strtok(NULL, delimiter1), NULL);
        float bcZ = strtof(strtok(NULL, delimiter2), NULL);
        // ////////////////////////////add color functionality
        //background color

        initializeColorType(backgroundColor, bcX, bcY, bcZ);


        // color of object
        token = strtok(NULL, delimiter1);
        printf("%s\n", token);
        if(strcmp(token, "mtlcolor") != 0){
            printf("invalid text format\n");
            return 1;
        }
        char *cX = strtok(NULL, delimiter1);
        char *cY = strtok(NULL, delimiter1);
        char *cZ = strtok(NULL, delimiter2);
        // color of object

        // type of object
        token = strtok(NULL, delimiter1);
        printf("%s\n", token);
        if(strcmp(token, "sphere") != 0){
            printf("invalid text format\n");
            return 1;
        }
        char *X = strtok(NULL, delimiter1);
        char *Y = strtok(NULL, delimiter1);
        char *Z = strtok(NULL, delimiter1);
        char *r = strtok(NULL, delimiter2);
        // type of object



        char* ppm = strtok(buf, ".");
        ppm = strcat(ppm, ".ppm");
        printf("Your new file is : %s\n", ppm);
        //printf("Your height is : %s\n", height);
        FILE* ppmFile = fopen(ppm, "w");
        writeHeader(ppmFile, width, height);
        writeBackground(ppmFile, width, height, backgroundColor);
        fclose(ppmFile);



        printCamera(camera);
        printf("%s\n", width);
        printf("%s\n", height);
        printf("%s\n", cX);
        printf("%s\n", cY);
        printf("%s\n", cZ);
        printf("%s\n", X);
        printf("%s\n", Y);
        printf("%s\n", Z);
        printf("%s\n", r);
    

        fclose(inputFile);
    }

}