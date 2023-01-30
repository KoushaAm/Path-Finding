#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {
   
   start = s; 
   mapImg = tm; 

   vector<vector<bool>> visited; 
   vector<vector<int>> dist_origin; 
   //vector<vector<pair<int,int>>> coord_origin; 
   Queue<pair<int, int>> q; 
   
   for (int i = 0; i < mapImg.width(); i++) {
      vector<bool> col_v;
      for (int k = 0; k < mapImg.height(); k++) {
         col_v.push_back(false);
      }

      visited.push_back(col_v);
   }

   // occupy visited and dist_origin
   for (int x = 0; x < mapImg.width(); x++) {
      vector<int> col_d;  
      
      //col_d.resize(mapImg.height()); 
      for (int y = 0; y < mapImg.height(); y++) {
         col_d.push_back(0);
      }
      dist_origin.push_back(col_d);
   }


   // coords since start 
   for (int x = 0; x < mapImg.width(); x++) {
      
      vector<pair<int,int>> col_c; 
      for (int y = 0; y < mapImg.height(); y++) {
         col_c.push_back(make_pair(-1,-1));
      }
      //col_c.resize(mapImg.height());

      coord_origin.push_back(col_c);
   }

   // start
   int d = 0; 
   visited[start.first][start.second] = true;
   dist_origin[start.first][start.second] = d; 
   coord_origin[start.first][start.second] = start; // keeps track of the parent
   pathPts.push_back(start);

   q.enqueue(start);

   //for rest
   while (!q.isEmpty()) {

        pair<int, int> curr_loc; 
        vector<pair<int,int>> n; 
        
        curr_loc = q.dequeue();

        // assign left below right above
        n = neighbors(curr_loc);

        d = dist_origin[curr_loc.first][curr_loc.second];

        for (int i = 0; i < n.size();  i++) {
            if (good(visited, dist_origin, curr_loc, n[i])) {
               visited[n[i].first][n[i].second] = true; 
               dist_origin[n[i].first][n[i].second] = d + 1;
               coord_origin[n[i].first][n[i].second] = curr_loc;
               pathPts.push_back(n[i]);
               q.enqueue(n[i]);
            }
        }
   }

   int farthest_coord_index = 0; 
   
   
   for (int i = 0; i < pathLength(); i++) {

      pair<int, int> acc = pathPts[farthest_coord_index]; 
      pair<int, int> curr = pathPts[i]; 

      if (dist_origin[curr.first][curr.second] >= dist_origin[acc.first][acc.second]) {
         farthest_coord_index = i; 
      }
      
   }

   pair <int, int> farthest_coord = pathPts[farthest_coord_index];

   Stack <pair<int, int>> sln_path; 
   pair<int,int> curr_path = farthest_coord; 
   sln_path.push(curr_path); 

   while (sln_path.peek() != start) {
      curr_path = coord_origin[curr_path.first][curr_path.second];
      sln_path.push(curr_path); 
   }

   vector <pair<int,int>> sln_final; 

   while (!sln_path.isEmpty()) {
      pair<int, int> newStep = sln_path.pop(); 
      sln_final.push_back(newStep); 
   }


   pathPts = sln_final; 
   //cout<< "size (" << pathPts.size()<< ")"  << endl;
   
}

PNG decoder::renderSolution(){

/* YOUR CODE HERE */

   PNG mapImg_copy = mapImg;

   for (int i = 0; i < pathLength(); i++) {

      //cout<< pathPts[i].first << ", " << pathPts[i].second << endl;

      RGBAPixel *pixel = mapImg_copy.getPixel(pathPts[i].first, pathPts[i].second);
      pixel->r = 255; 
      pixel->g = 0; 
      pixel->b = 0; 

   }

   return mapImg_copy;
   
   

}

PNG decoder::renderMaze(){

/* YOUR CODE HERE */
   PNG mapImg_copy = mapImg; 

   Queue <pair<int,int>> q; 
   vector <vector <bool>> visited; 
   vector<vector<int>> dist_origin; 

   for (int x = 0; x < mapImg.width(); x++) {


        vector<bool> col_v; 
        vector<int> col_d; 
        
        for (int y = 0; y < mapImg.height(); y++) {
            col_v.push_back(false); 
            col_d.push_back(0);
        }

        visited.push_back(col_v);
        dist_origin.push_back(col_d);
   }


   // for start
   int d = 0;
   visited[start.first][start.second] = true; 
   dist_origin[start.first][start.second] = 0; 
   setGrey(mapImg_copy, start); 
   q.enqueue(start); 

   pair<int, int> curr_loc; 
   vector <pair<int,int>> n; 
   
   // for the rest
   while (!q.isEmpty()) {

      curr_loc = q.dequeue();

      // assign neigbors
      n = neighbors(curr_loc);

      for (int i = 0; i < n.size(); i++) {

         pair<int,int> neigbor = n[i];  
         d = dist_origin[curr_loc.first][curr_loc.second];
         
         if (good(visited, dist_origin, curr_loc, neigbor)) {
               setGrey(mapImg_copy, neigbor); 
               visited[neigbor.first][neigbor.second] = true; 
               dist_origin[neigbor.first][neigbor.second] = d+1;
               q.enqueue(neigbor);
         }
      }
   }

   for (int x = start.first-3; x <= start.first + 3; x++) {
      for (int y = start.second-3; y <= start.second + 3; y++) {
         if (y >= 0 && y < mapImg_copy.height() && x >= 0 && x < mapImg_copy.width()) {
               RGBAPixel *pixel = mapImg_copy.getPixel(x,y); 
               pixel->r = 255;
               pixel->g = 0;
               pixel->b = 0;
         }
      }
   }

   ///cout<< mapImg_copy.height()<< " width & height" << mapImg_copy.width()<< endl; 
   return mapImg_copy; 

}

void decoder::setGrey(PNG & im, pair<int,int> loc){

/* YOUR CODE HERE */
   RGBAPixel *pixel = im.getPixel(loc.first, loc.second); 
   pixel->r = 2 * (pixel->r /4);
   pixel->g = 2 * (pixel->g /4);
   pixel->b = 2 * (pixel->b /4);

}

pair<int,int> decoder::findSpot(){

/* YOUR CODE HERE */
   return pathPts[pathPts.size()-1];
}

int decoder::pathLength(){

/* YOUR CODE HERE */
   return pathPts.size(); 
}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */
   bool range = (next.first < mapImg.width() && next.first >= 0 && next.second < mapImg.height() && next.second >= 0); 
   bool isVisited = false; 
   bool compared = false; 

   if (range) {
      if (v[next.first][next.second] == true) {
         isVisited = true; 
      }

      RGBAPixel *pixel = mapImg.getPixel(next.first, next.second);
      compared  = compare(*pixel, d[curr.first][curr.second]);
   }
   
   //decoder::compare(RGBAPixel p, int d)
   

   return range && (!isVisited) && compared; 

}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {

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


bool decoder::compare(RGBAPixel p, int d){

/* YOUR CODE HERE */
   // int r = p.r & 0b00000011;
   // r = r % 64; 
   // r = r << 4; 

   // int g = p.g & 0b00000011;
   // g = g % 64; 
   // g = g << 2; 

   // int b = p.b & 0b00000011;
   // b = b % 64; 

   // int pd = r + g + b; 

   int pd = ((p.r % 4) * 16) + ((p.g % 4) * 4) + (p.b % 4);

   return pd == ((d+1) % 64);


}
