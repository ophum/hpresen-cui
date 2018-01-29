#ifndef DEF_TOKEN_H
#define DEF_TOKEN_H

typedef struct TAG_TOKEN Token;
struct TAG_TOKEN{
    char *t;
    int type;
    Token *prev, *next;
};

Token *new_token();

void add_token(char *, int, Token *);
void del_token(Token *);
void del_tokens(Token *);
Token *next_token(Token *);
Token *prev_token(Token *);

char *get_token(Token *);
int get_type_token(Token *);

#endif /* DEF_TOKEN_H */
