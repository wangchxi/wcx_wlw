#include "dev_mng.h"
#include "dev_103.h"

/*�豸����*/
#define RCS931A 0x01
#define RCS901A 0x02
#define RCS915A 0x03
#define RCS9607 0x04
#define RCS943A 0x05

/********************************************************
rcs9607ң���       ϵ��
1:ua---------------120/4096*pt
2:ub
3:uc
4:ux
5:uab
6:ubc
7:uca
8:3u0
9:ia---------------6/4096*ct
10:ib
11:ic
12:I0
13:p---------------1.732*120*6/4096*ct*pt
14:q
15:cos-------------1.2/4096
16:F---------------60/4096
17:Fx
************************************************************/

/* �豸�������� */
static T_IED g_ied_list[] =
{
//	{1,  c103_service, C103_FUN_931A, 0, {1,1,0,0,0,0}, RCS931A},
//	{2,  c103_service, C103_FUN_901A, 0, {2,1,0,0,0,0}, RCS901A},
//	{3,  c103_service, C103_FUN_915A, 0, {3,1,0,0,0,0}, RCS915A},
    {1,  c103_service, C103_FUN_943A, 0, {1, 1, 0, 0, 0, 0}, RCS943A},
    {2,  c103_service, C103_FUN_943A, 0, {2, 1, 0, 0, 0, 0}, RCS943A},
};

BOOL IED_Initialize()
{
    //return DEV_Create_IED (g_ied_list, sizeof (g_ied_list) / sizeof (T_IED));
}
/******************************* RCS-943a�����¼��͸澯********************************/
static T_EVENT_ENTRY nr_943a_event_table[] =
{
    {26, "�غ�բ����      "},
    {168, "�������������"},
    {164, "Զ��������բ����"},
    {54, "���������ζ���"},
    {55, "���������ζ���"},
    {56, "���������ζ���"},
    {57, "����������ζ���"},
    {78, "�����ζ���    "},
    {79, "�����ζ���    "},
    {80, "�����ζ���    "},
    {116, "������ٶ���    "},
    {151, "������ٶ���    "},
    {82, "˫��������ٶ�  "},
    {83, "���Գ�����ٶ�  "},
    {66, "TV���߹������  "},
    {67, "TV���߹������  "},
    {25, "��բ            "},
    {182, "����            "},
};
#define m_943a_evSize (sizeof(nr_943a_event_table)/sizeof(nr_943a_event_table[0]))

static T_ALARM_ENTRY nr_943a_alarm_table[] =
{
    {194, "�洢������      "},
    {195, "�������        "},
    {196, "��ֵ����        "},
    {49, "������ֵ��Ч    "},
    {50, "CPU�����쳣     "},
    {189, "����������    "},
    {214, "װ�ó�������    "},
    {51, "DSP�����쳣     "},
    {200, "���ϳ����쳣    "},
    {222, "��ֵУ�����    "},
    {44, "ֱ����Դ�쳣    "},
    {202, "�����Դ�쳣    "},
    {241, "ĸ�ߵ�ѹ��·����"},
    {240, "��·��ѹ��·����"},
    {206, "TA����          "},
    {210, "TWJ�쳣	      "},
    {203, "���ƻ�·��·����"},
    {184, "������          "},
    {192, "ͨ���쳣	      "},
    {227, "�����в���      "},
    {226, "�޶Բ�����      "},
    {42, "���ӷ������    "},
    {31, "�����ѹ��    "},
    {1,  "���뱣��ѹ��    "},
    {2,  "������ѹ��    "},
    {3,  "������ѹ��    "},
    {68, "������ѹ��    "},
    {69, "�������ѹ��    "},
    {7,  "���Գ�����ٶ�  "},
    {6,  "˫��������ٶ�  "},
    {8,  "�����غ�        "},
    {12, "˫����ͨ������  "},
    {87, "�Ϻ�λ��        "},
    {204, "��բѹ��        "},
    {205, "��բѹ��        "},
    {91, "��ĸ��ѹ        "},
    {92, "��ĸ��ѹ        "},
    {9,  "��բλ��        "},
    {41, "��բλ��1       "},
    {46, "��բλ��2       "},
    {5,  "��������        "},
    {32, "��Զ��          "},
    {74, "��Զ��1         "},
    {75, "��Զ��2         "},
    {76, "��Զ��1         "},
    {77, "��Զ��2         "},

};
#define m_943a_alSize (sizeof(nr_943a_alarm_table)/sizeof(nr_943a_alarm_table[0]))

