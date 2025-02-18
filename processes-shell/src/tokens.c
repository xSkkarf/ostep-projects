#include "../include/tokens.h"

/**
 * This function counts the number of tokens in a string, where a token is defined as a sequence of characters
 * that are not spaces or newlines, and it can be a > or & operators whether or not they are surrounded by spaces.
 */
int count_tokens(char * tokens, int char_count){
    int token_count = 0;
    char last_char = 0;
    for (size_t i = 0; i < char_count; i++)
    {
        if((tokens[i] == ' ' || tokens[i] == '\n') && (last_char != 0 && last_char != ' ')){
            token_count++;
        }else if((tokens[i] == '>' || tokens[i] == '&') && i != 0 && i != char_count -2 && tokens[i-1] != ' ' && tokens[i+1] != ' '){
            token_count+=2;
        }else if((tokens[i] == '>' || tokens[i] == '&') && ((last_char == ' ' && tokens[i+1] != ' ' && i != char_count -2) || (last_char != ' ')) && i != 0){
            token_count++;
        }
        last_char = tokens[i];
    }

    return token_count;
}

/**
 * This function extracts the tokens from a string, where a token is defined as a sequence of characters that are not spaces or newlines,
 * The tokens are stored in an array of strings, with each string representing a single token.
 */
void extract_token(char * source, char ** destination, char * delim){
    int i = 0;
    char * temp;
    char * trim_res;

    while((temp = strsep(&source, delim))){
        if(*temp){
            int j;
            int last = 0;
            for (j = 0; temp[j] != '\0' ; j++){
                
                if(temp[j] == '>' || temp[j] == '&'){
                    
                    if((trim_res = trim_token(temp, last, j-1)) != NULL){
                        destination[i] = trim_res;
                        i++;
                    }

                    destination[i] = strdup((temp[j] == '>' ? ">" : "&"));
                    i++;

                    last = j+1;

                }
            }
            
            if((trim_res = trim_token(temp, last, j-1)) != NULL){
                destination[i] = trim_res;
                i++;
            }
        }
    }
    destination[i] = '\0';

}

/**
 * This function trims a token from a string, where a token is defined as a sequence of characters that are not spaces or newlines,
 * and that are not part of a longer token surrounded by spaces or newlines.
 */
char * trim_token(char * token, int start, int end){
    if(end >= start){
        char * result = malloc(sizeof(char) * (end - start + 2));

        for (int i = start; i <= end; i++){
            result[i-start] = token[i];
        }
        result[end-start+1] = '\0';

        return result;
    }else{
        return NULL;
    }
    
}