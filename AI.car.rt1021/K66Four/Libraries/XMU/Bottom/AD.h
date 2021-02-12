#ifndef AD_H
#define AD_H

#define ADC_LEFT ADC0_SE18//ADC0_SE8
#define ADC_MIDDLE ADC0_SE8//ADC0_SE12
#define ADC_RIGHT ADC0_SE13//ADC0_SE9

extern int protect_flag;
void ind_acq(void);
void ind_norm_maxmin(void);
void ind_norm(void);
void get_ind_error(void);
unsigned char IndJudgeCircle();
unsigned char IndJudgeIntoCircle(unsigned char type);
void AD_Img_Circle();
void ind_protect(void);

#endif // !AD_H