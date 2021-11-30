#include "Screen_Shot.h"

SCREEN_SHOT::SCREEN_SHOT()
{
	If_SaveImage  = 0 ;
	filename_BMP  = (char*) malloc(30*sizeof(char)); 
	First_Flag    = 1  ; // 必须为int 类型 
	num_samples   = 8 ;
	Msaa_Flag     = true  ; // 
}
SCREEN_SHOT::~SCREEN_SHOT(){} ;
// 
void SCREEN_SHOT::Process_Key()   
{
	cin.getline(filename_BMP ,30);
	If_SaveImage = 1 ; 
}
// 
void SCREEN_SHOT::Disable_Save()   
{
	If_SaveImage = 0 ;
}
//  
void SCREEN_SHOT::GET_Texture( GLuint texture_id , int Size_X , int Size_Y)  
{
	if (If_SaveImage==1)
	{
		if ( ( data = (GLbyte*) malloc( sizeof(unsigned char)*Size_X*Size_Y*3) )   )
		{
			glEnable(GL_TEXTURE_2D);  
			glBindTexture(GL_TEXTURE_2D , texture_id );  
			glGetTexImage(GL_TEXTURE_2D,0,GL_BGR,GL_UNSIGNED_BYTE,data);  
			glDisable(GL_TEXTURE_2D);  
			writeBMP(filename_BMP ,  Size_X  , Size_Y  );
			free ( data ) ; 
		}
		else
		{
			cout<<"Not enough space "<<endl ;
		}
	}
}
// 
bool SCREEN_SHOT::writeSingle_BMP_from_Data( const char filename[], unsigned char* data, unsigned int w, unsigned int h)
{
	std::ofstream out_file;

	/** 检查data */
	if(!data) 
	{
		std::cerr << "data corrupted! " << std::endl;
		out_file.close();
		return false;
	}

	/** 创建位图文件信息和位图文件头结构 */
	BITMAPFILEHEADER header;
	BITMAPINFOHEADER bitmapInfoHeader;

	//unsigned char textureColors = 0;/**< 用于将图像颜色从BGR变换到RGB */

	/** 打开文件,并检查错误 */
	out_file.open(filename, std::ios::out | std::ios::binary);
	if (!out_file)
	{
		std::cerr << "Unable to open file " << filename << std::endl;
		return false;
	}

	/** 填充BITMAPFILEHEADER */
	header.bfType = BITMAP_ID;
	header.bfSize = w*h  + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	header.bfReserved1 = 0;
	header.bfReserved2 = 0;
	header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	/** 写入位图文件头信息 */
	out_file.write((char*)&header, sizeof(BITMAPFILEHEADER));

	/** 填充BITMAPINFOHEADER */
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biWidth    = w;
	bitmapInfoHeader.biHeight   = h;
	bitmapInfoHeader.biPlanes   = 1;
	bitmapInfoHeader.biBitCount = 8;
	bitmapInfoHeader.biCompression = BI_RLE8; // BI_RLE4 BI_RLE8
	bitmapInfoHeader.biSizeImage = w * h  ; // 当压缩类型为BI_RGB是也可以设置为0
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;
	/** 写入位图文件信息 */
	out_file.write((char*)&bitmapInfoHeader, sizeof(BITMAPINFOHEADER));

	/** 将指针移到数据开始位置 */
	out_file.seekp(header.bfOffBits, std::ios::beg);

	/** 写入图像数据 */
	out_file.write((const char*)data, bitmapInfoHeader.biSizeImage);

	out_file.close();
	return true;
}
// 

// 
bool SCREEN_SHOT::writeSingle_BMP_from_Data( const char filename[], const unsigned char* data, unsigned int w, unsigned int h)
{
	std::ofstream out_file;

	/** 检查data */
	if(!data) 
	{
		std::cerr << "data corrupted! " << std::endl;
		out_file.close();
		return false;
	}

	/** 创建位图文件信息和位图文件头结构 */
	BITMAPFILEHEADER header;
	BITMAPINFOHEADER bitmapInfoHeader;

	//unsigned char textureColors = 0;/**< 用于将图像颜色从BGR变换到RGB */

	/** 打开文件,并检查错误 */
	out_file.open(filename, std::ios::out | std::ios::binary);
	if (!out_file)
	{
		std::cerr << "Unable to open file " << filename << std::endl;
		return false;
	}

	/** 填充BITMAPFILEHEADER */
	header.bfType = BITMAP_ID;
	header.bfSize = w*h + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	header.bfReserved1 = 0;
	header.bfReserved2 = 0;
	header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	/** 写入位图文件头信息 */
	out_file.write((char*)&header, sizeof(BITMAPFILEHEADER));

	/** 填充BITMAPINFOHEADER */
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biWidth    = w;
	bitmapInfoHeader.biHeight   = h;
	bitmapInfoHeader.biPlanes   = 1;
	bitmapInfoHeader.biBitCount = 8;
	bitmapInfoHeader.biCompression = BI_RLE8; // BI_RLE4 BI_RLE8
	bitmapInfoHeader.biSizeImage = w * h  ; // 当压缩类型为BI_RGB是也可以设置为0
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;
	/** 写入位图文件信息 */
	out_file.write((char*)&bitmapInfoHeader, sizeof(BITMAPINFOHEADER));

	/** 将指针移到数据开始位置 */
	out_file.seekp(header.bfOffBits, std::ios::beg);

	/** 写入图像数据 */
	out_file.write(  (const char*)data, bitmapInfoHeader.biSizeImage);

	out_file.close();
	return true;
}
// 

