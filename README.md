# HeroPowerControl
Hero robot power control
//大连交通大学-TOE工作室-英雄底盘功率控制-开源代码
一、基本架构
我的程序是跑在ucosiii下的，主要有以下几个任务组成：
1、电机数据反馈接收任务
task_can任务
通过信号量，同步了can接收中断，主要接收四个底盘电机的反馈速度。
2、遥控器数据接收是放在串口空闲中断中处理的，处理函数为void RemoteDataPrcess(uint8_t *sbus_rx_buffer)。可以直接task_control任务中获取遥控器控制信息。
3、逻辑及pid控制任务
task_control任务
此任务的运行周期为5ms，所有控制逻辑和pid都在此任务下运行。
4、串口调试任务
task_usart任务
用于与上位机互相传递数据，上传数据，接收数据，调试参数。
5、数据打印任务
task_print任务
用于周期性打印数据。
6、监视任务
task_monitor任务
此任务会对四个底盘电机反馈数据的帧率，遥控器反馈数据的帧率，经行统计、若四个底盘电机反馈数据的帧率低于某个值后，单片机的led灯不在闪烁：若遥控器反馈数据的帧率低于某个值后，将遥控器数据初始化，防止车疯转。
7、控制思路
      每个电机的最大输出量，即pid输出值的最大为12000。由于输出量比较大，所以在键盘的wasd控制的时候，按压wasd键位会让遥控器产生一个很大的固定控制值即pid目标值（此套程序遥控器最大可以产生+-660的控制值），此时由于电机速度基本为0，所以pid会长时间产生一个特别大的输出值，使功率限制不住。这种情况也会在按完w再按s，反向操作中产生，为了解决这种情况，需要对遥控器控制值做缓冲处理，即当控制值小于某个值时不做缓冲，当大于某个值时，在这个值的基础上加上某个固定的增量，如当控制值为660时，在80的基础上每个控制周期增加8，直到增加660为止。缓冲函数为int16_t Ramp_function(int16_t delta_Min,int16_t target,int16_t now, int16_t ramp_Coeff, u8 mode)。
      此缓冲函数用在麦轮解算之前，对xy方向产生的控制量进行缓冲。遥控器只能产生x和y方向的控制量，根据产生的xy控制量在解算成四个麦轮的速度控制值。所以缓冲函数放在麦轮解算之前是比较合适的。用于电机的速度控制范围为+-8192，所以要将解算后的四轮速度映射到+-7500
      加上缓冲函数后还是会超功率，所以在底盘pid中应该根据裁判系统反馈的60j剩余情况，来限制电机的输出量。当60j能量小于50j时，应该对所有的电机输出量进行限制，剩余的能量越少，输出量就越小，其关系为四个电机的总输出量等于剩余能量的平方，再乘以一个系数（PowerLimtParam）。 为了不影响车的运动方向，所以每个电机的输出量应该等于此电机占总输出量的百分比乘以限制后的总输出量。
      做了以上后，也会有很小概率的超功率现象，此现象是由于裁判系统数据有丢包的现象，所以应该记录接收数据时的系统的时间（PowerOldTime），当下时间减去接收数据时的系统的时间大于30ms时，说明裁判系统数据丢包了，此时的输出量应该很小，可以把60j的剩余能量直接设成一个很小的值，如5j。

需要调试的参数有：
1、当60j剩余能量小于某个值，这个某个值也需要调试，我选用了50为这个值，当这个值太大时，不能冲分利用60j的能量；当这个值太小时，会超功率或者车在加速的过程中有明显的卡顿现象，操作体验不好
2、delta_Min
缓冲的最小值，当小于此值的时候，不做缓冲
3、ramp_Coeff
缓冲的增量，当增量太大的时候，也会超功率，太小，会造成加速时间过长。
4、当操作手按了前进键后控制值为660，又按了后退键后控制值为-660，由于有缓冲函数，所以控制值会以一定的增量增加到-660，此过程会很长，所以为了缩短时间，当反向操作时，应该特殊处理，给控制值直接赋值为-660的二分之一或者三分之一，此百分比需要调试。此百分比在函数int16_t Ramp_function(int16_t delta_Min,int16_t target,int16_t now, int16_t ramp_Coeff, u8 mode)
中。
5、PowerLimtParam 
在调试以上参数时可以先把此参数给一个比较小的值，以上参数调试好后，再调试此参数。

二、代码的编译方式
在keil uVisioin5下编译
三、工具软件包
使用了STM32F4xx_StdPeriph_Lib_V3.5.0版本的固件库
四、代码运行的硬件环境
STM32F407VET6
五、代码运行的软件环境
ucosiii
