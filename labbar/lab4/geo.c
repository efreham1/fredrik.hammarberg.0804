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
    return  (   (  (r2->l.x-r1->l.x)>0 && (r2->l.x-r1->l.x)<dx1    ) || (   (r2->l.x-r1->l.x)<0 && (r1->l.x-r2->l.x)<dx2    )   ) 
            &&
            (   (  (r2->r.y-r1->r.y)>0 && (r2->r.y-r1->r.y)<dy1    ) || (   (r2->r.y-r1->r.y)<0 && (r1->r.y-r2->r.y)<dy2    )   );
}

rectangle_t intersection_rect(rectangle_t *r1, rectangle_t *r2){
    int xs[] = {r1->r.x, r1->l.x, r2->r.x, r2->l.x};
    int ys[] = {r1->r.y, r1->l.y, r2->r.y, r2->l.y};
    int small_x = xs[0];
    int large_x = xs[0];
    int small_y = ys[0];
    int large_y = ys[0];
    for (int i = 1; i < 4; i++){
        if (xs[i]<small_x){
            small_x = xs[i];
        }
        else if (xs[i]>large_x){
            large_x = xs[i];
        }

        if (ys[i]<small_y){
            small_y = ys[i];
        }
        else if (ys[i]>large_y){
            large_y = ys[i];
        }
    }
    rectangle_t new_rect = make_rectangle(small_x, large_x, small_y, large_y);
    return new_rect;
}

int main(void){

    rectangle_t r1 = make_rectangle(1, 6, 1, 2);
    print_rectangle(&r1);
    printf("area=%d\n", area_rect(&r1));
    rectangle_t r2 = make_rectangle(0, 2, 0, 10);
    if (intersects_rect(&r1, &r2)){
        printf("Banan, melon...");
    }
    rectangle_t r3 = intersection_rect(&r1, &r2);
    print_rectangle(&r3);
    return 0;
}