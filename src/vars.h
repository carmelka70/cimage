//this file includes the global variables in the program
#ifndef VARS_H
#define VARS_H

#include <stdint.h>
//CRITICAL CHUNKS

//IHDR - header
extern uint32_t IHDR_width ,IHDR_height;
extern uint8_t IHDR_bit_depth;
extern uint8_t IHDR_color_type;
extern uint8_t IHDR_compression_method;
extern uint8_t IHDR_filter_method;
extern uint8_t IHDR_interlace_method;

//PLTE - pallate for colors
extern uint8_t *PLTE_palette[3];

//IDAT - png data
extern uint8_t *IDAT_data;

//ANCILLARY CHUNKS

//tRNS - transparent
extern uint8_t *tRNS_alpha;
extern uint16_t tRNS_gray;
extern uint16_t tRNS_color[3];

//gAMA - brightness of the image
extern uint32_t gAMA_gamma;

//cHRM - local color mapping
extern uint32_t cHRM_white[2];
extern uint32_t cHRM_red[2];
extern uint32_t cHRM_green[2];
extern uint32_t cHRM_blue[2];

//sRGB - use srgb
extern uint8_t sRGB_intent;

//iCCP
extern char *iCCP_profile_name;
extern uint8_t iCCP_compression_method;
extern uint8_t iCCP_compressed_profile[];

//TEXT CHUNKS
/*
examples of keywords:
   Title            Short (one line) title or caption for image
   Author           Name of image's creator
   Description      Description of image (possibly long)
   Copyright        Copyright notice
   Creation Time    Time of original image creation
   Software         Software used to create the image
   Disclaimer       Legal disclaimer
   Warning          Warning of nature of content
   Source           Device used to create the image
   Comment          Miscellaneous comment; conversion from
                    GIF comment
*/
//tEXt - textual information
extern struct{
	char *keyword;
	char *text;
} *tEXt_blocks;

//zTXt - compressed textual information
extern struct{
	char *keyword;
	uint8_t compression_method;
	char *text;
} *zTXt_blocks;

//iTXt - unicode textual information
extern struct{
	char *keyword;
	uint8_t compression_flag;
	uint8_t compression_method;
	char *language_tag;
	char *translated_keyword;
	char *text;
} *iTXt_blocks;

//bKGD - background color
extern uint8_t bKGD_palette;
extern uint16_t bKGD_gray;
extern uint16_t bKGD_red ,bg_green ,bg_blue;

//pHYs - physical image size
extern uint32_t pHYs_x ,pHYs_y;
extern uint8_t pHYs_unit;

//sBIT - significant bits
extern uint8_t sBIT_gray;
extern uint8_t sBIT_red ,sBIT_green ,sBIT_blue;
extern uint8_t sBIT_pred ,sBIT_pgreen ,sBIT_pblue;
extern uint8_t sBIT_agray ,sBIT_alpha;
extern uint8_t sBIT_ared ,sBIT_agreen ,sBIT_ablue;

//sPLT - suggested pallete 

//hIST - pallete histogram
extern uint16_t *hIST_freq;

//tIME - time of last modification
extern uint16_t tIME_year;
extern uint8_t tIME_month ,tIME_day ,tIME_hour ,tIME_minute ,tIME_second;

#endif