static T_SET_ENTRY nr_943a_set_table[] =
{
    {0, SET_T_UINT, "������ֵ����    ", " "},
    {1, SET_T_FLOAT, "�����仯����ֵ", " "},
    {2, SET_T_FLOAT, "������������    ", " "},
    {3, SET_T_FLOAT, "������������    ", " "},
    {4, SET_T_FLOAT, "TA���ϵ��      ", " "},
    {5, SET_T_FLOAT, "������߶�ֵ  ", " "},
    {6, SET_T_FLOAT, "������Ͷ�ֵ  ", " "},
    {7, SET_T_FLOAT, "TA���߲�����ֵ  ", " "},
    {8, SET_T_FLOAT, "���򲹳�ϵ��    ", " "},
    {9, SET_T_FLOAT, "�񵴱�������    ", " "},
    {10, SET_T_FLOAT, "�ӵؾ����ζ�ֵ", " "},
    {11, SET_T_FLOAT, "������ʱ��    ", " "},
    {12, SET_T_FLOAT, "�ӵؾ����ζ�ֵ", " "},
    {13, SET_T_FLOAT, "�ӵؾ�����ʱ��", " "},
    {14, SET_T_FLOAT, "�ӵؾ����ζ�ֵ", " "},
    {15, SET_T_FLOAT, "�ӵآ���ı���  ", " "},
    {16, SET_T_FLOAT, "�ӵؾ�����ʱ��", " "},
    {17, SET_T_FLOAT, "�������ζ�ֵ", " "},
    {18, SET_T_FLOAT, "�������ζ�ֵ", " "},
    {19, SET_T_FLOAT, "��������ʱ��", " "},
    {20, SET_T_FLOAT, "�������ζ�ֵ", " "},
    {21, SET_T_FLOAT, "������ı���  ", " "},
    {22, SET_T_FLOAT, "��������ʱ��", " "},
    {23, SET_T_FLOAT, "����������      ", " "},
    {24, SET_T_FLOAT, "����������      ", " "},
    {25, SET_T_FLOAT, "�ӵؾ���ƫ�ƽ�  ", " "},
    {26, SET_T_FLOAT, "������ƫ�ƽ�  ", " "},
    {27, SET_T_FLOAT, "���������ζ�ֵ", " "},
    {28, SET_T_FLOAT, "����������ʱ��", " "},
    {29, SET_T_FLOAT, "���������ζ�ֵ", " "},
    {30, SET_T_FLOAT, "����������ʱ��", " "},
    {31, SET_T_FLOAT, "���������ζ�ֲ", " "},
    {32, SET_T_FLOAT, "����������ʱ��", " "},
    {33, SET_T_FLOAT, "����������ζ�ֲ", " "},
    {34, SET_T_FLOAT, "�����������ʱ��", " "},
    {35, SET_T_FLOAT, "����������ٶ�  ", " "},
    {36, SET_T_FLOAT, "����������ɶ�ֵ", " "},
    {37, SET_T_FLOAT, "�����������ʱ��", " "},
    {38, SET_T_FLOAT, "TV���߹�����ֵ", " "},
    {39, SET_T_FLOAT, "TV���߹�����ʱ��", " "},
    {40, SET_T_FLOAT, "TV���߹�����ֵ", " "},
    {41, SET_T_FLOAT, "TV���߹�����ʱ��", " "},
    {42, SET_T_FLOAT, "�̶��ǶȲֵ  ", " "},
    {43, SET_T_FLOAT, "�غ�բʱ��      ", " "},
    {44, SET_T_FLOAT, "ͬ�ں�բ��      ", " "},
    {45, SET_T_FLOAT, "��·����翹    ", " "},
    {46, SET_T_FLOAT, "��·�������    ", " "},
    {47, SET_T_FLOAT, "��·����翹    ", " "},
    {48, SET_T_FLOAT, "��·�������    ", " "},
    {49, SET_T_FLOAT, "��·�ܳ���      ", " "},
    {50, SET_T_FLOAT, "��·���        ", " "},
    {51, SET_T_FLOAT, "Ͷ���������  ", " "},
    {52, SET_T_FLOAT, "ͶTV���߱����", " "},
    {53, SET_T_FLOAT, "Ͷ������ʽ      ", " "},
    {54, SET_T_FLOAT, "Ͷר�ù���      ", " "},
    {55, SET_T_FLOAT, "Ͷͨ���Ի�����  ", " "},
    {56, SET_T_FLOAT, "ͶԶ���ܱ������", " "},
    {57, SET_T_FLOAT, "Ͷ�񵴱���	 ", " "},
    {58, SET_T_FLOAT, "Ͷ��νӵؾ���  ", " "},
    {59, SET_T_FLOAT, "Ͷ��νӵؾ���  ", " "},
    {60, SET_T_FLOAT, "Ͷ��νӵؾ���  ", " "},
    {61, SET_T_FLOAT, "Ͷ���������  ", " "},
    {62, SET_T_FLOAT, "Ͷ���������  ", " "},
    {63, SET_T_FLOAT, "Ͷ���������  ", " "},
    {64, SET_T_FLOAT, "�غϼ��٢�ξ���", " "},
    {65, SET_T_FLOAT, "�غϼ��٢�ξ���", " "},
    {66, SET_T_FLOAT, "˫��������ٶ�  ", " "},
    {67, SET_T_FLOAT, "���Գ�����ٶ�  ", " "},
    {68, SET_T_FLOAT, "Ͷ���������  ", " "},
    {69, SET_T_FLOAT, "Ͷ���������  ", " "},
    {70, SET_T_FLOAT, "Ͷ���������  ", " "},
    {71, SET_T_FLOAT, "Ͷ����������  ", " "},
    {72, SET_T_FLOAT, "Ͷ�����������  ", " "},
    {73, SET_T_FLOAT, "Ͷ�غ�բ        ", " "},
    {74, SET_T_FLOAT, "Ͷ��ͬ�ڷ�ʽ    ", " "},
    {75, SET_T_FLOAT, "Ͷ����ѹĸ��ѹ  ", " "},
    {76, SET_T_FLOAT, "Ͷĸ��ѹ����ѹ  ", " "},
    {77, SET_T_FLOAT, "Ͷ����ѹĸ��ѹ  ", " "},
    {78, SET_T_FLOAT, "Ͷ�غ�բ����    ", " "},
    {79, SET_T_FLOAT, "TV����������  ", " "},
    {80, SET_T_FLOAT, "TV���߱����غ�  ", " "},
    {81, SET_T_FLOAT, "��μ����ϱ���  ", " "},
    {82, SET_T_FLOAT, "Ͷ������ϱ���  ", " "},
};
#define m_943a_setSize (sizeof(nr_943a_set_table)/sizeof(nr_943a_set_table[0]))

