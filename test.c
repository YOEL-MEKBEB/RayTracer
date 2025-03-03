#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stdlib.h"
#include "string.h"
#include <math.h>
/// @brief calls strtof and handles error where it returns 0 on text
/// @param token
/// @return returns the converted value on success or NAN on error
float protectedStrToF(char *token) {
    float value = strtof(token, NULL);
    if (strtof(token, NULL) == 0.0){
        if(strcmp("0", token) != 0 && strcmp("0.0", token) != 0) {
            return NAN;
        }
    }
    return value;
}


int main() {
    // Camera *camera = malloc(sizeof(Camera));
    // ColorType *backgroundColor = malloc(sizeof(ColorType));

    char buf[20];
    char *delimiter1 = " ";
    char *delimiter2 = "\n";
    char *delimiter3 = "\n\n";
    int m = 0;    // shape tag;

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


        // start big if statement here
        char buf2[100];

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

        float lightX, lightY, lightZ;
        int isPointLight;
        float lightIntensity;
        float c1, c2, c3;

        float X;
        float Y;
        float Z;
        float r;


        char *token;
        while(fgets(buf2, 100, inputFile) != NULL){
          token = strtok(buf2, delimiter1);

          printf("%s\n", token);

          if(strcmp(token, "imsize") == 0){

              printf("entered\n");

              strcpy(width, strtok(NULL, delimiter1));
              strcpy(height, strtok(NULL, delimiter2));
          
          } else if (strcmp(token, "eye") == 0) {
            eyeX = protectedStrToF(strtok(NULL, delimiter1));
            eyeY = protectedStrToF(strtok(NULL, delimiter1));
            eyeZ = protectedStrToF(strtok(NULL, delimiter2));
            printf("eyeZ: %f\n", eyeZ);
          }else if (strcmp(token, "viewdir") == 0) {
                viewDirX = protectedStrToF(strtok(NULL, delimiter1));
                viewDirY = protectedStrToF(strtok(NULL, delimiter1));
                viewDirZ = protectedStrToF(strtok(NULL, delimiter2));
          } else if (strcmp(token, "vfov") == 0) {
                vfov = protectedStrToF(strtok(NULL, delimiter2));
          } else if (strcmp(token, "updir") == 0) {
                updirX = protectedStrToF(strtok(NULL, delimiter1));
                updirY = protectedStrToF(strtok(NULL, delimiter1));
                updirZ = protectedStrToF(strtok(NULL, delimiter2));
          } else if (strcmp(token, "bkgcolor") == 0) {
                bcX = protectedStrToF(strtok(NULL, delimiter1));
                bcY = protectedStrToF(strtok(NULL, delimiter1));
                bcZ = protectedStrToF(strtok(NULL, delimiter2));
          
          } else if ((strcmp(token, "mtlcolor") == 0) || (strcmp(token, "\nmtlcolor") == 0)) {
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
                n = atoi(strtok(NULL, delimiter2));

          }else if ((strcmp(token, "sphere") == 0) || (strcmp(token, "\nsphere") == 0)) {
                    X = protectedStrToF(strtok(NULL, delimiter1));
                    Y = protectedStrToF(strtok(NULL, delimiter1));
                    Z = protectedStrToF(strtok(NULL, delimiter1));
                    r = protectedStrToF(strtok(NULL, delimiter2));
                    // printf("in Sphere: %f\n", r);
                    
                    SphereType *sphere = malloc(sizeof(SphereType));
                    //SphereType sphere;
                    if(initializeSphere(sphere, X, Y, Z, r, m) == -1){
                        return 1;
                    }
                    if(setIntrinsicColor(sphere, Odr, Odg, Odb) == -1){
                        return 1;
                    }
                    if(setSpecularColor(sphere, Osr, Osg, Osb) == -1){
                        return 1;
                    }
                    if(setWeight(sphere, ka, kd, ks) == -1){
                        return 1;
                    }
                    if(setShinyFactor(sphere, n) == -1){
                        return 1;
                    }
                    printSphere(sphere);
                    sphereArray[m] = sphere;
                    m++;
                    printf("%d\n", m);

          }  else if(strcmp(token, "light")==0){
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
                    setLightParameters(light, lightX, lightY, lightZ, isPointLight, lightIntensity);
                    lightArray[lightIndex] = light;
                    lightIndex++;
          }else if(strcmp(token, "attlight")==0){
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
                    setAttLightParameters(light, lightX, lightY, lightZ,isPointLight,lightIntensity, c1, c2, c3);
                    lightArray[lightIndex] = light;
                    printLight(light);
                    printLight(lightArray[lightIndex]);
                    lightIndex++;
          }
        }

        printf("%s\n", width);
        printf("%s\n", height);

        printf("%f\n", eyeX);
        printf("%f\n", eyeY);
        printf("%f\n", eyeZ);
        
        printf("%f\n", viewDirX);
        printf("%f\n", viewDirY);
        printf("%f\n", viewDirZ);
        
        printf("%f\n", bcX);
        printf("%f\n", bcY);
        printf("%f\n", bcZ);

        printf("%f\n", vfov);
        

        // all the information has been collected to define image coordinates

        //****************************************************************** */


    return 0;
}
