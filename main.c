#include <stdio.h>
#include <string.h>


FILE *input_file;


typedef enum {
    IDENTIFIER_TOKEN,
    PLUS_TOKEN,
    MINUS_TOKEN,
    DIVIDE_TOKEN,
    MULTIPLE_TOKEN,
    ASSIGNMENT_TOKEN,
    ADDITION_ASSIGNMENT_TOKEN,
    SUBTRACTION_ASSIGNMENT_TOKEN,
    MULTIPLICATION_ASSIGNMENT_TOKEN,
    DIVISION_ASSIGNMENT_TOKEN,
    BRACKET_TOKEN,
    CURLY_BRACE_TOKEN,
    PARENTHESES_TOKEN,
    COMMENT_TOKEN,
    AND_TOKEN,
    OR_TOKEN,
    EQUAL_TOKEN,
    NOT_EQUAL_TOKEN,
    GREATER_TOKEN,
    LESS_TOKEN,
    GREATER_EQUAL_TOKEN,
    LESS_EQUAL_TOKEN,
    IF_TOKEN,
    ELSE_TOKEN,
    FOR_TOKEN,
    WHILE_TOKEN,
    INPUT_TOKEN,
    OUTPUT_TOKEN,
    INT_TOKEN,
    INTEGER_TOKEN,
    FLOAT_TOKEN,
    DECIMAL_POINT_TOKEN,
    STR_TOKEN,
    STRING_TOKEN,
    BOOLEAN_TOKEN,
    TRUE_TOKEN,
    FALSE_TOKEN,
    OVER_TOKEN,
    UNIDENTIFIED_TOKEN,
} token;

token tokenscan(FILE *input_text);
char *strtoken(token t);
int write_tokens();

char *strtoken(token t) {
    switch (t) {
        case IDENTIFIER_TOKEN:
            return "<IDENTIFIER_TOKEN>";

        case PLUS_TOKEN:
            return "<PLUS_TOKEN>";

        case MINUS_TOKEN:
            return "<MINUS_TOKEN>";

        case MULTIPLE_TOKEN:
            return "<MULTIPLE_TOKEN>";

        case DIVIDE_TOKEN:
            return "<DIVIDE_TOKEN>";

        case ASSIGNMENT_TOKEN:
            return "<ASSIGNMENT_TOKEN>";

        case ADDITION_ASSIGNMENT_TOKEN:
            return "<ADDITION_ASSIGNMENT_TOKEN>";

        case SUBTRACTION_ASSIGNMENT_TOKEN:
            return "<SUBTRACTION_ASSIGNMENT_TOKEN>";

        case MULTIPLICATION_ASSIGNMENT_TOKEN:
            return "<MULTIPLICATION_ASSIGNMENT_TOKEN>";

        case DIVISION_ASSIGNMENT_TOKEN:
            return "<DIVISION_ASSIGNMENT_TOKEN>";

        case COMMENT_TOKEN:
            return "<COMMENT_TOKEN>";

        case CURLY_BRACE_TOKEN:
            return "<CURLY_BRACE_TOKEN>";

        case BRACKET_TOKEN:
            return "<BRACKET_TOKEN>";

        case PARENTHESES_TOKEN:
            return "<PARENTHESES_TOKEN>";

        case AND_TOKEN:
            return "<AND_TOKEN>";

        case OR_TOKEN:
            return "<OR_TOKEN>";

        case EQUAL_TOKEN:
            return "<EQUAL_TOKEN>";

        case NOT_EQUAL_TOKEN:
            return "<NOT_EQUAL_TOKEN>";

        case GREATER_TOKEN:
            return "<GREATER_TOKEN>";

        case LESS_TOKEN:
            return "<LESS_TOKEN>";

        case GREATER_EQUAL_TOKEN:
            return "<GREATER_EQUAL_TOKEN>";

        case LESS_EQUAL_TOKEN:
            return "<LESS_EQUAL_TOKEN>";

        case IF_TOKEN:
            return "<IF_TOKEN>";

        case ELSE_TOKEN:
            return "<ELSE_TOKEN>";

        case FOR_TOKEN:
            return "<FOR_TOKEN>";

        case WHILE_TOKEN:
            return "<WHILE_TOKEN>";

        case INPUT_TOKEN:
            return "<INPUT_TOKEN>";

        case OUTPUT_TOKEN:
            return "<OUTPUT_TOKEN>";

        case INT_TOKEN:
            return "<INT_TOKEN>";

        case INTEGER_TOKEN:
            return "<INTEGER_TOKEN>";

        case FLOAT_TOKEN:
            return "<FLOAT_TOKEN>";

        case DECIMAL_POINT_TOKEN:
            return "<DECIMAL_POINT_TOKEN>";

        case STR_TOKEN:
            return "<STR_TOKEN>";

        case STRING_TOKEN:
            return "<STRING_TOKEN>";

        case BOOLEAN_TOKEN:
            return "<BOOLEAN_TOKEN>";

        case TRUE_TOKEN:
            return "<TRUE_TOKEN>";

        case FALSE_TOKEN:
            return "<FALSE_TOKEN>";

        case OVER_TOKEN:
            return "<OVER_TOKEN>";

        case UNIDENTIFIED_TOKEN:
            return "<UNIDENTIFIED_TOKEN>";
    }
}

