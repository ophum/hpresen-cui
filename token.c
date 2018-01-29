#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "token.h"

Token *new_token(){
  Token *t = (Token *)malloc(sizeof(Token));
  t->next = NULL;
  t->prev = t;
  return t;
}

void add_token(char *t, int type, Token *tokens){
  Token *last = tokens->prev;

  last->next = (Token *)malloc(sizeof(Token));
  last->next->prev = last;
  last->next->next = NULL;
  tokens->prev = last->next;

  last = last->next;

  last->t = (char *)malloc(sizeof(char) * (strlen(t) + 1));
  strncpy(last->t, t, strlen(t));
  last->t[strlen(t)] = '\0';
  last->type = type;
}

void del_token(Token *t){
  if(t != NULL){
    if(t->t != NULL) free(t->t);
    free(t);
  }
}

void del_tokens(Token *head){
  Token *del;

  while((del = head) != NULL){
    head = head->next;
    del_token(del);
  }
}

Token *next_token(Token *t){
  return t->next;
}

Token *prev_token(Token *t){
  return t->prev;
}

char *get_token(Token *t){
  return t->t;
}

int get_type_token(Token *t){
  return t->type;
}

static int getFileSize(char *filename){
  int size = 0;
  FILE *fp;

  if((fp = fopen(filename, "r")) != NULL){
    fseek(fp, 0L, SEEK_END);
    size = (int)ftell(fp);
  }
  return size;
}

static int delimiterList[256];

void initDelimiter(){
  int i;
  for(i = '0'; i <= '9'; i++){
    delimiterList[i] = 0;
  }

  for(i = 'a'; i <= 'z'; i++){
    delimiterList[i] = 0;
  }

  for(i = 'A'; i <= 'Z'; i++){
    delimiterList[i] = 0;
  }

  for(i = ' '; i <= '/'; i++){
    delimiterList[i] = 1;
  }

  for(i = ':'; i <= '@'; i++){
    delimiterList[i] = 1;
  }

  for(i = '['; i <= '`'; i++){
    delimiterList[i] = 1;
  }

  for(i = '{'; i <= '~'; i++){
    delimiterList[i] = 1;
  }

  delimiterList['\n'] = 1;
}

static int isDelimiter(char ch){
  return delimiterList[ch];
}

Token *Tokenize(char *filename){
  Token *head = new_token();
  FILE *fp;
  int tok_size;
  int i;
  int filesize = getFileSize(filename);
  char *file;
  char delimiter;

  initDelimiter();

  if(filesize == 0 || (fp = fopen(filename, "r")) == NULL){
    return NULL;
  }

  file = (char *)malloc(sizeof(char) * filesize);
  fread(file, sizeof(char), filesize, fp);
  fclose(fp);

  for(int i = 0; i < filesize; i++){
    switch(file[i]){
    default: // デリミタまでをトークンとする
      for(tok_size = 0; !isDelimiter(file[i + tok_size]); tok_size++);
      delimiter = file[i + tok_size];
      file[i+tok_size] = '\0';
      add_token(&file[i], 0, head);
      add_token(&delimiter, 1, head);
      i += tok_size;
      break;
    }
  }
  free(file);
  return head;
}
