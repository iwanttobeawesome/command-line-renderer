#include <iostream> //cout
#include <unistd.h> //usleep
#include <algorithm> //find_if
#include <vector> //vectors
#include <stdlib.h> //forgot
#include <cmath> //floor ceil etc
//VERSION 1.2!!!
//added vector instead of array to make screen size variable
unsigned long framecount;
float cx = 0.0f;
float cy = 0.0f;
float cz = 0.0f;
const int width = 28;
const int height = 14;
//30 * 15 seems to be the limit here before it stops clearing the console. could circumvent this by rendering in chunks
typedef struct{
    float x,y;
}point;
typedef struct{
    point rp;
    float x, y, z;
}point3d;
char chars[] = {'.','#'};
std::vector<int> buffer; // display buffer
std::vector<point*> points;
std::vector<point3d*> point3ds;
void isnum(string input){
  std::vector<int>::iterator it = std::find_if(string.begin(),string.end(),
}
int getplace(float x, float y){
    return floor(x)+floor(y)*width;
}
void drawline(float x1, float x2, float y1, float y2){
    //if statement here in case of negative
   if(x2 > x1){
  for(float i = x1; i< x2; i++){
      if(i > width || i < 0 ||(y1 + (y2-y1) * (i - x1) / (x2-x1)) < 0 || (y1 + (y2-y1) * (i - x1) / (x2-x1)) >= height){
          break;
      }
    buffer[getplace(i, y1 + (y2-y1) * (i - x1) / (x2-x1))] = 1;
    
  }
   }else{
        for(float i = x1; i< x2; i--){
      if(i > width || i < 0 ||(y1 + (y2-y1) * (i - x1) / (x2-x1)) < 0 || (y1 + (y2-y1) * (i - x1) / (x2-x1)) >= height){
          break;
      }
    buffer[getplace(i, y1 + (y2-y1) * (i - x1) / (x2-x1))] = 1;
    
  }
   }
   
}
void renderscreen(){
     std::cout << "\x1B[2J\x1B[H"; //clears console
    for(int r = 1; r < (width*height)+1; r++){
         std::cout << chars[buffer[r-1]];
         if(r%width == 0 && r!= 0){
            std::cout << std::endl;
         }
    }
}
int addpoint(float x,float y){
   points.push_back(new point({x,y}));
}

void fillbuffer(){
    for(int i = 0; i < width*height; i++){
        buffer.push_back(0);
    }
}
void clearbuffer(){
    for(int i = 0; i < width*height; i++){
        buffer[i] = 0;
    }
}
void processbuffer(){
    for(auto & e: points){
        if(e->x > width || e->x < 0 || e->y < 0 || e->y >= height){
            continue;
        }
        int loc = floor(e->x)+floor( (e->y))*width;
        buffer[loc] = 1;
    }
}

void func(){
   points[1]->y = 8+  sin(framecount/12) * 3;
    //points[0]->y = 6;
    points[0]->y = 4+ cos(framecount/12)*3;
    drawline(points[0]->x,points[1]->x,points[0]->y,points[1]->y);
    for(auto p3d: point3ds){
       p3d->rp.x = p3d->x;
    }
} //lil function to do things and test
int main(){
    addpoint(1,2);
    addpoint(7,2);
    fillbuffer();
    do{
        clearbuffer();
        func();
        processbuffer();
        renderscreen();
        
        usleep(16666);
        framecount++;
    }while(1>0);
    return 0;
}