#ifndef __SMOTORCONTROL_H__
#define __SMOTORCONTROL_H__

int velocity_type_choose();
void train_smotor_control(); //通过长前瞻电感计算舵机打角
void short_adc_judge();//通过短前瞻电感计算舵机打角
void cie_data_get();    //传输采集到的电感值到模型中


#endif