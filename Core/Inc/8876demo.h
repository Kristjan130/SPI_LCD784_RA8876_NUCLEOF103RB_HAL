#ifndef __8876DEMO_H__
#define __8876DEMO_H__

#define layer1_start_addr 0
#define layer2_start_addr 1024000   //400*1280*2
#define layer3_start_addr 2048000   //400*1280*2*2
#define layer4_start_addr 3072000   //400*1280*2*3
#define layer5_start_addr 4096000   //400*1280*2*4
#define layer6_start_addr 5120000   //400*1280*2*5
#define layer7_start_addr 6144000   //400*1280*2*5

void BTE_Compare(void);
void BTE_Color_Expansion(void);
void BTE_Pattern_Fill(void);
void PIP_Demo(void);
void App_Demo_Waveform(void);
void App_Demo_Scrolling_Text(void);
void App_Demo_multi_frame_buffer(void);
void App_Demo_slide_frame_buffer(void);
void App_Demo_Alpha_Blending(void);
void mono_Demo(void);
void Text_Demo(void);
void DMA_Demo(void);
void Geometric(void);
void gray(void);

#endif//__8876DEMO_H__
