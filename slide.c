#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "slide.h"

Slide *new_slide(int contentLength){
  Slide *s = (Slide *)malloc(sizeof(Slide));
  s->content = (char *)calloc(sizeof(char), contentLength);
  return s;
}

void del_slide(Slide *s){
  free(s->content);
  free(s);
}


