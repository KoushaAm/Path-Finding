#define CATCH_CONFIG_MAIN

#include <iostream>
#include <limits.h>
#include <sys/stat.h>
#include <vector>

#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"
#include "cs221util/catch.hpp"

#include "decoder.h"
#include "treasureMap.h"

using namespace std;
using namespace cs221util;


#define IMAGEDIR "images/"
#define SOLNIMGDIR "soln_images/"

/**
 * Test Cases
 * these are just examples of a logical flow similar to 
 * that of main.cpp. We suggest decoupling the embedding
 * tests from the decoding tests, but we leave it to you
 * to do so.
 */

TEST_CASE("my test") {
    PNG maze;
	maze.readFromFile("images/zdesmaze.png");
	pair<int,int> start(69,359);

    PNG base;
    base.readFromFile("images/zdesbase.png");
    treasureMap M(base, maze, start);

    PNG treasure = M.renderMap();
	treasure.writeToFile("images/zdesbase(test).png");
    PNG treasuremaze = M.renderMaze(); 
    PNG treasuremazeans;
    treasuremazeans.readFromFile("images/zdesgreyedmaze.png");
    treasuremaze.writeToFile("images/zdesgreyedmaze(test).png");
    treasuremazeans.readFromFile("images/zdesgreyedmaze(test).png");
    REQUIRE(treasuremazeans == treasuremaze);
    //s" << endl;

    decoder dec(treasure, start); 

    PNG soln = dec.renderSolution(); 
    soln.writeToFile("images/zdessoln(test).png");
    PNG solnans; 
    solnans.readFromFile("images/zdessoln.png");
    REQUIRE(soln== solnans);
    //cout << "render pass" << endl;

}


// TEST_CASE ("test 2") {
//     PNG maze;
// 	maze.readFromFile("images/snake.png");
// 	pair<int,int> start(1,1);

//     PNG base;
//     base.readFromFile("images/sunshine.png");

//     treasureMap M(base, maze, start);

//     PNG treasure = M.renderMap();
// 	treasure.writeToFile("images/embeddedsnake(test).png");
//     PNG treasureans;
//     treasureans.readFromFile("images/embeddedsnake.png");
//     REQUIRE( treasure == treasureans );

//     PNG treasuremaze = M.renderMaze();
// 	treasuremaze.writeToFile("images/greyedsnake(test).png");
//     PNG treasuremazeans;
// 	treasuremazeans.readFromFile("images/greyedsnake.png");
//     REQUIRE( treasuremaze == treasuremazeans );

//     decoder dec(treasure,start);

//     PNG soln = dec.renderSolution();
//     soln.writeToFile("images/solnsnake(test).png");
//     PNG solnans;
//     solnans.readFromFile("images/solnsnake.png");
//     REQUIRE( soln == solnans );
// }



TEST_CASE("treasureMap::basic no cycles", "[weight=1][part=treasureMap]")
{

    PNG maze;
	maze.readFromFile("images/snake.png");
	pair<int,int> start(1,1);

    PNG base;
    base.readFromFile("images/sunshine.png");

    treasureMap M(base, maze, start);
    

    PNG treasure = M.renderMap();
    //std:: cout<< "HI" << std:: endl; 
	treasure.writeToFile("images/embeddedsnake(test).png");
    PNG treasureans;
    treasureans.readFromFile("images/embeddedsnake.png");
    REQUIRE( treasure == treasureans );

    PNG treasuremaze = M.renderMaze();
	treasuremaze.writeToFile("images/greyedsnake(test).png");
    PNG treasuremazeans;
	treasuremazeans.readFromFile("images/greyedsnake.png");
    REQUIRE( treasuremaze == treasuremazeans );

    decoder dec(treasure,start);

    PNG soln = dec.renderSolution();
    soln.writeToFile("images/solnsnake(test).png");
    PNG solnans;
    solnans.readFromFile("images/solnsnake.png");
    REQUIRE( soln == solnans );

    PNG solnmaze = dec.renderMaze();
    solnmaze.writeToFile("images/solnsnakemaze(test).png");
    PNG solnmazeans;
    solnmazeans.readFromFile("images/solnsnakemaze.png");
    REQUIRE( solnmaze == solnmazeans );

}

TEST_CASE("decoder::basic cycles", "[weight=1][part=decoder]")
{
	PNG maze;
	maze.readFromFile("images/maze.png");
	pair<int,int> start(1,1);

    PNG base;
    base.readFromFile("images/sunshine.png");

    treasureMap M(base, maze, start);

    PNG treasure = M.renderMap();
	treasure.writeToFile("images/embeddedmaze(test).png");
    PNG treasureans;
    treasureans.readFromFile("images/embeddedmaze.png");
    REQUIRE( treasure == treasureans );

    PNG treasuremaze = M.renderMaze();
	treasuremaze.writeToFile("images/greyedmaze(test).png");
    PNG treasuremazeans;
	treasuremazeans.readFromFile("images/greyedmaze.png");
    REQUIRE( treasuremaze == treasuremazeans );

    decoder dec(treasure,start);

    PNG soln = dec.renderSolution();
    soln.writeToFile("images/solnmaze(test).png");
    PNG solnans;
    solnans.readFromFile("images/solnmaze.png");
    REQUIRE( soln == solnans );

    PNG solnmaze = dec.renderMaze();
    solnmaze.writeToFile("images/solnmazemaze(test).png");
    PNG solnmazeans;
    solnmazeans.readFromFile("images/solnmazemaze.png");
    REQUIRE( solnmaze == solnmazeans );

}

