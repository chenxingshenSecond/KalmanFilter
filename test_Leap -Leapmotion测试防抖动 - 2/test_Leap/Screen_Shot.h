// 
#pragma once
#ifndef _SCREEN_SHOT_HEADER_
#define _SCREEN_SHOT_HEADER_ 


#include <algorithm>
#include <stdio.h>
#include "stdlib.h"
#include "math.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>   // include important windows stuff

#define BITMAP_ID            0x4D42 // universal id for a bitmap
// 
// �÷� ��Ҫ����һЩ�������洢δ����IV����
// 
using namespace std;

class SCREEN_SHOT
{
public:
	GLbyte      * data  ;
	int   If_SaveImage  ;
	int   First_Flag    ;
	char* filename_BMP  ;



	bool   Msaa_Flag  ;  
	//  ���Լ�����ͨ������MSAA_fbo ������msaa��FBO   // 
	// 
	int Texture_width  ;
	int Texture_height ;
	// 
	SCREEN_SHOT::SCREEN_SHOT(); 
	SCREEN_SHOT::~SCREEN_SHOT(); 

	void SCREEN_SHOT::Disable_Save()   ;
	void SCREEN_SHOT::Process_Key()   ; 
	bool SCREEN_SHOT::writeBMP   ( const char filename[] , unsigned int w, unsigned int h);  
	//bool SCREEN_SHOT::writeBMP_from_Data(const char filename[], unsigned char* data, unsigned int w, unsigned int h) ;OT::screenshot( char* filename) ; 
	bool SCREEN_SHOT::writeBMP_from_Data(const char filename[], unsigned char* data, unsigned int w, unsigned int h) ; 
	bool SCREEN_SHOT::writeSingle_BMP_from_Data( const char filename[], unsigned char* data, unsigned int w, unsigned int h) ; 
	bool SCREEN_SHOT::writeSingle_BMP_from_Data( const char filename[], const unsigned char* data, unsigned int w, unsigned int h) ;

protected: 

private: 

};

#endif