/******************************* RCS-901a�����¼��͸澯********************************/
static T_EVENT_ENTRY nr_901a_event_table[] =
{
    {26, "�غ�բ����      "},
    {169, "�����仯������  "},
    {166, "����������    "},
    {113, "��Ƶ�仯���迹  "},
    {78, "�����ζ���	  "},
    {79, "�����ζ���	  "},
    {80, "�����ζ���	  "},
    {55, "����������	  "},
    {56, "����������	  "},
    {114, "��ȫ�����й���  "},
    {116, "�������		  "},
    {151, "�������		  "},
    {88, "ѡ����Ч����	  "},
    {89, "����ʧ������	  "},
    {90, "������������	  "},
    {63, "TV���߹���	  "},
    {20, "��A		  "},
    {21, "��B		  "},
    {22, "��C		  "},
    {182, "��		  "},

};
#define m_901a_evSize (sizeof(nr_901a_event_table)/sizeof(nr_901a_event_table[0]))

static T_ALARM_ENTRY nr_901a_alarm_table[] =
{
    {194, "�洢������  "},
    {195, "�������      "},
    {196, "��ֵ����      "},
    {49, "������ֵ��Ч    "},
    {50, "CPU�����쳣     "},
    {189, "��������    "},
    {214, "װ�ó�����    "},
    {51, "DSP�����쳣     "},
    {200, "���ϳ����쳣    "},
    {222, "��ֵУ�����    "},
    {44, "ֱ����Դ�쳣    "},
    {202, "�����Դ�쳣    "},
    {241, "ĸ�ߵ�ѹ��·����"},
    {240, "��·��ѹ��·����"},
    {206, "TA����	      "},
    {210, "TWJ�쳣	      "},
    {212, "��բ�����쳣    "},
    {192, "ͨ���쳣	      "},
    {42 , "���ӷ������    "},

};
#define m_901a_alSize (sizeof(nr_901a_alarm_table)/sizeof(nr_901a_alarm_table[0]))

