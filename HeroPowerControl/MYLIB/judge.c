#include "judge.h"

wl4data w4d;//��������ת������4�ֽ�ת����float��
int32_t PowerOldTime = 0;//ÿ�����ݽ��յ�ϵͳʱ��

extPowerHeatData_t	Judge_extPowerHeatData = {0,0,0,60,0,0};

//���ղ���ϵͳ������Ϣ
void Receive104(u8 *candata)
{
	OS_ERR err;
	w4d.c[0] = candata[0];
	w4d.c[1] = candata[1];
	w4d.c[2] = candata[2];
	w4d.c[3] = candata[3];
	Judge_extPowerHeatData.chassisPowerBuffer = w4d.f;
	PowerOldTime = OSTimeGet(&err);
}
