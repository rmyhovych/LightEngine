cmake_minimum_required (VERSION 3.8)

FILE(GLOB_RECURSE 
	
	PicoEngineSRC 
	
	
	src
	*.cpp)

FILE(GLOB_RECURSE

	PicoEngineHDR
	
	src
	*.h)

ADD_LIBRARY(PicoEngine ${PicoEngineSRC} ${PicoEngineHDR})