static T_SET_ENTRY nr_901a_set_table[] =
{
    {0, SET_T_UINT, "������ֵ����    ", " "},
    {1, SET_T_FLOAT, "�����仯����ֵ", " "},
    {2, SET_T_FLOAT, "������������    ", " "},
    {3, SET_T_FLOAT, "��Ƶ�仯���迹  ", " "},
    {4, SET_T_FLOAT, "����Χ�仯���迹", " "},
    {5, SET_T_FLOAT, "�����������ֵ", " "},
    {6, SET_T_FLOAT, "ͨ������ʱ�䶨ֵ", " "},
    {7, SET_T_FLOAT, "���򲹳�ϵ��    ", " "},
    {8, SET_T_FLOAT, "�񵴱�������    ", " "},
    {9, SET_T_FLOAT, "�ӵؾ���I�ζ�ֵ ", " "},
    {10, SET_T_FLOAT, "�ӵؾ���II�ζ�ֵ", " "},
    {11, SET_T_FLOAT, "�ӵؾ���II��ʱ��", " "},
    {12, SET_T_FLOAT, "�ӵؾ����ζ�ֵ", " "},
    {13, SET_T_FLOAT, "�ӵؾ�����ʱ��", " "},
    {14, SET_T_FLOAT, "������I�ζ�ֵ", " "},
    {15, SET_T_FLOAT, "������II�ζ�ֵ", " "},
    {16, SET_T_FLOAT, "������II��ʱ��", " "},
    {17, SET_T_FLOAT, "�������ζ�ֵ", " "},
    {18, SET_T_FLOAT, "��������ʱ��", " "},
    {19, SET_T_FLOAT, "�������Ƶ��趨ֵ", " "},
    {20, SET_T_FLOAT, "����������      ", " "},
    {21, SET_T_FLOAT, "����������    ", " "},
    {22, SET_T_FLOAT, "�ӵؾ���ƫ�ƽ�  ", " "},
    {23, SET_T_FLOAT, "������ƫ�ƽ�  ", " "},
    {24, SET_T_FLOAT, "�������II�ζ�ֵ", " "},
    {25, SET_T_FLOAT, "�������II��ʱ��", " "},
    {26, SET_T_FLOAT, "���������ζ�ֲ", " "},
    {27, SET_T_FLOAT, "����������ʱ��", " "},
    {28, SET_T_FLOAT, "����������ٶ�", " "},
    {29, SET_T_FLOAT, "TV�����������ֵ", " "},
    {30, SET_T_FLOAT, "TV����ʱ�������", " "},
    {31, SET_T_FLOAT, "TV����ʱ����ʱ��", " "},
    {32, SET_T_FLOAT, "�����غ�բʱ��", " "},
    {33, SET_T_FLOAT, "�����غ�բʱ��  ", " "},
    {34, SET_T_FLOAT, "ͬ�ں�բ��      ", " "},
    {35, SET_T_FLOAT, "��·����翹", " "},
    {36, SET_T_FLOAT, "��·�������", " "},
    {37, SET_T_FLOAT, "��·����翹", " "},
    {38, SET_T_FLOAT, "��·�������    ", " "},
    {39, SET_T_FLOAT, "��·�ܳ���      ", " "},
    {40, SET_T_FLOAT, "��·���        ", " "},
    {41, SET_T_FLOAT, "Ͷ��Ƶ�仯���迹", " "},
    {42, SET_T_FLOAT, "Ͷ�����仯������", " "},
    {43, SET_T_FLOAT, "Ͷ����������  ", " "},
    {44, SET_T_FLOAT, "Ͷ���򲹳��迹  ", " "},
    {45, SET_T_FLOAT, "����ʽͨ��      ", " "},
    {46, SET_T_FLOAT, "Ͷ�Զ�ͨ������  ", " "},
    {47, SET_T_FLOAT, "����Դ��	 ", " "},
    {48, SET_T_FLOAT, "��ѹ����·TV  ", " "},
    {49, SET_T_FLOAT, "Ͷ�񵴱���Ԫ��  ", " "},
    {50, SET_T_FLOAT, "ͶI�νӵؾ���   ", " "},
    {51, SET_T_FLOAT, "ͶII�νӵؾ���  ", " "},
    {52, SET_T_FLOAT, "ͶIII�νӵؾ��� ", " "},
    {53, SET_T_FLOAT, "ͶI��������", " "},
    {54, SET_T_FLOAT, "ͶII��������", " "},
    {55, SET_T_FLOAT, "ͶIII��������", " "},
    {56, SET_T_FLOAT, "Ͷ�������ƾ���", " "},
    {57, SET_T_FLOAT, "���ؼ���II�ξ���", " "},
    {58, SET_T_FLOAT, "���ؼ��٢�ξ���", " "},
    {59, SET_T_FLOAT, "�����ξ�����", " "},
    {60, SET_T_FLOAT, "�����բ����� ", " "},
    {61, SET_T_FLOAT, "Ͷ������բ��ʽ ", " "},
    {62, SET_T_FLOAT, "Ͷ�غ�բ ", " "},
    {63, SET_T_FLOAT, "Ͷ��ͬ�ڷ�ʽ ", " "},
    {64, SET_T_FLOAT, "Ͷ����ѹ��ʽ  ", " "},
    {65, SET_T_FLOAT, "Ͷ�غ�բ����", " "},
    {66, SET_T_FLOAT, "����Ӧ�����غ�", " "},
    {67, SET_T_FLOAT, "������II����", " "},
    {68, SET_T_FLOAT, "�ӵؾ���II����", " "},
    {69, SET_T_FLOAT, "��II����������", " "},
    {70, SET_T_FLOAT, "Ͷѡ����Ч����", " "},
    {71, SET_T_FLOAT, "��ȫ����ϱ���", " "},
    {72, SET_T_FLOAT, "Ͷ������ϱ���", " "},
    {73, SET_T_FLOAT, "Ͷ������ϱ���  ", " "},
    {74, SET_T_FLOAT, "���غϰ�����Ч  ", " "},
    {75, SET_T_FLOAT, "Ͷ���ط�ʽ	 ", " "},
    {76, SET_T_FLOAT, "Ͷ���ط�ʽ      ", " "},
    {77, SET_T_FLOAT, "Ͷ���ط�ʽ      ", " "},
};
#define m_901a_setSize (sizeof(nr_901a_set_table)/sizeof(nr_901a_set_table[0]))

