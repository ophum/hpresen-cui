#ifndef DEF_SLIDE_H
#define DEF_SLIDE_H

typedef struct TAG_SLIDE Slide;
struct TAG_SLIDE{
  char *content;
};

Slide *new_slide(int);
void del_slide(Slide *);

#endif /* DEF_SLIDE_H */