token tokenscan(FILE *input_text) {
    char buffer[256];
    int bufferIndex = 0;

    char ch = fgetc(input_text);
    switch (ch) {
        case '+':
            ch = fgetc(input_text);
            if (ch == '~') {
                return ADDITION_ASSIGNMENT_TOKEN;
            } else {
                ungetc(ch, input_text);
                return PLUS_TOKEN;
            }

        case '-':
            buffer[bufferIndex] = ch;
            ch = fgetc(input_text);
            if (ch == '~') {
                return SUBTRACTION_ASSIGNMENT_TOKEN;
            }
            else if (ch >= 48 && ch <= 57) {
                if (ch == '0'){
                    bufferIndex++;
                    buffer[bufferIndex] = ch;
                    ch = fgetc(input_text);
                    if (ch == '.'){
                        bufferIndex++;
                        buffer[bufferIndex] = ch;
                        ch = fgetc(input_text);
                        if (ch >= 48 && ch <= 57){
                            int zeroCount = 0;
                            int nonZeroCount = 0;
                            while (ch >= 48 && ch <= 57) {
                                if (ch == '0')
                                    zeroCount += 1;
                                else
                                    nonZeroCount += 1;
                                bufferIndex++;
                                buffer[bufferIndex] = ch;
                                ch = fgetc(input_text);
                            }
                            if (nonZeroCount == 0 && zeroCount > 1){
                                ungetc(ch, input_text);
                                return UNIDENTIFIED_TOKEN;
                            }
                            else if ((ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~' ||
                                      ch == '>' || ch == '<'|| ch == '!' || ch == '(' || ch == ')'  || ch == EOF ||
                                      ch == '\n') && buffer[bufferIndex - 1] != '0'){
                                ungetc(ch , input_text);
                                return DECIMAL_POINT_TOKEN;
                            }
                            else return UNIDENTIFIED_TOKEN;

                        }
                        else
                            return UNIDENTIFIED_TOKEN;
                    }
                    else {
                        while (ch >= 48 && ch <= 57) {
                            bufferIndex++;
                            buffer[bufferIndex] = ch;
                            ch = fgetc(input_text);
                        }
                        return UNIDENTIFIED_TOKEN;
                    }
                }
                else {
                    while (ch >= 48 && ch <= 57) {
                        bufferIndex++;
                        buffer[bufferIndex] = ch;
                        ch = fgetc(input_text);
                    }
                    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~'
                        || ch == '>' || ch == '<' || ch == '!' || ch == ';' || ch == EOF || ch == '\n') {
                        ungetc(ch, input_text);
                        return INTEGER_TOKEN;
                    }
                    else if (ch == '.'){
                        bufferIndex++;
                        buffer[bufferIndex] = ch;
                        ch = fgetc(input_text);
                        if (ch >= 48 && ch <= 57){
                            int zero_count = 0;
                            int nonzero_count = 0;
                            while (ch >= 48 && ch <= 57) {
                                if (ch == '0')
                                    zero_count += 1;
                                else
                                    nonzero_count += 1;
                                bufferIndex++;
                                buffer[bufferIndex] = ch;
                                ch = fgetc(input_text);
                            }
                            if (zero_count == 1 && nonzero_count == 0)
                                return DECIMAL_POINT_TOKEN;
                            else if (nonzero_count == 0 && zero_count > 1) {
                                ungetc(ch, input_text);
                                return UNIDENTIFIED_TOKEN;
                            }
                            else if ((ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~' ||
                                      ch == '>' || ch == '<'|| ch == '!' || ch == '(' || ch == ')'  || ch == EOF ||
                                      ch == '\n') && buffer[bufferIndex - 1] != '0'){
                                ungetc(ch , input_text);
                                return DECIMAL_POINT_TOKEN;
                            }
                            else return UNIDENTIFIED_TOKEN;

                        }
                        else
                            return UNIDENTIFIED_TOKEN;
                    }
                    else
                        return UNIDENTIFIED_TOKEN;
                }
            }
            else {
                ungetc(ch, input_text);
                return MINUS_TOKEN;
            }

        case '*':
            buffer[bufferIndex] = ch;
            ch = fgetc(input_text);
            if (ch == '~') {
                return MULTIPLICATION_ASSIGNMENT_TOKEN;
            } else {
                ungetc(ch, input_text);
                return MULTIPLE_TOKEN;
            }

        case '/':
            buffer[bufferIndex] = ch;
            ch = fgetc(input_text);
            if (ch == '~') {
                return DIVISION_ASSIGNMENT_TOKEN;
            } else {
                ungetc(ch, input_text);
                return DIVIDE_TOKEN;
            }

        case '~':
            buffer[bufferIndex] = ch;
            ch = fgetc(input_text);
            if (ch == '~') {
                return EQUAL_TOKEN;
            } else {
                ungetc(ch, input_text);
                return ASSIGNMENT_TOKEN;
            }

        case '!':
            buffer[bufferIndex] = ch;
            ch = fgetc(input_text);
            if (ch == '~') {
                return NOT_EQUAL_TOKEN;
            }
            else {
                ungetc(ch, input_text);
                return UNIDENTIFIED_TOKEN;
            }

        case '>':
            buffer[bufferIndex] = ch;
            ch = fgetc(input_text);
            if (ch == '~') {
                return GREATER_EQUAL_TOKEN;
            } else {
                ungetc(ch , input_text);
                return GREATER_TOKEN;
            }

        case '<':
            buffer[bufferIndex] = ch;
            ch = fgetc(input_text);
            if (ch == '~') {
                return LESS_EQUAL_TOKEN;
            } else {
                ungetc(ch, input_text);
                return LESS_TOKEN;
            }

        case '\n':
        case ' ':
            return tokenscan(input_file);

        case '(':
        case ')':
            return PARENTHESES_TOKEN;

        case '{':
        case '}':
            return CURLY_BRACE_TOKEN;

        case '[':
        case ']':
            return BRACKET_TOKEN;

        case ';':
            return OVER_TOKEN;

        case '&':
            ch = fgetc(input_text);
            if (ch == '>') {
                do {
                    ch = fgetc(input_text);
                    if (ch == EOF)
                        return COMMENT_TOKEN;
                } while(ch != 10);
                if (ch == '\n')
                    return COMMENT_TOKEN;
            }
            else if (ch =='<') {
                while (ch != '>'){
                    ch = fgetc(input_text);
                    if (ch == EOF)
                        return COMMENT_TOKEN;
                }
                return COMMENT_TOKEN;
            }
            else
                ungetc(ch, input_text);
                return UNIDENTIFIED_TOKEN;

        case '"':
            do{
                ch = fgetc(input_text);
                if (ch == EOF)
                    return UNIDENTIFIED_TOKEN;
            } while (ch != '"');
            if (ch == '"')
                return STRING_TOKEN;

        case 'a' ... 'z':

            while ((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90) || (ch >= 48 && ch <= 57) || ch == '_') {
                buffer[bufferIndex] = ch;
                bufferIndex++;
                ch = fgetc(input_text);
            }
            if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~' || ch == '>' || ch == '<' ||
                ch == '!' || ch =='(' || ch == ')' || ch == ';' || ch == EOF || ch == '\n') {
                ungetc(ch, input_text);
            }
            else
                return UNIDENTIFIED_TOKEN;

            if (bufferIndex == 4 && strncmp(buffer, "awa", 3) == 0)
                return AND_TOKEN;
            else if (bufferIndex == 4 && strncmp(buffer, "bool", 4) == 0)
                return BOOLEAN_TOKEN;
            else if (bufferIndex == 7 && strncmp(buffer, "consoli", 7) == 0)
                return INPUT_TOKEN;
            else if (bufferIndex == 7 && strncmp(buffer, "consolo", 7) == 0)
                return OUTPUT_TOKEN;
            else if (bufferIndex == 3 && strncmp(buffer, "eth", 3) == 0)
                return OR_TOKEN;
            else if (bufferIndex == 5 && strncmp(buffer, "float", 5) == 0)
                return FLOAT_TOKEN;
            else if (bufferIndex == 3 && strncmp(buffer, "int", 3) == 0)
                return INT_TOKEN;
            else if (bufferIndex == 6 && strncmp(buffer, "nothen", 6) == 0)
                return ELSE_TOKEN;
            else if (bufferIndex == 3 && strncmp(buffer, "str", 3) == 0)
                return STR_TOKEN;
            else if (bufferIndex == 5 && strncmp(buffer, "until", 5) == 0)
                return WHILE_TOKEN;
            else if (bufferIndex == 6 && strncmp(buffer, "within", 6) == 0)
                return FOR_TOKEN;
            else if (bufferIndex == 4 && strncmp(buffer, "when", 4) == 0)
                return IF_TOKEN;
            else
                return IDENTIFIER_TOKEN;

        case 'F':
            buffer[bufferIndex] = ch;
            ch = fgetc(input_text);
            if (ch == 'a') {
                bufferIndex++;
                buffer[bufferIndex] = ch;
                ch = fgetc(input_text);
                if (ch == 'l') {
                    bufferIndex++;
                    buffer[bufferIndex] = ch;
                    ch = fgetc(input_text);
                    if (ch == 's') {
                        bufferIndex++;
                        buffer[bufferIndex] = ch;
                        ch = fgetc(input_text);
                        if (ch == 'e') {
                            bufferIndex++;
                            buffer[bufferIndex] = ch;
                            ch = fgetc(input_text);
                            if (ch == ' ' || ch == '(' || ch == ')' || ch == ';' || ch == '~' || ch == '!' || ch == EOF || ch == '\n') {
                                ungetc(ch, input_text);
                                return FALSE_TOKEN;
                            }
                        }
                    }
                }
            }

        case 'T':
            buffer[bufferIndex] = ch;
            ch = fgetc(input_text);
            if (ch == 'r') {
                bufferIndex++;
                buffer[bufferIndex] = ch;
                ch = fgetc(input_text);
                if (ch == 'u') {
                    bufferIndex++;
                    buffer[bufferIndex] = ch;
                    ch = fgetc(input_text);
                    if (ch == 'e') {
                        bufferIndex++;
                        buffer[bufferIndex] = ch;
                        ch = fgetc(input_text);
                        if (ch == ' ' || ch == '(' || ch == ')' || ch == ';' || ch == '~' || ch == '!' || ch == EOF || ch == '\n') {
                            ungetc(ch, input_text);
                            return TRUE_TOKEN;
                        }
                    }
                }
            }

        case '0' ... '9':
            if (ch == '0'){
                bufferIndex++;
                buffer[bufferIndex] = ch;
                ch = fgetc(input_text);
                if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~' || ch == '>' || ch == '<'
                || ch == '!' || ch == '(' || ch == ')' || ch == '\n' || ch == EOF){
                    return INTEGER_TOKEN;
                }
                else if (ch == '.'){
                    bufferIndex++;
                    buffer[bufferIndex] = ch;
                    ch = fgetc(input_text);
                    if (ch >= 48 && ch <= 57){
                        int zeroCount = 0;
                        int nonZeroCount = 0;
                        while (ch >= 48 && ch <= 57) {
                            if (ch == '0')
                                zeroCount += 1;
                            else
                                nonZeroCount += 1;
                            bufferIndex++;
                            buffer[bufferIndex] = ch;
                            ch = fgetc(input_text);
                        }
                        if (zeroCount == 1 && nonZeroCount == 0){
                            return DECIMAL_POINT_TOKEN;
                        }
                        if (nonZeroCount == 0 && zeroCount > 1){
                            ungetc(ch, input_text);
                            return UNIDENTIFIED_TOKEN;
                        }
                        else if ((ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~' ||
                                 ch == '>' || ch == '<'|| ch == '!' || ch == '(' || ch == ')'  || ch == EOF ||
                                 ch == '\n') && buffer[bufferIndex - 1] != '0'){
                            ungetc(ch , input_text);
                            return DECIMAL_POINT_TOKEN;
                        }
                        else return UNIDENTIFIED_TOKEN;

                    }
                    else
                        return UNIDENTIFIED_TOKEN;
                }
                else
                    return UNIDENTIFIED_TOKEN;
            }
            while (ch >= 48 && ch <= 57) {
                bufferIndex++;
                buffer[bufferIndex] = ch;
                ch = fgetc(input_text);
            }
            if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~' || ch == '>' || ch == '<' ||
                ch == '(' || ch == ')' || ch == '!' || ch == ';' || ch == EOF || ch == '\n') {
                ungetc(ch, input_text);
                return INTEGER_TOKEN;
            }
            else if (ch == '.'){
                bufferIndex++;
                buffer[bufferIndex] = ch;
                ch = fgetc(input_text);
                if (ch >= 48 && ch <= 57){
                    int zero_count = 0;
                    int nonzero_count = 0;
                    while (ch >= 48 && ch <= 57) {
                        if (ch == '0')
                            zero_count += 1;
                        else
                            nonzero_count += 1;
                        bufferIndex++;
                        buffer[bufferIndex] = ch;
                        ch = fgetc(input_text);
                    }
                    if (nonzero_count == 0 || zero_count > 1){
                        ungetc(ch, input_text);
                        return UNIDENTIFIED_TOKEN;
                    }
                    else if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~' ||
                             ch == '>' || ch == '<'|| ch == '!' || ch == '(' || ch == ')' || ch == EOF ||
                             ch == '\n' || (zero_count == 1 && buffer[bufferIndex - 1] == '0')){
                        ungetc(ch , input_text);
                        return DECIMAL_POINT_TOKEN;
                    }
                    else return UNIDENTIFIED_TOKEN;

                }
                else
                    return UNIDENTIFIED_TOKEN;
            }
            else
                return UNIDENTIFIED_TOKEN;

        default:
            return UNIDENTIFIED_TOKEN;
    }
}

int write_tokens() {

    FILE *output_file;
    char pin;

    input_file = fopen(INPUT_FILE_PATH, "r");

    if (input_file == NULL) {
        perror("Error opening \"input.txt\" file");
        return 1;
    }

    output_file = fopen(OUTPUT_FILE_PATH, "w+");

    if (output_file == NULL) {
        perror("Error opening \"output.txt\" file");
        fclose(input_file);
        return 1;
    }

    while ((pin = fgetc(input_file)) != EOF) {
        if (pin == '\n')
            fprintf(output_file, "%c", '\n');
        ungetc(pin, input_file);
        token currentToken = tokenscan(input_file);
        fprintf(output_file, "%s", strtoken(currentToken));
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}

int main() {
    write_tokens();
    return 0;
}