// 
bool SCREEN_SHOT::writeBMP_from_Data(const char filename[], unsigned char* data, unsigned int w, unsigned int h)
{
	std::ofstream out_file;

	/** 检查data */
	if(!data) 
	{
		std::cerr << "data corrupted! " << std::endl;
		out_file.close();
		return false;
	}

	/** 创建位图文件信息和位图文件头结构 */
	BITMAPFILEHEADER header;
	BITMAPINFOHEADER bitmapInfoHeader;

	//unsigned char textureColors = 0;/**< 用于将图像颜色从BGR变换到RGB */

	/** 打开文件,并检查错误 */
	out_file.open(filename, std::ios::out | std::ios::binary);
	if (!out_file)
	{
		std::cerr << "Unable to open file " << filename << std::endl;
		return false;
	}

	/** 填充BITMAPFILEHEADER */
	header.bfType = BITMAP_ID;
	header.bfSize = w*h*3 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	header.bfReserved1 = 0;
	header.bfReserved2 = 0;
	header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	/** 写入位图文件头信息 */
	out_file.write((char*)&header, sizeof(BITMAPFILEHEADER));

	/** 填充BITMAPINFOHEADER */
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biWidth    = w;
	bitmapInfoHeader.biHeight   = h;
	bitmapInfoHeader.biPlanes   = 1;
	bitmapInfoHeader.biBitCount = 24;
	bitmapInfoHeader.biCompression = BI_RGB; // BI_RLE4 BI_RLE8
	bitmapInfoHeader.biSizeImage = w * h * 3; // 当压缩类型为BI_RGB是也可以设置为0
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;
	/** 写入位图文件信息 */
	out_file.write((char*)&bitmapInfoHeader, sizeof(BITMAPINFOHEADER));

	/** 将指针移到数据开始位置 */
	out_file.seekp(header.bfOffBits, std::ios::beg);

	/** 写入图像数据 */
	out_file.write((char*)data, bitmapInfoHeader.biSizeImage);

	out_file.close();
	return true;
}
// 
//
bool SCREEN_SHOT::writeBMP(const char filename[] , unsigned int w, unsigned int h)
{
	std::ofstream out_file;
	/** 检查data */
	if(!data) 
	{
		std::cerr << "data corrupted! " << std::endl;
		out_file.close();
		return false;
	} 
	/** 创建位图文件信息和位图文件头结构 */
	BITMAPFILEHEADER header;
	BITMAPINFOHEADER bitmapInfoHeader; 
	//unsigned char textureColors = 0;/**< 用于将图像颜色从BGR变换到RGB */  
	/** 打开文件,并检查错误 **/
	out_file.open(filename, std::ios::out | std::ios::binary);
	if (!out_file)
	{
		std::cerr << "Unable to open file " << filename << std::endl;
		return false;
	}

	/** 填充BITMAPFILEHEADER */
	header.bfType = BITMAP_ID;
	header.bfSize = w*h*3 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	header.bfReserved1 = 0;
	header.bfReserved2 = 0;
	header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	/** 写入位图文件头信息 */
	out_file.write((char*)&header, sizeof(BITMAPFILEHEADER));

	/** 填充BITMAPINFOHEADER */
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biWidth = w;
	bitmapInfoHeader.biHeight = h;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = 24;
	bitmapInfoHeader.biCompression = BI_RGB; // BI_RLE4 BI_RLE8
	bitmapInfoHeader.biSizeImage = w * h * 3; // 当压缩类型为BI_RGB是也可以设置为0
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;
	/** 写入位图文件信息 */
	out_file.write((char*)&bitmapInfoHeader, sizeof(BITMAPINFOHEADER));

	/** 将指针移到数据开始位置 */
	out_file.seekp(header.bfOffBits, std::ios::beg);

	/** 写入图像数据 */
	out_file.write((char*)data, bitmapInfoHeader.biSizeImage);

	out_file.close();
	return true;
}   // 