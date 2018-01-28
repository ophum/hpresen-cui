#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef struct TAG_SLIDE Slide;
struct TAG_SLIDE{
  char *content;
};

Slide *new_slide(int contentLength){
  Slide *s = (Slide *)malloc(sizeof(Slide));
  s->content = (char *)calloc(sizeof(char), contentLength);
  return s;
}

void del_slide(Slide *s){
  free(s->content);
  free(s);
}

int main(int argc, char **argv){
  Slide *slide[3];
  int i;
  
  for(i = 0; i < 3; i++){
    slide[i] = new_slide(1024); 
  }

  strncpy(slide[0]->content, "hogeaaaaaa\naaaaaa", 1024);
  strncpy(slide[1]->content, "nyan", 1024);
  strncpy(slide[2]->content, "foo", 1024);

  initscr();
  start_color();
  cbreak();
  noecho();

  i = 0;
  while(getch() != 'q'){
    if(i == sizeof(slide) / sizeof(Slide)) break;
    erase();
    printw("%s", slide[i]->content);
    i++;
  }

  nocbreak();
  echo();
  endwin();  

  return 0;
}