/******************************* 915A�����¼��͸澯********************************/
static T_EVENT_ENTRY nr_915a_event_table[] =
{
    {16 , "��·����        "},
    {17 , "������·1       "},
    {18 , "������·2       "},
    {19 , "������·3       "},
    {21 , "������·4       "},
    {22 , "������·5       "},
    {23 , "������·6       "},
    {24 , "������·7       "},
    {25 , "������·8       "},
    {26 , "������·9       "},
    {27 , "������·10      "},
    {28 , "������·11      "},
    {29 , "������·12      "},
    {30 , "������·13      "},
    {31 , "������·14      "},
    {32 , "������·15      "},
    {33 , "������·16      "},
    {34 , "������·17      "},
    {35 , "������·18      "},
    {36 , "������·19      "},
    {37 , "������·20      "},
    {14 , "ĸ��󱸶���    "},
    {116, "ʧ����һĸ      "},
    {117, "ʧ������ĸ      "},
    {69 , "A����բ         "},
    {70 , "B����բ         "},
    {71 , "C����բ         "},
    {153, "ĸ����һĸ      "},
    {154, "ĸ����һĸ      "},
    {158, "�����ĸ��      "},
    {157, "������ĸ��      "},
    {163, "ĸ��ʧ��        "},

};
#define m_915a_evSize (sizeof(nr_915a_event_table)/sizeof(nr_915a_event_table[0]))

