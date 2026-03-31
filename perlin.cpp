#include <iostream>
#include <ctime>
#include <cstdlib>
#include "graphics/canvas.h"
using namespace std;

class gridNode{
    public:
    Vector2 pos;
    Vector2 gradientVector;
        gridNode(){
        gradientVector = Vector2(0.0,0.0);
        pos = Vector2(0.0,0.0);;
        }
    gridNode(Vector2 gradvec, Vector2 argpos){
        gradientVector = gradvec;
        pos = argpos;
    }
};


class vecGrid{
    public:
        

        gridNode ** grid;
        int width;
        int height;
    vecGrid(int awidth, int aheight){
        width = awidth;
        height = aheight;
        srand(time(0));

        grid = new gridNode*[height];
        for(int i = 0; i < height; i++){
            grid[i] = new gridNode[width];
        }


        for(int y =0; y < height; y++)
        {
            for(int x =0; x < width; x++)
            {
                grid[y][x] = gridNode(Vector2(rand() % 101 -50.0,rand() % 101 -50.0),Vector2((float)x,(float)y));
            }
        }
    }


    bool contain(int candidate, int * toCompare, int size){
        for(int i = 0; i < size; i++){
            if (toCompare[i] == candidate){return true;}
        }
        return false;
    }

   double smoothstep(double x){
        if(3*x*x-2*x*x*x > 1.0){return 1.0;}
        if(3*x*x-2*x*x*x < 0.0){return 0.0;}
        return  3*x*x-2*x*x*x;
}
    Vector2 getGrad(Vector2 node){
        return grid[(int)(node.y) %height ][(int)(node.x) %width ] .gradientVector;
    }

    double getValue(Vector2 a){
        Vector2 gridbase = Vector2(floor(a.x),floor(a.y));
        Vector2 delta = (gridbase-a);
        Vector2 dotx = Vector2(Vector2::dotproduct(getGrad(gridbase),delta),Vector2::dotproduct(getGrad(gridbase+Vector2(1.0,0.0)),(gridbase+Vector2(1.0,0.0)-a)));
        Vector2 doty = Vector2(Vector2::dotproduct(getGrad(gridbase+Vector2(0.0,1.0)),(gridbase+Vector2(0.0,1.0))-a),Vector2::dotproduct(getGrad(gridbase+Vector2(1.0,1.0)),(gridbase+Vector2(1.0,1.0)-a)));


        double ix = dotx.x + (dotx.y - dotx.x)*smoothstep(delta.x);
        double ix1 = doty.x + (doty.y - doty.x)*smoothstep(delta.x);

        return ix+(ix1-ix)*smoothstep(delta.y);

    }

};




int main(){
    int size;
    cout << "size?";
    cin >> size;

    int Isdebug;
    cout << "debug? 0 ou 1";
    cin >> Isdebug;



    vecGrid perlin(size,size);
    vecGrid perlin2(size*2,size*2);


    canvas ctx;
    ctx.initiate();

    int range;
    cout << "range?\n\t";
    cin >> range;
    range = ctx.clamps(range,0,ctx.resolution);

    int octave;
    cout << "octaves?\n\t";
    cin >> octave;
    ctx.treatment([&](int x , int y, int i){
                Vector2 cand = Vector2((double)x / (double)ctx.width   * (double)perlin.width,(double)y / (double)ctx.height * (double)perlin.height);
                  return (int)floor(((range/2.0) + perlin.getValue(cand)*(range/2.0)));
    });
    for (int index = 0; index < octave; index++){
        vecGrid operlin((int)(size * pow(2.0,index)),(int)(size * pow(2.0,index)));
        canvas octx = canvas(ctx.width,ctx.height,0);

            octx.treatment([&](int x , int y, int i){
                Vector2 cand = Vector2((double)x / (double)octx.width   * (double)perlin.width,(double)y / (double)octx.height * (double)operlin.height);
                  return (int)floor((range/2.0) +(operlin.getValue(cand)*(range/2.0)*pow(0.4,index)));
        ctx = ctx + octx;
    });

    }

        if(Isdebug == 1){

        
        for(int y =0; y < perlin.height; y++)
        {
            for(int x =0; x < perlin.width; x++)
            {
                Vector2 base = Vector2((double)x / (double)perlin.width * (double)ctx.width,(double)y / (double)perlin.height * (double)ctx.height);
                ctx.drawLine(base,base+perlin.getGrad(Vector2((double)x,(double)y)).unit()*3,91);
            }
        }
        }
        Sleep(1000);

        ctx.Update();

        /*Vector2 pivot(5,5);
        double t =0.0;*/
while (true){
/*Sleep(1000/3);
    

    ctx.treatment([&](int x , int y, int i){
        Vector2 offset =  Vector2((double)ctx.midwidth,(double)ctx.midheight) - Vector2((double)x,(double)y);
        return (int)(1.0 + Vector2::dotproduct(offset,pivot.rotate(t)));
    }
        );
        t += 3.0;
        cout << t ;
ctx.Update();*/
}
    return 0;
}