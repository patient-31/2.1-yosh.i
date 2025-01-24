/*
 * ________________________________________________________________________________
 * |  File: expander.c
 * |  Project: source
 * |  File Created: Friday, 10th January 2025 04:24 pm
 * |  Author: Chat-GPT
 */


#include "../includes/program.h"

#define MAX_EXPANDED 4096 // Maximum size for expanded input
#define MAX_TOKENS 128    // Maximum number of tokens

// Function to expand environment variables and handle quotes
char **expand_env_and_split_w_quotes(const char *input, char **env) {
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (!tokens) {
        perror("malloc");
        return NULL;
    }

    char *expanded = malloc(MAX_EXPANDED);
    if (!expanded) {
        perror("malloc");
        free(tokens);
        return NULL;
    }

    size_t out_pos = 0;
    size_t token_count = 0;
    char *current_token = expanded;

    int in_single_quote = 0;
    int in_double_quote = 0;

    for (size_t i = 0; input[i] != '\0'; i++) {
        if (out_pos >= MAX_EXPANDED - 1) {
            fprintf(stderr, "Output buffer overflow\n");
            free(tokens);
            free(expanded);
            return NULL;
        }

        if (input[i] == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
        } else if (input[i] == '"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
        } else if (input[i] == ' ' && !in_single_quote && !in_double_quote) {
            if (out_pos > 0) {
                current_token[out_pos] = '\0';
                if (token_count >= MAX_TOKENS - 1) {
                    fprintf(stderr, "Too many tokens\n");
                    free(tokens);
                    free(expanded);
                    return NULL;
                }
                tokens[token_count++] = strdup(current_token);
                current_token = &expanded[out_pos + 1];
                out_pos = 0;
            }
        } else if (input[i] == '$' && !in_single_quote) {
            char var_name[128] = {0};
            size_t var_len = 0;

            i++;
            while (isalnum(input[i]) || input[i] == '_') {
                if (var_len >= sizeof(var_name) - 1) break;
                var_name[var_len++] = input[i++];
            }
            i--; // Step back because the loop overshoots

            const char *value = get_env_yosh(var_name, env);
            if (!value) value = ""; // Default to empty string if not found

            size_t value_len = strlen(value);
            if (out_pos + value_len >= MAX_EXPANDED) {
                fprintf(stderr, "Environment variable expansion exceeds buffer limit\n");
                free(tokens);
                free(expanded);
                return NULL;
            }

            strncpy(current_token + out_pos, value, value_len);
            out_pos += value_len;
        } else {
            current_token[out_pos++] = input[i];
        }
    }

    if (out_pos > 0) {
        current_token[out_pos] = '\0';
        if (token_count >= MAX_TOKENS - 1) {
            fprintf(stderr, "Too many tokens\n");
            free(tokens);
            free(expanded);
            return NULL;
        }
        tokens[token_count++] = strdup(current_token);
    }

    tokens[token_count] = NULL;
    free(expanded);
    return tokens;
}