static T_ALARM_ENTRY nr_915a_alarm_table[] =
{
    {194, "�ڴ����  "},
    {195, "����������      "},
    {196, "��ֵ������      "},
    {201, "��բ���ڱ���    "},
    {202, "����ʧ��        "},
    {211, "�ڲ�ͨѶ����    "},
    {214, "װ�ó�����������"},
    {231, "һĸTV����      "},
    {232, "��ĸTV����      "},
    {210, "TWJ����         "},
    {206, "TA����	      "},
    {209, "��բλ�ñ���    "},
    {103, "ĸ��TA���߱���  "},
    {104, "������ֵ��Ч    "},
    {81 , "�޸Ķ�ֵ        "},
    {82 , "DSP����         "},
    {135, "Iĸ��ѹ�������� "},
    {136, "IIĸ��ѹ��������"},
};
#define m_915a_alSize (sizeof(nr_915a_alarm_table)/sizeof(nr_915a_alarm_table[0]))

static T_SET_ENTRY nr_915a_set_table[] =
{

    {0, SET_T_UINT, "������ֵ����  ", " "},
    {1, SET_T_FLOAT, "�����������ֵ", " "},
    {2, SET_T_FLOAT, "�����������ֵ", " "},
    {3, SET_T_FLOAT, "�������ƶ�ϵ��", " "},
    {4, SET_T_FLOAT, "�����ƶ�ϵ����ֵ", " "},
    {5, SET_T_FLOAT, "�����ƶ�ϵ����ֵ", " "},
    {6, SET_T_FLOAT, "��籣��������ֵ", " "},
    {7, SET_T_FLOAT, "ĸ������������ֵ", " "},
    {8, SET_T_FLOAT, "ĸ����������ֵ", " "},
    {9, SET_T_FLOAT, "ĸ������ʱ�䶨ֵ", " "},
    {10, SET_T_FLOAT, "��ȫ������ֵ  ", " "},
    {11, SET_T_FLOAT, "��ȫ�ฺ��ֵ  ", " "},
    {12, SET_T_FLOAT, "��ȫ��ʱ�䶨ֵ  ", " "},
    {13, SET_T_FLOAT, "TA���ߵ�����ֵ  ", " "},
    {14, SET_T_FLOAT, "TA�쳣������ֵ  ", " "},
    {15, SET_T_FLOAT, "ĸ����͵�ѹ����", " "},
    {16, SET_T_FLOAT, "ĸ�������ѹ����", " "},
    {17, SET_T_FLOAT, "ĸ����ѹ����", " "},
    {18, SET_T_FLOAT, "ĸ��ʧ���ѹ��ֵ", " "},
    {19, SET_T_FLOAT, "ĸ��ʧ���ѹ��ֵ", " "},
    {20, SET_T_FLOAT, "Ͷ��ĸ���    ", " "},
    {21, SET_T_FLOAT, "Ͷ��ʧ�鱣��    ", " "},
    {22, SET_T_FLOAT, "Ͷ��ĸ������    ", " "},
    {23, SET_T_FLOAT, "Ͷ�뵥ĸ��ʽ    ", " "},
    {24, SET_T_FLOAT, "ͶIĸTV         ", " "},
    {25, SET_T_FLOAT, "ͶIIĸTV        ", " "},
    {26, SET_T_FLOAT, "Ͷ������ĸ��  ", " "},
    {27, SET_T_FLOAT, "ͶTV�����Զ��ָ�", " "},
};
#define m_915a_setSize (sizeof(nr_915a_set_table)/sizeof(nr_915a_set_table[0]))

/************************************************************************/
/*                  RCS-931A                                            */
/************************************************************************/
static T_EVENT_ENTRY nr_931a_event_table[] =
{
    {26, "�غ�բ����	  "},
    {168, "���������	  "},
    {164, "Զ������բ	  "},
    {113, "��Ƶ�仯���迹  "},
    {78, "�����ζ���	  "},
    {79, "�����ζ���	  "},
    {80, "�����ζ���	  "},
    {55, "����������	  "},
    {56, "����������	  "},
    {114, "��ȫ�����й���  "},
    {116, "�������		  "},
    {151, "�������		  "},
    {88, "ѡ����Ч����	  "},
    {89, "����ʧ������	  "},
    {90, "������������	  "},
    {63, "TV���߹���	  "},
    {20, "��A		  "},
    {21, "��B		  "},
    {22, "��C		  "},
    {182, "��		  "},
};
#define m_931a_evSize (sizeof(nr_931a_event_table)/sizeof(nr_931a_event_table[0]))

