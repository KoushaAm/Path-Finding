#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{
/* YOUR CODE HERE */
    base = baseim; 
    maze = mazeim; 
    start = s; 
}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){

/* YOUR CODE HERE */

    RGBAPixel *pixel = im.getPixel(loc.first, loc.second); 
    pixel->r = 2 * (pixel->r /4);
    pixel->g = 2 * (pixel->g /4);
    pixel->b = 2 * (pixel->b /4);

}

// int treasureMap::shiftBits(int n, int p1, int p2) {
//     if (((n & (1 << p1)) >> p1) ^ ((n & (1 << p2)) >> p2)){
//         n ^= 1 << p1;
//         n ^= 1 << p2;
//     }

//     return n;
// }

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){

    /* YOUR CODE HERE */
    RGBAPixel *pixel = im.getPixel(loc.first, loc.second); 
    int r = pixel->r & 0b11111100;
    int g = pixel->g & 0b11111100;
    int b = pixel->b & 0b11111100;

    int v = d % 64; 
    int rd = v & 0b110000; 
    rd = rd >> 4; 
    int gd = v & 0b001100; 
    gd = gd >> 2; 
    int bd = v & 0b000011; 

    pixel->r = r + rd; 
    pixel->g = g + gd; 
    pixel->b = b + bd; 

}


PNG treasureMap::renderMap(){

/* YOUR CODE HERE */
    PNG base_copy = base; 
    vector<vector<bool>> visited; 
    vector<vector<int>> dist_origin; 
    Queue <pair<int, int>> q; 

    for (int x = 0; x < base.width(); x++) {


        vector<bool> col_v; 
        //col_v.resize(base.height());
        vector<int> col_d; 
        //col_d.resize(base.height());
        for (int y = 0; y < base.height(); y++) {
            col_v.push_back(false); 
            col_d.push_back(0);
        }

        visited.push_back(col_v);
        dist_origin.push_back(col_d);
    }

    int d = 0;
    visited[start.first][start.second] = true;
    dist_origin[start.first][start.second] = d; 
    

    setLOB(base_copy, start, d);
    q.enqueue(start);

    while (!q.isEmpty()) {

        pair<int, int> curr_loc; 
        vector<pair<int,int>> n; 
        
        curr_loc = q.dequeue();

        // assign left below right above
        n = neighbors(curr_loc);

        d = dist_origin[curr_loc.first][curr_loc.second];

        for (int i = 0; i < n.size();  i++) {

            //pair<int,int> neigbor = n[i]; 

            if (good(visited, curr_loc, n[i])) {

                visited[n[i].first][n[i].second] = true; 

                dist_origin[n[i].first][n[i].second] = d + 1;

                setLOB(base_copy, n[i], d + 1); 

                q.enqueue(n[i]);
            }
        }
    }

    return base_copy;

}


PNG treasureMap::renderMaze(){

/* YOUR CODE HERE */
    PNG base_copy = base; 
    Queue <pair<int,int>> q; 
    vector <vector <bool>> visited; 

    for (int x = 0; x < base.width(); x++) {
        vector<bool> col_v; 
        for (int y = 0; y < base.height(); y++) {
            col_v.push_back(false); 
        }
        visited.push_back(col_v);
    }

    // for start
    visited[start.first][start.second] = true; 
    setGrey(base_copy, start); 
    q.enqueue(start); 

    pair<int, int> curr; 
    vector <pair<int,int>> n; 
    
    // for the rest
    while (!q.isEmpty()) {

        curr = q.dequeue();

        // assign neigbors
        n = neighbors(curr);

        for (int i = 0; i < n.size(); i++) {

            pair<int,int> neigbor = n[i];  
            
            if (good(visited, curr, neigbor)) {
                //setGrey(PNG & im, pair<int,int> loc)

                visited[neigbor.first][neigbor.second] = true; 
                setGrey(base_copy, neigbor); 
                q.enqueue(neigbor);
            }
        }
    }

    for (int x = start.first-3; x <= start.first + 3; x++) {
        for (int y = start.second-3; y <= start.second + 3; y++) {
            if (y >= 0 && y < base_copy.height() && x >= 0 && x < base_copy.width()) {
                RGBAPixel *pixel = base_copy.getPixel(x,y); 
                pixel->r = 255;
                pixel->g = 0;
                pixel->b = 0;
            }
        }
    }

    //cout << "before render " << endl ; 
    return base_copy; 

}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */
    bool range = (next.first < base.width() && next.first >= 0 && next.second < base.height() && next.second >= 0); 
    bool isVisited = false; // default
    bool color = false; 
    if (range) {
        if (v[next.first][next.second] == true) {
            isVisited = v[next.first][next.second]; 
        }
        
        RGBAPixel *pixel_curr = maze.getPixel(curr.first, curr.second); 
        RGBAPixel *pixel_next = maze.getPixel(next.first, next.second); 
    

        color = (*pixel_curr == *pixel_next); 
        //color = (pixel_curr->r == pixel_next->r && pixel_curr->g == pixel_next->g && pixel_curr->b == pixel_next->b && pixel_curr->a == pixel_next->a);
        //cout << color << " comparing " << isVisited << endl; 
    }
    
    
    
    return (range && (!isVisited) && color);

}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {

/* YOUR CODE HERE */
    pair<int, int> left; 
    pair<int, int> below; 
    pair<int, int> right;
    pair<int, int> above; 

    left  = make_pair(curr.first-1, curr.second);
    below = make_pair(curr.first, curr.second+1);
    right = make_pair(curr.first+1, curr.second);
    above = make_pair(curr.first, curr.second-1);

    vector<pair<int, int>> n; 
    n.push_back(left);
    n.push_back(below);
    n.push_back(right);
    n.push_back(above);

    return n; 

}




    // int r_alt = d & 0b00110000; 
    // int g_alt = d & 0b00001100; 
    // int b_alt = d & 0b00000011; 

    // r_alt = shiftBits(r_alt, 0, 4); // 000000** tranfer to least two sig figs
    // r_alt = shiftBits(r_alt, 1, 5); // 000000** tranfer to least two sig figs

    // g_alt = shiftBits(g_alt, 0, 4);
    // g_alt = shiftBits(g_alt, 1, 5);

    // b_alt = shiftBits(b_alt, 0, 4);
    // b_alt = shiftBits(b_alt, 1, 5);


    // // swap the pair with the two lest sig figs of r g b 
    
    // // for (int x = 0; x < base.width(); x++) {

    // //     for (int y = 0; y < base.height(); y++) {

    // // if (loc.first == x && loc.second == y) {
    // RGBAPixel *pixel = base.getPixel(loc.first, loc.second);

    // pixel->r = pixel->r & 0b11111100; 
    // pixel->r = pixel->r ^ r_alt; 

    // pixel->g = pixel->g & 0b11111100; 
    // pixel->g = pixel->g ^ g_alt; 

    // pixel->b = pixel->b & 0b11111100; 
    // pixel->b = pixel->b ^ b_alt; 
    // // }
    //     // }
    // // }


    // for (int x = 0; x < base.width(); x++) {

    //     for (int y = 0; y < base.height(); y++) {

    //         if (loc.first == x && loc.second == y) {
    // RGBAPixel *pixel = base.getPixel(loc.first, loc.second); 
    // pixel->r = 2 * (pixel->r /4);
    // pixel->g = 2 * (pixel->g /4);
    // pixel->b = 2 * (pixel->b /4);
    //     //     }
        // }
    // }