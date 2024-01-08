#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

//----------------------------Function to calculate the MD5 hash of a given string or int-----------------------------
void calculate_md5_hash(char* input, char* output){
    MD5_CTX md5_1;
    MD5_Init(&md5_1);
    MD5_Update(&md5_context, input, strlen(input));
    MD5_Final((unsigned char*)output, &md5_1);
}

//----------------------Function to convert the hexadecimal MD5 hash to a string--------------------------------------------
void hex_to_string(unsigned char* hex, char* output){
    int i;
    for(i=0; i < 16; i++){
        sprintf(output+i*2, "%02x", hex[i]);
    }
}

//-------------------Function to check if a password is equal to its MD5 hash
int is_password_equal_to_hash(char* password, char* md5_hash){
    char md5_output[33];
    calculate_md5_hash(password, md5_output);
    return strcmp(md5_output, md5_hash) == 0;
}

//run main program to brute force the password 
int main(){
    //MD5 hash goes here (take string or int value as char)
    char md5_hash[] = "b5e4d80c6dc2a5e629563f132c7b6816";
    
    // loop to brute force all possible combinations
    for(int length = 1; length <= strlen(md5_hash)/2; length++){
        char password[length + 1];
        password[length] = '\0';
        for(int i = 0; i < 62; i++){
            password[0] = i < 10 ? i + '0' : (i - 10) + 'A';
            for(int j = 1; j < length; j++){
                password[j] = i < 10 ? i + '0' : (i - 10) + 'A';
            }
            if(is_password_equal_to_hash(password, md5_hash)){
                printf("Found password: %s\n", password);
                return 0;
            }
        }
    }
    
    printf("Password not found\n");
    return 1;
}