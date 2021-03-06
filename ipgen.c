//
//  main.c
//  ipgen
//  
//  Ip adress generator from user arguments
//  Gerador de endereçamento IP a partir do range estabelecido pelo usuário.
//
//  Created by Danilo Vitelli Camillo on 31/12/15.
//  Copyright © 2015 Danilo Vitelli Camillo. All rights reserved.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int setInferiorLimit(int remainder, int octet);
int setSuperiorLimit(int remainder, int octet);

int main(int argc, const char * argv[]) {
    
    int firstOctet, secondOctet, thirdOctet, fourthOctet, mask;
    int firstInferiorLimit, firstSuperiorLimit, secondInferiorLimit, secondSuperiorLimit, thirdInferiorLimit, thirdSuperiorLimit, fourthInferiorLimit, fourthSuperiorLimit;
    int quotient, remainder;
    FILE *fp;
    
    /*  Receives the IP address as an argument from the command line and atributes the octets to the respectives variables*/
    
    if(argc == 2){
    
    sscanf(argv[1],"%d.%d.%d.%d/%d", &firstOctet, &secondOctet, &thirdOctet, &fourthOctet, &mask);
        
    }else{
        printf("Type an ip address with mask:\n");
        scanf("%d.%d.%d.%d/%d",&firstOctet, &secondOctet, &thirdOctet, &fourthOctet, &mask);
    }
    /*  Makes the mask integer division by 8 and gets the quotient and the remainder. The quotient indicates the number of fixed octets and the remainder indicates the number of bits for the next octet used by the mask*/
    
    quotient = mask/8;
    remainder = mask%8;
    
    /*  Opens a file to write */
    fp = fopen("ipgen.txt","w UTF-8");
    if(!fp){
        printf( "Erro na abertura do arquivo");
        exit(0);
    }
    
    switch (quotient) {
            
        case 1:
            
            if (remainder!=0){
                
                secondInferiorLimit= setInferiorLimit(remainder,secondOctet) - 1;
                secondSuperiorLimit = setSuperiorLimit(remainder,secondOctet) + 1;
                
            } else{
                secondInferiorLimit = 0;
                secondSuperiorLimit = 255;
            }
            
            firstInferiorLimit = firstSuperiorLimit = firstOctet;
            thirdInferiorLimit = 0;
            thirdSuperiorLimit = 255;
            fourthInferiorLimit = 1;
            fourthSuperiorLimit = 254;
            break;
            
        case 2:
            
            if (remainder!=0){
                
                thirdInferiorLimit = setInferiorLimit(remainder,thirdOctet) - 1;
                thirdSuperiorLimit = setSuperiorLimit(remainder,thirdOctet) + 1;
                
            } else{
                thirdInferiorLimit = 0;
                thirdSuperiorLimit = 255;
            }
            
            firstInferiorLimit = firstSuperiorLimit = firstOctet;
            secondInferiorLimit = secondSuperiorLimit = secondOctet;
            fourthInferiorLimit = 1;
            fourthSuperiorLimit = 254;
            
            break;
            
        case 3:
            
            if (remainder!=0){
                
                fourthInferiorLimit = setInferiorLimit(remainder,fourthOctet);
                fourthSuperiorLimit = setSuperiorLimit(remainder,fourthOctet);
                
            } else{
                fourthInferiorLimit = 1;
                fourthSuperiorLimit = 254;
            }
            
            firstInferiorLimit = firstSuperiorLimit = firstOctet;
            secondInferiorLimit = secondSuperiorLimit = secondOctet;
            thirdInferiorLimit = thirdSuperiorLimit = thirdOctet;
            
            break;
            
        case 4:
            
            firstInferiorLimit = firstSuperiorLimit = firstOctet;
            secondInferiorLimit = secondSuperiorLimit = secondOctet;
            thirdInferiorLimit = thirdSuperiorLimit = thirdOctet;
            fourthInferiorLimit = fourthSuperiorLimit = fourthOctet;
            
            break;
            
        case 0:
            
            firstInferiorLimit = 1;
            firstSuperiorLimit = 255;
            secondInferiorLimit = 0;
            secondSuperiorLimit = 255;
            thirdInferiorLimit = 0;
            thirdSuperiorLimit = 255;
            fourthInferiorLimit = 1;
            fourthSuperiorLimit = 254;
            
            break;
            
        default:
            
            firstInferiorLimit = firstSuperiorLimit = firstOctet;
            secondInferiorLimit = secondSuperiorLimit = secondOctet;
            thirdInferiorLimit = thirdSuperiorLimit = thirdOctet;
            fourthInferiorLimit = fourthSuperiorLimit = fourthOctet;
            
            break;
    }
    
    while(firstInferiorLimit <= firstSuperiorLimit){
        while(secondInferiorLimit <= secondSuperiorLimit){
            while(thirdInferiorLimit <= thirdSuperiorLimit){
                while(fourthInferiorLimit  <= fourthSuperiorLimit){
                    printf("%d.%d.%d.%d\n", firstInferiorLimit, secondInferiorLimit, thirdInferiorLimit, fourthInferiorLimit);
                    fprintf(fp,"%d.%d.%d.%d\n", firstInferiorLimit, secondInferiorLimit, thirdInferiorLimit, fourthInferiorLimit);
                    fourthInferiorLimit++;
                }
                thirdInferiorLimit++;
                fourthInferiorLimit = 1;
            }
            secondInferiorLimit++;
            thirdInferiorLimit = 1;
            fourthInferiorLimit = 1;
        }
        firstInferiorLimit++;
        secondInferiorLimit = 1;
        thirdInferiorLimit = 1;
        fourthInferiorLimit = 1;
    }
    
    return 0;
}

int setInferiorLimit(int remainder, int octet)
{

    int bit, hostQuantity, networkIdentifier, broadcastAddress, sum = 0;
    int inferiorLimit, superiorLimit;
    
    bit = 8 - remainder;
        
    while(bit < 8){
    sum = sum + pow(2,bit);
    bit++;
    }
    
    hostQuantity= (255 - sum) - 1;
    
    networkIdentifier = 0;
    inferiorLimit = 1;
    superiorLimit = hostQuantity;
    broadcastAddress = hostQuantity + 1;
    
    while (networkIdentifier < octet){
        
        if(octet > broadcastAddress){
            
            networkIdentifier = broadcastAddress + 1;
            inferiorLimit = networkIdentifier + 1;
            superiorLimit = networkIdentifier + hostQuantity;
            broadcastAddress = superiorLimit + 1;
            
        }else{
            return inferiorLimit;
        }
    }
    
    return inferiorLimit;
    
}

int setSuperiorLimit(int remainder, int octet)
{
    
    int bit, hostQuantity, networkIdentifier, broadcastAddress, sum = 0;
    int inferiorLimit, superiorLimit;
    
    bit = 8 - remainder;
    
    while(bit < 8){
        sum = sum + pow(2,bit);
        bit++;
    }
    
    hostQuantity = (255 - sum) - 1;
    
    networkIdentifier = 0;
    inferiorLimit = 1;
    superiorLimit = hostQuantity;
    broadcastAddress = superiorLimit + 1;
    
    while (octet > broadcastAddress){
        
        networkIdentifier = broadcastAddress + 1;
        inferiorLimit = networkIdentifier + 1;
        superiorLimit = networkIdentifier + hostQuantity;
        broadcastAddress = superiorLimit + 1;
        
    }
    
    return superiorLimit;
    
}