static T_ALARM_ENTRY nr_931a_alarm_table[] =
{
    {194, "�洢������      "},
    {195, "�������        "},
    {196, "��ֵ����        "},
    {49, "������ֵ��Ч    "},
    {50, "CPU�����쳣     "},
    {189, "��������    "},
    {214, "װ�ó�����    "},
    {51, "DSP�����쳣  "},
    {200, "���ϳ����쳣    "},
    {222, "��ֵУ�����    "},
    {44, "ֱ����Դ�쳣    "},
    {202, "�����Դ�쳣  "},
    {241, "ĸ�ߵ�ѹ��·����"},
    {240, "��·��ѹ��·����"},
    {206, "TA����	  "},
    {210, "TWJ�쳣	  "},
    {212, "��բ�����쳣  "},
    {192, "ͨ���쳣	  "},
    {247, "�ݿ���������  "},
    {227, "�����в���  "},
    {226, "�޶Բ�����  "},
    {42 , "���ӷ������  "},
};
#define m_931a_alSize (sizeof(nr_931a_alarm_table)/sizeof(nr_931a_alarm_table[0]))

static T_SET_ENTRY nr_931a_set_table[] =
{
    {0, SET_T_UINT, "������ֵ����    ", " "},
    {1, SET_T_FLOAT, "�����仯����ֵ", " "},
    {2, SET_T_FLOAT, "������������", " "},
    {3, SET_T_FLOAT, "��Ƶ�仯���迹", " "},
    {4, SET_T_FLOAT, "TA���ϵ��", " "},
    {5, SET_T_FLOAT, "������߶�ֵ", " "},
    {6, SET_T_FLOAT, "������Ͷ�ֵ", " "},
    {7, SET_T_FLOAT, "TA���߲�����ֵ", " "},
    {8, SET_T_FLOAT, "���򲹳�ϵ��", " "},
    {9, SET_T_FLOAT, "�񵴱�������", " "},
    {10, SET_T_FLOAT, "�ӵؾ���I�ζ�ֵ", " "},
    {11, SET_T_FLOAT, "�ӵؾ���II�ζ�ֵ", " "},
    {12, SET_T_FLOAT, "�ӵؾ���II��ʱ��", " "},
    {13, SET_T_FLOAT, "�ӵؾ����ζ�ֵ", " "},
    {14, SET_T_FLOAT, "�ӵؾ�����ʱ��", " "},
    {15, SET_T_FLOAT, "������I�ζ�ֵ", " "},
    {16, SET_T_FLOAT, "������II�ζ�ֵ", " "},
    {17, SET_T_FLOAT, "������II��ʱ��", " "},
    {18, SET_T_FLOAT, "�������ζ�ֵ", " "},
    {19, SET_T_FLOAT, "��������ʱ��", " "},
    {20, SET_T_FLOAT, "�������Ƶ��趨ֵ", " "},
    {21, SET_T_FLOAT, "����������", " "},
    {22, SET_T_FLOAT, "����������    ", " "},
    {23, SET_T_FLOAT, "�ӵؾ���ƫ�ƽ� ", " "},
    {24, SET_T_FLOAT, "������ƫ�ƽ� ", " "},
    {25, SET_T_FLOAT, "�������II�ζ�ֵ", " "},
    {26, SET_T_FLOAT, "�������II��ʱ��", " "},
    {27, SET_T_FLOAT, "���������ζ�ֲ", " "},
    {28, SET_T_FLOAT, "����������ʱ��", " "},
    {29, SET_T_FLOAT, "����������ٶ�", " "},
    {30, SET_T_FLOAT, "TV�����������ֵ", " "},
    {31, SET_T_FLOAT, "TV����ʱ�������", " "},
    {32, SET_T_FLOAT, "TV����ʱ����ʱ��", " "},
    {33, SET_T_FLOAT, "�����غ�բʱ��", " "},
    {34, SET_T_FLOAT, "�����غ�բʱ��  ", " "},
    {35, SET_T_FLOAT, "ͬ�ں�բ��      ", " "},
    {36, SET_T_FLOAT, "��·����翹", " "},
    {37, SET_T_FLOAT, "��·�������", " "},
    {38, SET_T_FLOAT, "��·�����ݿ�", " "},
    {39, SET_T_FLOAT, "��·����翹", " "},
    {40, SET_T_FLOAT, "��·�������", " "},
    {41, SET_T_FLOAT, "��·�����ݿ�    ", " "},
    {42, SET_T_FLOAT, "��·�ܳ���    ", " "},
    {43, SET_T_FLOAT, "��·���    ", " "},
    {44, SET_T_FLOAT, "��Ƶ�仯�迹Ͷ��", " "},
    {45, SET_T_FLOAT, "�����Ͷ��    ", " "},
    {46, SET_T_FLOAT, "TA�ϱ����Ͷ��", " "},
    {47, SET_T_FLOAT, "������ʽ	", " "},
    {48, SET_T_FLOAT, "ר�ù���", " "},
    {49, SET_T_FLOAT, "ͨ���Ի�����", " "},
    {50, SET_T_FLOAT, "Զ���ܱ������", " "},
    {51, SET_T_FLOAT, "��ѹ����·TV  ", " "},
    {52, SET_T_FLOAT, "Ͷ�񵴱���Ԫ��  ", " "},
    {53, SET_T_FLOAT, "ͶI�νӵؾ���   ", " "},
    {54, SET_T_FLOAT, "ͶII�νӵؾ���  ", " "},
    {55, SET_T_FLOAT, "ͶIII�νӵؾ��� ", " "},
    {56, SET_T_FLOAT, "ͶI��������", " "},
    {57, SET_T_FLOAT, "ͶII��������", " "},
    {58, SET_T_FLOAT, "ͶIII��������", " "},
    {59, SET_T_FLOAT, "Ͷ�������ƾ���", " "},
    {60, SET_T_FLOAT, "���ؼ���II�ξ���", " "},
    {61, SET_T_FLOAT, "���ؼ��٢�ξ���", " "},
    {62, SET_T_FLOAT, "�����ξ�����", " "},
    {63, SET_T_FLOAT, "�����բ����� ", " "},
    {64, SET_T_FLOAT, "Ͷ������բ��ʽ ", " "},
    {65, SET_T_FLOAT, "Ͷ�غ�բ ", " "},
    {66, SET_T_FLOAT, "Ͷ��ͬ�ڷ�ʽ ", " "},
    {67, SET_T_FLOAT, "Ͷ����ѹ��ʽ  ", " "},
    {68, SET_T_FLOAT, "Ͷ�غ�բ����", " "},
    {69, SET_T_FLOAT, "����Ӧ�����غ�", " "},
    {70, SET_T_FLOAT, "������II����", " "},
    {71, SET_T_FLOAT, "�ӵؾ���II����", " "},
    {72, SET_T_FLOAT, "��II����������", " "},
    {73, SET_T_FLOAT, "Ͷѡ����Ч����", " "},
    {74, SET_T_FLOAT, "��ȫ����ϱ���", " "},
    {75, SET_T_FLOAT, "Ͷ������ϱ���", " "},
    {76, SET_T_FLOAT, "Ͷ������ϱ���  ", " "},
    {77, SET_T_FLOAT, "���غϰ�����Ч  ", " "},
    {78, SET_T_FLOAT, "Ͷ���ط�ʽ	 ", " "},
    {79, SET_T_FLOAT, "Ͷ���ط�ʽ      ", " "},
    {80, SET_T_FLOAT, "Ͷ���ط�ʽ      ", " "},
};
#define m_931a_setSize (sizeof(nr_931a_set_table)/sizeof(nr_931a_set_table[0]))

/* �������� */
T_C103_CODE_TABLE g_c103_code[] =
{
    {RCS943A, nr_943a_event_table, nr_943a_alarm_table, nr_943a_set_table, m_943a_evSize, m_943a_alSize, m_943a_setSize},
    {RCS915A, nr_915a_event_table, nr_915a_alarm_table, nr_915a_set_table, m_915a_evSize, m_915a_alSize, m_915a_setSize},
    {RCS901A, nr_901a_event_table, nr_901a_alarm_table, nr_901a_set_table, m_901a_evSize, m_901a_alSize, m_901a_setSize},
    {RCS931A, nr_931a_event_table, nr_931a_alarm_table, nr_931a_set_table, m_931a_evSize, m_931a_alSize, m_931a_setSize},
    {RCS9607},
};
WORD g_c103_code_size = sizeof (g_c103_code) / sizeof (T_C103_CODE_TABLE);
