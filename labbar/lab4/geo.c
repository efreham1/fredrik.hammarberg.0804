#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct point
{
  int x;
  int y;
};
typedef struct point point_t;
struct rectangle
{
    point_t l;
    point_t r;
};
typedef struct rectangle rectangle_t;


void translate(point_t *p1, point_t *p2){
  p1->x += p2->x;
  p1->y += p2->y;
}

void print_point(point_t *p){
    printf("point(%d, %d)", p->x, p->y);
}

void print_rectangle(rectangle_t *r){
    printf("rectangle(upper_left=");
    print_point(&r->l);
    printf(", lower_right=");
    print_point(&r->r);
    printf(")\n");
}

point_t make_point(int x, int y){
    point_t p = {.x = x, .y = y};
    return p;
}

rectangle_t make_rectangle(int x1, int x2, int y1, int y2){
    if (x1>x2){
        int tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    if (y1<y2){
        int tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
    point_t p1 = make_point(x1, y1);
    point_t p2 = make_point(x2, y2);
    rectangle_t r = {.l = p1, .r = p2};
    return r;
}

int area_rect(rectangle_t *r){
    int dx = abs(r->l.x-r->r.x);
    int dy = abs(r->l.y-r->r.y);
    return dx*dy;
}

bool intersects_rect(rectangle_t *r1, rectangle_t *r2){
    int dx1 = abs(r1->l.x-r1->r.x);
    int dy1 = abs(r1->l.y-r1->r.y);
    int dx2 = abs(r2->l.x-r2->r.x);
    int dy2 = abs(r2->l.y-r2->r.y);
    return ;
}

int main(void){

    rectangle_t r = make_rectangle(1, 6, 1, 2);
    print_rectangle(&r);
    printf("area=%d\n", area_rect(&r));
    return 0;
}