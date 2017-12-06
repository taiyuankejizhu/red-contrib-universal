/*******************************************************************************
    File name:         dlt645_api_07.h
    Author:         ����
    Version:          1.0
    Date:            2012��10��22��
    Description:     dlt645 2007���Լ����ͷ�ļ����������ܲɼ��ն��뼯����������
                    �������ܵ��ͨ�ŵĹ�Լ����                 
    Others:       
    Function List: 
    1. History: 
                    
          1)  Date:
          2)  Author:
          3)  Modification:  Created
    2. ...
*******************************************************************************/
#ifndef _DLT645_API_2007_H_
#define _DLT645_API_2007_H_


#pragma pack(push)  // ����һ�ֽڶ���
#pragma pack(1)

/* ���Կ��� */
#define D07_DEBUG_ON
#undef D07_DEBUG_ON   // ��ʽ��ע�͵�


#ifdef D07_DEBUG_ON

#define OUT_BUF_LEN 1024
#define D07_ON  0
#define D07_OFF 1

extern int g_need_pack_07;
extern char g_out_data_07[OUT_BUF_LEN];

#endif



#ifndef _TYPE_DEF_LM_
#define _TYPE_DEF_LM_
#ifndef __RTL_H__
#define __RTL_H__
typedef char    BOOL;
#endif
#define TRUE    (1)
#define FALSE   (0)
typedef unsigned char UCHAR;
typedef char    CHAR;
typedef unsigned short USHORT;
typedef short   SHORT;

typedef unsigned long ULONG;
typedef long    LONG;

#ifndef _TYPE_DEF_
#define _TYPE_DEF_
typedef char            INT8;       //c
typedef short           INT16;      //s
typedef int             INT32;      //l
typedef unsigned char   UINT8;      //uc
typedef unsigned short  UINT16;     //us
typedef unsigned int    UINT32;     //ul

#ifdef MACHINE_64_BITS
typedef long             INT64;
typedef unsigned   long  UINT64;
#else
typedef long  long           INT64;
typedef unsigned long  long  UINT64;
#endif

typedef char*           STRING;     //str
typedef char            ISBOOL;     //b
typedef unsigned int    IPADDR;     //ip
typedef double          DOUBLE;
typedef void*  FRWK_HANDLE;

#endif
#endif



/* �궨�� **/
#define NAME_LEN              128   
#define UNKNOWN_RULER_ID     0XFFFFFFFF
#define D07_ADDR_LEN         12                      /* ��ַ�� */
#define D07_DATA_MAX_NR      240                       /* dlt645 2007 ����������ֽ������ԼID */
#define D07_DATA_MAX         (D07_DATA_MAX_NR + 4)   /* dlt645 2007 ����������ֽ��� */
#define D07_FRAME_LEN_MIN    12                        /* DLT645 2007 ��С֡�ֽ��� */  

/*������ 2007*/
#define D07_CTRL_RESV                                0x00     // ����
#define D07_CTRL_SYNC_TIME                            0x08     // �㲥Уʱ
#define D07_CTRL_READ_DATA                            0x11    // ������
#define D07_CTRL_READ_AFTERDATA                        0x12    // ����������
#define D07_CTRL_READ_ADDR                            0x13    // ��ͨ�ŵ�ַ
#define D07_CTRL_WRITE_DATA                            0x14    // д����
#define D07_CTRL_WRITE_ADDR                            0x15    // дͨ�ŵ�ַ
#define D07_CTRL_FREEZ_COMM                            0x16    // ��������
#define D07_CTRL_MODIFY_BAUD                        0x17    // �޸�ͨ������
#define D07_CTRL_MODIFY_PASSWORD                    0x18    // �޸�����
#define D07_CTRL_CLEAR_MAXDEMAND                    0x19    // �����������
#define D07_CTRL_CLEAR_METER                        0x1A    // �������
#define D07_CTRL_CLEAR_EVENT                        0x1B    // �¼�����
#define D07_CTRL_COMM                                0x1C    // ��������

/** �궨�� */


/* ����ֵ���� �б�*/
typedef enum
{
    E_D07_OK = 0,            /* ����OK */
    E_D07_ERRO_NULL,        /* ָ��Ϊ�� */
    E_D07_ERRO_UNKOWN_ID,    // δ֪��ԼID
    E_D07_ERRO_PARA_NONE,   /* ������ */
    E_D07_ERRO_PARA_OUT_RANGE,
    
    //check frame
    E_D07_ERRO_FRAME_UNCOMP,        /* ��������֡���� */
    E_D07_ERRO_FRAME_0x68,          /* ����֡֡��ʼ�� 0x68 ��λ�ò��� */
    E_D07_ERRO_FRAME_CHECK_SUM,     /* ����֡����Ͳ��� */
    E_D07_ERRO_FRAME_END_0x16,      /* ����֡������ 0x16 ���� */
    E_D07_ERRO_NONE_FRAME,          // û���ҵ�֡

}eD07Err;









/* dlt645 2007��Լ���� **/
typedef enum
{
    E_D07_RULER_TYPE_UNKNOWN  =  0,                         // δ֪�Ĺ�Լ����

    /* ��׼Э�� */
    E_D07_RULER_TYPE_A1_MIN,
    
    /* [00] [00] [(00~FF)] [00] */
    E_D07_RULER_TYPE_COMB_HAVE_POWER_TOTAL = E_D07_RULER_TYPE_A1_MIN,// ����й��ܵ���
    E_D07_RULER_TYPE_COMB_HAVE_POWER_RATE,            // ����й����ʵ���
    E_D07_RULER_TYPE_COMB_HAVE_POWER_BLOCK,            // ����е������ݿ�

    /* [00] [01] [(00~FF)] [00] */
    E_D07_RULER_TYPE_FORTH_HAVE_POWER_TOTAL,        // �����й��ܵ���
    E_D07_RULER_TYPE_FORTH_HAVE_POWER_RATE,            // �����й����ʵ���
    E_D07_RULER_TYPE_FORTH_HAVE_POWER_BLOCK,        // �����й��������ݿ�

    /* [00] [02] [(00~FF)] [00] */
    E_D07_RULER_TYPE_BACK_HAVE_POWER_TOTAL,            // �����й��ܵ���
    E_D07_RULER_TYPE_BACK_HAVE_POWER_RATE,            // �����й����ʵ���
    E_D07_RULER_TYPE_BACK_HAVE_POWER_BLOCK,            // �����й��������ݿ�

    /* [00] [03] [(00~FF)] [00] */
    E_D07_RULER_TYPE_COMB_NONE_1_POWER_TOTAL,        // ����޹�1�ܵ���
    E_D07_RULER_TYPE_COMB_NONE_1_POWER_RATE,        // ����޹�1���ʵ���
    E_D07_RULER_TYPE_COMB_NONE_1_POWER_BLOCK,        // ����޹�1�������ݿ�

    /* [00] [04] [(00~FF)] [00] */
    E_D07_RULER_TYPE_COMB_NONE_2_POWER_TOTAL,        // ����޹�2�ܵ���
    E_D07_RULER_TYPE_COMB_NONE_2_POWER_RATE,        // ����޹�2���ʵ���
    E_D07_RULER_TYPE_COMB_NONE_2_POWER_BLOCK,        // ����޹�2�������ݿ�

    /* [00] [05] [(00~FF)] [00] */
    E_D07_RULER_TYPE_QUAD_1_NONE_POWER_TOTAL,        // ��һ�����޹��ܵ���
    E_D07_RULER_TYPE_QUAD_1_NONE_POWER_RATE,        // ��һ�����޹����ʵ���
    E_D07_RULER_TYPE_QUAD_1_NONE_POWER_BLOCK,        // ��һ�����޹��������ݿ�

    /* [00] [06] [(00~FF)] [00] */
    E_D07_RULER_TYPE_QUAD_2_NONE_POWER_TOTAL,        // �ڶ������޹��ܵ���
    E_D07_RULER_TYPE_QUAD_2_NONE_POWER_RATE,        // �ڶ������޹����ʵ���
    E_D07_RULER_TYPE_QUAD_2_NONE_POWER_BLOCK,        // �ڶ������޹��������ݿ�

    /* [00] [07] [(00~FF)] [00] */
    E_D07_RULER_TYPE_QUAD_3_NONE_POWER_TOTAL,        // ���������޹��ܵ���
    E_D07_RULER_TYPE_QUAD_3_NONE_POWER_RATE,        // ���������޹����ʵ���
    E_D07_RULER_TYPE_QUAD_3_NONE_POWER_BLOCK,        // ���������޹��������ݿ�

    /* [00] [08] [(00~FF)] [00] */
    E_D07_RULER_TYPE_QUAD_4_NONE_POWER_TOTAL,        // ���������޹��ܵ���
    E_D07_RULER_TYPE_QUAD_4_NONE_POWER_RATE,        // ���������޹����ʵ���
    E_D07_RULER_TYPE_QUAD_4_NONE_POWER_BLOCK,        // ���������޹��������ݿ�

    /* [00] [09] [(00~FF)] [00] */
    E_D07_RULER_TYPE_FORTH_APPARENT_POWER_TOTAL,    // ���������ܵ���
    E_D07_RULER_TYPE_FORTH_APPARENT_POWER_RATE,        // �������ڷ��ʵ���
    E_D07_RULER_TYPE_FORTH_APPARENT_POWER_BLOCK,    // �������ڵ������ݿ�

    /* [00] [0A] [(00~FF)] [00] */
    E_D07_RULER_TYPE_BACK_APPARENT_POWER_TOTAL,        // ���������ܵ���
    E_D07_RULER_TYPE_BACK_APPARENT_POWER_RATE,        // �������ڷ��ʵ���
    E_D07_RULER_TYPE_BACK_APPARENT_POWER_BLOCK,        // �������ڵ������ݿ�

    /* [00] [80][00] [00] */
    E_D07_RULER_TYPE_ASSO_POWER_TOTAL,                // �����ܵ���

    /* [00] [81][00] [00] */
    E_D07_RULER_TYPE_FORTH_FUND_HAVE_POWER_TOTAL,    // �����й������ܵ���

    /* [00] [82][00] [00] */
    E_D07_RULER_TYPE_BACK_FUND_HAVE_POWER_TOTAL,    // �����й������ܵ���

    /* [00] [83][00] [00] */
    E_D07_RULER_TYPE_FORTH_HARM_HAVE_POWER_TOTAL,    // �����й�г���ܵ���

    /* [00] [84][00] [00] */
    E_D07_RULER_TYPE_BACK_HARM_HAVE_POWER_TOTAL,    // �����й�г���ܵ���

    /* [00] [85][00] [00] */
    E_D07_RULER_TYPE_COPR_LOSS_HAVE_POWER_COMP_TOTAL,       // ͭ���й��ܵ��ܲ�����

    /* [00] [86][00] [00] */
    E_D07_RULER_TYPE_CORE_LOSS_HAVE_POWER_COMP_TOTAL,        // �����й��ܵ��ܲ�����

    /* [00] [(15~9A)][00] [00] */
    E_D07_RULER_TYPE_PHASE_A_FORTH_HAVE_POWER,                // A�������й�����
    E_D07_RULER_TYPE_PHASE_A_BACK_HAVE_POWER,                // A�෴���й�����
    E_D07_RULER_TYPE_PHASE_A_COMB_NONE_1_POWER,              // A������޹�1����
    E_D07_RULER_TYPE_PHASE_A_COMB_NONE_2_POWER,                // A������޹�2����
    E_D07_RULER_TYPE_PHASE_A_QUAD_1_NONE_POWER,              // A���һ�����޹�����
    E_D07_RULER_TYPE_PHASE_A_QUAD_2_NONE_POWER,                // A��ڶ������޹�����
    E_D07_RULER_TYPE_PHASE_A_QUAD_3_NONE_POWER,                // A����������޹�����
    E_D07_RULER_TYPE_PHASE_A_QUAD_4_NONE_POWER,                // A����������޹�����
    E_D07_RULER_TYPE_PHASE_A_FORTH_APPARENT_POWER,            // A���������ڵ���
    E_D07_RULER_TYPE_PHASE_A_BACK_APPARENT_POWER,            // A�෴�����ڵ���
    E_D07_RULER_TYPE_PHASE_A_ASSO_POWER,                    // A���������
    E_D07_RULER_TYPE_PHASE_A_FORTH_FUND_HAVE_POWER,            // A�������й���������
    E_D07_RULER_TYPE_PHASE_A_BACK_FUND_HAVE_POWER,            // A�෴���й���������
    E_D07_RULER_TYPE_PHASE_A_FORTH_HARM_HAVE_POWER,            // A�������й�г������
    E_D07_RULER_TYPE_PHASE_A_BACK_HARM_HAVE_POWER,            // A�෴���й�г������
    E_D07_RULER_TYPE_PHASE_A_COPR_LOSS_HAVE_POWER_COMP,       // A��ͭ���й����ܲ�����
    E_D07_RULER_TYPE_PHASE_A_CORE_LOSS_HAVE_POWER_COMP,        // A�������й����ܲ�����


    /* [00] [(29~AE)][00] [00] */
    E_D07_RULER_TYPE_PHASE_B_FORTH_HAVE_POWER,                // B�������й�����
    E_D07_RULER_TYPE_PHASE_B_BACK_HAVE_POWER,                // B�෴���й�����
    E_D07_RULER_TYPE_PHASE_B_COMB_NONE_1_POWER,              // B������޹�1����
    E_D07_RULER_TYPE_PHASE_B_COMB_NONE_2_POWER,                // B������޹�2����
    E_D07_RULER_TYPE_PHASE_B_QUAD_1_NONE_POWER,              // B���һ�����޹�����
    E_D07_RULER_TYPE_PHASE_B_QUAD_2_NONE_POWER,                // B��ڶ������޹�����
    E_D07_RULER_TYPE_PHASE_B_QUAD_3_NONE_POWER,                // B����������޹�����
    E_D07_RULER_TYPE_PHASE_B_QUAD_4_NONE_POWER,                // B����������޹�����
    E_D07_RULER_TYPE_PHASE_B_FORTH_APPARENT_POWER,            // B���������ڵ���
    E_D07_RULER_TYPE_PHASE_B_BACK_APPARENT_POWER,            // B�෴�����ڵ���
    E_D07_RULER_TYPE_PHASE_B_ASSO_POWER,                    // B���������
    E_D07_RULER_TYPE_PHASE_B_FORTH_FUND_HAVE_POWER,            // B�������й���������
    E_D07_RULER_TYPE_PHASE_B_BACK_FUND_HAVE_POWER,            // B�෴���й���������
    E_D07_RULER_TYPE_PHASE_B_FORTH_HARM_HAVE_POWER,            // B�������й�г������
    E_D07_RULER_TYPE_PHASE_B_BACK_HARM_HAVE_POWER,            // B�෴���й�г������
    E_D07_RULER_TYPE_PHASE_B_COPR_LOSS_HAVE_POWER_COMP,       // B��ͭ���й����ܲ�����
    E_D07_RULER_TYPE_PHASE_B_CORE_LOSS_HAVE_POWER_COMP,        // B�������й����ܲ�����


    /* [00] [(3D~C2)][00] [00] */
    E_D07_RULER_TYPE_PHASE_C_FORTH_HAVE_POWER,                // C�������й�����
    E_D07_RULER_TYPE_PHASE_C_BACK_HAVE_POWER,                // C�෴���й�����
    E_D07_RULER_TYPE_PHASE_C_COMB_NONE_1_POWER,              // C������޹�1����
    E_D07_RULER_TYPE_PHASE_C_COMB_NONE_2_POWER,                // C������޹�2����
    E_D07_RULER_TYPE_PHASE_C_QUAD_1_NONE_POWER,              // C���һ�����޹�����
    E_D07_RULER_TYPE_PHASE_C_QUAD_2_NONE_POWER,                // C��ڶ������޹�����
    E_D07_RULER_TYPE_PHASE_C_QUAD_3_NONE_POWER,                // C����������޹�����
    E_D07_RULER_TYPE_PHASE_C_QUAD_4_NONE_POWER,                // C����������޹�����
    E_D07_RULER_TYPE_PHASE_C_FORTH_APPARENT_POWER,            // C���������ڵ���
    E_D07_RULER_TYPE_PHASE_C_BACK_APPARENT_POWER,            // C�෴�����ڵ���
    E_D07_RULER_TYPE_PHASE_C_ASSO_POWER,                    // C���������
    E_D07_RULER_TYPE_PHASE_C_FORTH_FUND_HAVE_POWER,            // C�������й���������
    E_D07_RULER_TYPE_PHASE_C_BACK_FUND_HAVE_POWER,            // C�෴���й���������
    E_D07_RULER_TYPE_PHASE_C_FORTH_HARM_HAVE_POWER,            // C�������й�г������
    E_D07_RULER_TYPE_PHASE_C_BACK_HARM_HAVE_POWER,            // C�෴���й�г������
    E_D07_RULER_TYPE_PHASE_C_COPR_LOSS_HAVE_POWER_COMP,       // C��ͭ���й����ܲ�����
    E_D07_RULER_TYPE_PHASE_C_CORE_LOSS_HAVE_POWER_COMP,        // C�������й����ܲ�����


    // ��Ӧ��A.1�������ݱ�ʶ���������ʶ */
    E_D07_RULER_TYPE_A1_MAX = E_D07_RULER_TYPE_PHASE_C_CORE_LOSS_HAVE_POWER_COMP,        

    /* ��Ӧ��A.2 */
    E_D07_RULER_TYPE_A2_MIN,
    
    /* [01] [00] [(00~FF)] [00] */

    /* [01] [01] [(00~FF)] [00] */
    E_D07_RULER_TYPE_FORTH_HAVE_DEMAND_TOTAL = E_D07_RULER_TYPE_A2_MIN,        // �����й����������������ʱ��
    E_D07_RULER_TYPE_FORTH_HAVE_DEMAND_RATE,                // �����й������������������ʱ��
    E_D07_RULER_TYPE_FORTH_HAVE_DEMAND_BLOCK,                // �����й��������������ʱ�����ݿ�

    /* [01] [02] [(00~FF)] [00] */
    E_D07_RULER_TYPE_BACK_HAVE_DEMAND_TOTAL,                // �����й����������������ʱ��
    E_D07_RULER_TYPE_BACK_HAVE_DEMAND_RATE,                    // �����й������������������ʱ��
    E_D07_RULER_TYPE_BACK_HAVE_DEMAND_BLOCK,                // �����й��������������ʱ�����ݿ�

    /* [01] [03] [(00~FF)] [00] */
    E_D07_RULER_TYPE_COMB_NONE_1_DEMAND_TOTAL,                // ����޹�1���������������ʱ��
    E_D07_RULER_TYPE_COMB_NONE_1_DEMAND_RATE,                // ����޹�1�����������������ʱ��
    E_D07_RULER_TYPE_COMB_NONE_1_DEMAND_BLOCK,                // ����޹�1�������������ʱ�����ݿ�

    /* [01] [04] [(00~FF)] [00] */
    E_D07_RULER_TYPE_COMB_NONE_2_DEMAND_TOTAL,                // ����޹�2���������������ʱ��
    E_D07_RULER_TYPE_COMB_NONE_2_DEMAND_RATE,                // ����޹�2�����������������ʱ��
    E_D07_RULER_TYPE_COMB_NONE_2_DEMAND_BLOCK,                // ����޹�2�������������ʱ�����ݿ�

    /* [01] [05] [(00~FF)] [00] */
    E_D07_RULER_TYPE_QUAD_1_NONE_DEMAND_TOTAL,                // ��һ�����޹����������������ʱ��
    E_D07_RULER_TYPE_QUAD_1_NONE_DEMAND_RATE,                // ��һ�����޹������������������ʱ��
    E_D07_RULER_TYPE_QUAD_1_NONE_DEMAND_BLOCK,                // ��һ�����޹��������������ʱ�����ݿ�

    /* [01] [06] [(00~FF)] [00] */
    E_D07_RULER_TYPE_QUAD_2_NONE_DEMAND_TOTAL,                // �ڶ������޹����������������ʱ��
    E_D07_RULER_TYPE_QUAD_2_NONE_DEMAND_RATE,                // �ڶ������޹������������������ʱ��
    E_D07_RULER_TYPE_QUAD_2_NONE_DEMAND_BLOCK,                // �ڶ������޹��������������ʱ�����ݿ�

    /* [01] [07] [(00~FF)] [00] */
    E_D07_RULER_TYPE_QUAD_3_NONE_DEMAND_TOTAL,                // ���������޹����������������ʱ��
    E_D07_RULER_TYPE_QUAD_3_NONE_DEMAND_RATE,                // ���������޹������������������ʱ��
    E_D07_RULER_TYPE_QUAD_3_NONE_DEMAND_BLOCK,                // ���������޹��������������ʱ�����ݿ�

    /* [01] [08] [(00~FF)] [00] */
    E_D07_RULER_TYPE_QUAD_4_NONE_DEMAND_TOTAL,                // ���������޹����������������ʱ��
    E_D07_RULER_TYPE_QUAD_4_NONE_DEMAND_RATE,                // ���������޹������������������ʱ��
    E_D07_RULER_TYPE_QUAD_4_NONE_DEMAND_BLOCK,                // ���������޹��������������ʱ�����ݿ�

    /* [01] [09] [(00~FF)] [00] */
    E_D07_RULER_TYPE_FORTH_APPARENT_DEMAND_TOTAL,            // �����������������������ʱ��
    E_D07_RULER_TYPE_FORTH_APPARENT_DEMAND_RATE,            // �������ڷ����������������ʱ��
    E_D07_RULER_TYPE_FORTH_APPARENT_DEMAND_BLOCK,            // ���������������������ʱ�����ݿ�

    /* [01] [0A] [(00~FF)] [00] */
    E_D07_RULER_TYPE_BACK_APPARENT_DEMAND_TOTAL,            // �����������������������ʱ��
    E_D07_RULER_TYPE_BACK_APPARENT_DEMAND_RATE,                // �������ڷ����������������ʱ��
    E_D07_RULER_TYPE_BACK_APPARENT_DEMAND_BLOCK,            // ���������������������ʱ�����ݿ�

    /* [01] [(15~9A)][00] [00] */
    E_D07_RULER_TYPE_PHASE_A_FORTH_HAVE_DEMAND,                // A�������й��������������ʱ��
    E_D07_RULER_TYPE_PHASE_A_BACK_HAVE_DEMAND,                // A�෴���й��������������ʱ��
    E_D07_RULER_TYPE_PHASE_A_COMB_NONE_1_DEMAND,              // A������޹�1�������������ʱ��
    E_D07_RULER_TYPE_PHASE_A_COMB_NONE_2_DEMAND,            // A������޹�2�������������ʱ��
    E_D07_RULER_TYPE_PHASE_A_QUAD_1_NONE_DEMAND,              // A���һ�����޹��������������ʱ��
    E_D07_RULER_TYPE_PHASE_A_QUAD_2_NONE_DEMAND,            // A��ڶ������޹��������������ʱ��
    E_D07_RULER_TYPE_PHASE_A_QUAD_3_NONE_DEMAND,            // A����������޹��������������ʱ��
    E_D07_RULER_TYPE_PHASE_A_QUAD_4_NONE_DEMAND,            // A����������޹��������������ʱ��
    E_D07_RULER_TYPE_PHASE_A_FORTH_APPARENT_DEMAND,            // A�����������������������ʱ��
    E_D07_RULER_TYPE_PHASE_A_BACK_APPARENT_DEMAND,            // A�෴�������������������ʱ��


    /* [01] [(29~AE)][00] [00] */
    E_D07_RULER_TYPE_PHASE_B_FORTH_HAVE_DEMAND,                // B�������й��������������ʱ��
    E_D07_RULER_TYPE_PHASE_B_BACK_HAVE_DEMAND,                // B�෴���й��������������ʱ��
    E_D07_RULER_TYPE_PHASE_B_COMB_NONE_1_DEMAND,              // B������޹�1�������������ʱ��
    E_D07_RULER_TYPE_PHASE_B_COMB_NONE_2_DEMAND,            // B������޹�2�������������ʱ��
    E_D07_RULER_TYPE_PHASE_B_QUAD_1_NONE_DEMAND,              // B���һ�����޹��������������ʱ��
    E_D07_RULER_TYPE_PHASE_B_QUAD_2_NONE_DEMAND,            // B��ڶ������޹��������������ʱ��
    E_D07_RULER_TYPE_PHASE_B_QUAD_3_NONE_DEMAND,            // B����������޹��������������ʱ��
    E_D07_RULER_TYPE_PHASE_B_QUAD_4_NONE_DEMAND,            // B����������޹��������������ʱ��
    E_D07_RULER_TYPE_PHASE_B_FORTH_APPARENT_DEMAND,            // B�����������������������ʱ��
    E_D07_RULER_TYPE_PHASE_B_BACK_APPARENT_DEMAND,            // B�෴�������������������ʱ��

    /* [01] [(3D~C2)][00] [00] */
    E_D07_RULER_TYPE_PHASE_C_FORTH_HAVE_DEMAND,                // C�������й��������������ʱ��
    E_D07_RULER_TYPE_PHASE_C_BACK_HAVE_DEMAND,                // C�෴���й��������������ʱ��
    E_D07_RULER_TYPE_PHASE_C_COMB_NONE_1_DEMAND,              // C������޹�1�������������ʱ��
    E_D07_RULER_TYPE_PHASE_C_COMB_NONE_2_DEMAND,            // C������޹�2�������������ʱ��
    E_D07_RULER_TYPE_PHASE_C_QUAD_1_NONE_DEMAND,              // C���һ�����޹��������������ʱ��
    E_D07_RULER_TYPE_PHASE_C_QUAD_2_NONE_DEMAND,            // C��ڶ������޹��������������ʱ��
    E_D07_RULER_TYPE_PHASE_C_QUAD_3_NONE_DEMAND,            // C����������޹��������������ʱ��
    E_D07_RULER_TYPE_PHASE_C_QUAD_4_NONE_DEMAND,            // C����������޹��������������ʱ��
    E_D07_RULER_TYPE_PHASE_C_FORTH_APPARENT_DEMAND,            // C�����������������������ʱ��
    E_D07_RULER_TYPE_PHASE_C_BACK_APPARENT_DEMAND,            // C�෴�������������������ʱ��
    

    /* ��Ӧ��A.2�������������ʱ�����ݱ�ʶ����� */
    E_D07_RULER_TYPE_A2_MAX = E_D07_RULER_TYPE_PHASE_C_BACK_APPARENT_DEMAND,    

    /* ��Ӧ��A.3 �������ݱ�ʶ����� */
    E_D07_RULER_TYPE_A3_MIN,
    E_D07_RULER_TYPE_PHASE_A_VOLT = E_D07_RULER_TYPE_A3_MIN,// A���ѹ
    E_D07_RULER_TYPE_PHASE_B_VOLT,                            // B���ѹ
    E_D07_RULER_TYPE_PHASE_C_VOLT,                            // C���ѹ
    E_D07_RULER_TYPE_VOLT_BLOCK,                            // ��ѹ���ݿ�
    
    E_D07_RULER_TYPE_PHASE_A_ELEC,                            // A�����
    E_D07_RULER_TYPE_PHASE_B_ELEC,                            // B�����
    E_D07_RULER_TYPE_PHASE_C_ELEC,                            // C�����
    E_D07_RULER_TYPE_ELEC_BLOCK,                            // �������ݿ�

    E_D07_RULER_TYPE_INSTANT_HAVE_POWER_RATE_TOTAL,            // ˲ʱ���й�����    
    E_D07_RULER_TYPE_INSTANT_PHASE_A_HAVE_POWER_RATE,        // ˲ʱA���й�����
    E_D07_RULER_TYPE_INSTANT_PHASE_B_HAVE_POWER_RATE,        // ˲ʱB���й�����
    E_D07_RULER_TYPE_INSTANT_PHASE_C_HAVE_POWER_RATE,        // ˲ʱC���й�����
    E_D07_RULER_TYPE_INSTANT_HAVE_POWER_RATE_BLOCK,            // ˲ʱ�й��������ݿ�
    
    E_D07_RULER_TYPE_INSTANT_NONE_POWER_RATE_TOTAL,            // ˲ʱ���޹�����    
    E_D07_RULER_TYPE_INSTANT_PHASE_A_NONE_POWER_RATE,        // ˲ʱA���޹�����
    E_D07_RULER_TYPE_INSTANT_PHASE_B_NONE_POWER_RATE,        // ˲ʱB���޹�����
    E_D07_RULER_TYPE_INSTANT_PHASE_C_NONE_POWER_RATE,        // ˲ʱC���޹�����
    E_D07_RULER_TYPE_INSTANT_NONE_POWER_RATE_BLOCK,            // ˲ʱ�޹��������ݿ�

    E_D07_RULER_TYPE_INSTANT_APPARENT_POWER_RATE_TOTAL,        // ˲ʱ�����ڹ���    
    E_D07_RULER_TYPE_INSTANT_PHASE_A_APPARENT_POWER_RATE,    // ˲ʱA�����ڹ���
    E_D07_RULER_TYPE_INSTANT_PHASE_B_APPARENT_POWER_RATE,    // ˲ʱB�����ڹ���
    E_D07_RULER_TYPE_INSTANT_PHASE_C_APPARENT_POWER_RATE,    // ˲ʱC�����ڹ���
    E_D07_RULER_TYPE_INSTANT_APPARENT_POWER_RATE_BLOCK,        // ˲ʱ���ڹ������ݿ�

    E_D07_RULER_TYPE_POWER_RATE_FACTOR_TOTAL,                // �ܹ�������
    E_D07_RULER_TYPE_PHASE_A_POWER_RATE_FACTOR,                // A�๦������
    E_D07_RULER_TYPE_PHASE_B_POWER_RATE_FACTOR,                // B�๦������
    E_D07_RULER_TYPE_PHASE_C_POWER_RATE_FACTOR,                // C�๦������
    E_D07_RULER_TYPE_POWER_RATE_FACTOR_BLOCK,                // �����������ݿ�
    
    E_D07_RULER_TYPE_PHASE_A_ANGLE,                            // A�����
    E_D07_RULER_TYPE_PHASE_B_ANGLE,                            // B�����
    E_D07_RULER_TYPE_PHASE_C_ANGLE,                            // C�����
    E_D07_RULER_TYPE_ANGLE_BLOCK,                            // ������ݿ�
    
    E_D07_RULER_TYPE_PHASE_A_VOLT_WAVEFORM_DISTORTION,        // A���ѹ����ʧ���
    E_D07_RULER_TYPE_PHASE_B_VOLT_WAVEFORM_DISTORTION,        // B���ѹ����ʧ���
    E_D07_RULER_TYPE_PHASE_C_VOLT_WAVEFORM_DISTORTION,        // C���ѹ����ʧ���
    E_D07_RULER_TYPE_VOLT_WAVEFORM_DISTORTION_BLOCK,        // ��ѹ����ʧ������ݿ�
    
    E_D07_RULER_TYPE_PHASE_A_ELEC_WAVEFORM_DISTORTION,        // A���������ʧ���
    E_D07_RULER_TYPE_PHASE_B_ELEC_WAVEFORM_DISTORTION,        // B���������ʧ���
    E_D07_RULER_TYPE_PHASE_C_ELEC_WAVEFORM_DISTORTION,        // C���������ʧ���
    E_D07_RULER_TYPE_ELEC_WAVEFORM_DISTORTION_BLOCK,        // ��������ʧ������ݿ�
    
    E_D07_RULER_TYPE_PHASE_A_VOLT_HARMONIC_CONTENT_T,        // A���ѹ(t)��г������
    E_D07_RULER_TYPE_PHASE_A_VOLT_HARMONIC_CONTENT_BLOCK,    // A���ѹ��г���������ݿ�
    
    E_D07_RULER_TYPE_PHASE_B_VOLT_HARMONIC_CONTENT_T,        // B���ѹ(t)��г������
    E_D07_RULER_TYPE_PHASE_B_VOLT_HARMONIC_CONTENT_BLOCK,   // B���ѹг���������ݿ�
    
    E_D07_RULER_TYPE_PHASE_C_VOLT_HARMONIC_CONTENT_T,        // C���ѹ(t)��г������
    E_D07_RULER_TYPE_PHASE_C_VOLT_HARMONIC_CONTENT_BLOCK,   // C���ѹг���������ݿ�

    E_D07_RULER_TYPE_PHASE_A_ELEC_HARMONIC_CONTENT_T,        // A�����(t)��г������
    E_D07_RULER_TYPE_PHASE_A_ELEC_HARMONIC_CONTENT_BLOCK,    // A�����г���������ݿ�
    
    E_D07_RULER_TYPE_PHASE_B_ELEC_HARMONIC_CONTENT_T,        // C�����(t)��г������
    E_D07_RULER_TYPE_PHASE_B_ELEC_HARMONIC_CONTENT_BLOCK,    // C�����г���������ݿ�
    
    E_D07_RULER_TYPE_PHASE_C_ELEC_HARMONIC_CONTENT_T,        // C�����(t)��г������
    E_D07_RULER_TYPE_PHASE_C_ELEC_HARMONIC_CONTENT_BLOCK,    // C�����г���������ݿ�
    
    E_D07_RULER_TYPE_ZERO_LINE_ELEC,                        // ���ߵ���
    E_D07_RULER_TYPE_POWER_GRID_HZ,                            // ����Ƶ��
    E_D07_RULER_TYPE_1M_AVER_HAVE_POWER_RATE_TOTAL,            // һ�����й���ƽ������
    
    E_D07_RULER_TYPE_CURRENT_HAVE_POWER_DEMAND,                // ��ǰ�й�����
    E_D07_RULER_TYPE_CURRENT_NONE_POWER_DEMAND,                // ��ǰ�޹�����
    E_D07_RULER_TYPE_CURRENT_APPARENT_POWER_DEMAND,            // ��ǰ��������
    
    E_D07_RULER_TYPE_METER_TEMP,                            // �����¶�
    E_D07_RULER_TYPE_INTER_CLOCK_CELL_VOLT,                    // ʱ�ӵ�ص�ѹ(�ڲ�)
    E_D07_RULER_TYPE_READ_METER_CELL_VOLT,                    // ͣ�糭����ص�ѹ(�ⲿ)
    E_D07_RULER_TYPE_INTER_CLOCK_WORK_TIME,                    // �ڲ���ع���ʱ��
    
    E_D07_RULER_TYPE_A3_MAX = E_D07_RULER_TYPE_INTER_CLOCK_WORK_TIME,
    
    /* ��Ӧ�� A.4 �¼���¼���ݱ�ʶ����� */
    E_D07_RULER_TYPE_A4_MIN,                                /* ��A.4��Լ��Сֵ */
    E_D07_RULER_TYPE_PHASE_ABC_LOSS_VOLT_TIMES = E_D07_RULER_TYPE_A4_MIN,// ABC��ʧѹ���������ۼ�ʱ��
    E_D07_RULER_TYPE_PHASE_A_LOSS_VOLT_RECORD,                // ��(n)��A��ʧѹ��¼
    E_D07_RULER_TYPE_PHASE_B_LOSS_VOLT_RECORD,                // ��(n)��B��ʧѹ��¼
    E_D07_RULER_TYPE_PHASE_C_LOSS_VOLT_RECORD,                // ��(n)��C��ʧѹ��¼
        
    E_D07_RULER_TYPE_PHASE_ABC_LESS_VOLT_TIMES,                // ABC��Ƿѹ���������ۼ�ʱ��
    E_D07_RULER_TYPE_PHASE_A_LESS_VOLT_RECORD,                // ��(n)��A��Ƿѹ��¼
    E_D07_RULER_TYPE_PHASE_B_LESS_VOLT_RECORD,                // ��(n)��B��Ƿѹ��¼
    E_D07_RULER_TYPE_PHASE_C_LESS_VOLT_RECORD,                // ��(n)��C��Ƿѹ��¼
    
    E_D07_RULER_TYPE_PHASE_ABC_MORE_VOLT_TIMES,                // ABC���ѹ���������ۼ�ʱ��
    E_D07_RULER_TYPE_PHASE_A_MORE_VOLT_RECORD,                // ��(n)��A���ѹ��¼
    E_D07_RULER_TYPE_PHASE_B_MORE_VOLT_RECORD,                // ��(n)��B���ѹ��¼
    E_D07_RULER_TYPE_PHASE_C_MORE_VOLT_RECORD,                // ��(n)��C���ѹ��¼
    
    E_D07_RULER_TYPE_PHASE_ABC_DROP_TIMES,                    // ABC�������������ۼ�ʱ��
    E_D07_RULER_TYPE_PHASE_A_DROP_RECORD,                    // ��(n)��A������¼
    E_D07_RULER_TYPE_PHASE_B_DROP_RECORD,                    // ��(n)��B������¼
    E_D07_RULER_TYPE_PHASE_C_DROP_RECORD,                    // ��(n)��C������¼
    
    E_D07_RULER_TYPE_LOSS_VOLT_TIMES_TOTAL,                    // ȫʧѹ���������ۼ�ʱ��
    E_D07_RULER_TYPE_LOSS_ALL_VOLT_TIME_N,                    // ��(n)��ȫʧѹ����ʱ�̣�����ֵ������ʱ��
    E_D07_RULER_TYPE_APS_LOSS_ELEC_TIMES_TOTAL,                // ������Դʧ�緢�����������ۼ�ʱ��
    E_D07_RULER_TYPE_APS_LOSS_ELEC_TIME_N,                    // ��(n)�θ�����Դʧ�緢��ʱ�̣�����ʱ��
    
    E_D07_RULER_TYPE_VOLT_ANTI_PHASE_TIMES_TOTAL,            // ��ѹ�������ܴ��������ۼ�ʱ��
    E_D07_RULER_TYPE_VOLT_ANTI_PHASE_RECORD_N,                // ��(n)�ε�ѹ�������¼

    E_D07_RULER_TYPE_ELEC_ANTI_PHASE_TIMES_TOTAL,            // �����������ܴ��������ۼ�ʱ��
    E_D07_RULER_TYPE_ELEC_ANTI_PHASE_RECORD_N,                // ��(n)�ε����������¼
    
    E_D07_RULER_TYPE_VOLT_UNBALANCE_TIMES_TOTAL,            // ��ѹ��ƽ���ܴ��������ۼ�ʱ��
    E_D07_RULER_TYPE_VOLT_UNBALANCE_RECORD_N,                // ��(n)�ε�ѹ��ƽ���¼
    
    E_D07_RULER_TYPE_ELEC_UNBALANCE_TIMES_TOTAL,            // ������ƽ���ܴ��������ۼ�ʱ��
    E_D07_RULER_TYPE_ELEC_UNBALANCE_RECORD_N,                // ��(n)�ε�����ƽ���¼
    
    E_D07_RULER_TYPE_PHASE_ABC_LOSS_ELEC_TIMES,                // ABC��ʧ�����������ۼ�ʱ��
    E_D07_RULER_TYPE_PHASE_A_LOSS_ELEC_RECORD,                // ��(n)��A��ʧ����¼
    E_D07_RULER_TYPE_PHASE_B_LOSS_ELEC_RECORD,                // ��(n)��B��ʧ����¼
    E_D07_RULER_TYPE_PHASE_C_LOSS_ELEC_RECORD,                // ��(n)��C��ʧ����¼
    
    E_D07_RULER_TYPE_PHASE_ABC_MORE_ELEC_TIMES,                // ABC��������������ۼ�ʱ��
    E_D07_RULER_TYPE_PHASE_A_MORE_ELEC_RECORD,                // ��(n)��A�������¼
    E_D07_RULER_TYPE_PHASE_B_MORE_ELEC_RECORD,                // ��(n)��B�������¼
    E_D07_RULER_TYPE_PHASE_C_MORE_ELEC_RECORD,                // ��(n)��C�������¼
    
    E_D07_RULER_TYPE_PHASE_ABC_DROP_ELEC_TIMES,                // ABC��������������ۼ�ʱ��
    E_D07_RULER_TYPE_PHASE_A_DROP_ELEC_RECORD,                // ��(n)��A�������¼
    E_D07_RULER_TYPE_PHASE_B_DROP_ELEC_RECORD,                // ��(n)��B�������¼
    E_D07_RULER_TYPE_PHASE_C_DROP_ELEC_RECORD,                // ��(n)��C�������¼
    
    E_D07_RULER_TYPE_PHASE_ABC_BACKWARD_ELEC_TIMES,            // ABC�ೱ��������������ۼ�ʱ��
    E_D07_RULER_TYPE_PHASE_A_BACKWARD_ELEC_RECORD,            // ��(n)��A�ೱ�������¼
    E_D07_RULER_TYPE_PHASE_B_BACKWARD_ELEC_RECORD,            // ��(n)��B�ೱ�������¼
    E_D07_RULER_TYPE_PHASE_C_BACKWARD_ELEC_RECORD,            // ��(n)��C�ೱ�������¼
    
    E_D07_RULER_TYPE_PHASE_ABC_OVERLOAD_TIMES,                // ABC����ش��������ۼ�ʱ��
    E_D07_RULER_TYPE_PHASE_A_OVERLOAD_RECORD,                // ��(n)��A����ؼ�¼
    E_D07_RULER_TYPE_PHASE_B_OVERLOAD_RECORD,                // ��(n)��B����ؼ�¼
    E_D07_RULER_TYPE_PHASE_C_OVERLOAD_RECORD,                // ��(n)��C����ؼ�¼
    
    E_D07_RULER_TYPE_VOLT_PASS_PERCENT_M,                    // ��(n)�µ�ѹ�ϸ���ͳ������
    E_D07_RULER_TYPE_PHASE_A_VOLT_PASS_PERCENT_M,            // ��(n)��A���ѹ�ϸ���ͳ������
    E_D07_RULER_TYPE_PHASE_B_VOLT_PASS_PERCENT_M,            // ��(n)��B���ѹ�ϸ���ͳ������
    E_D07_RULER_TYPE_PHASE_C_VOLT_PASS_PERCENT_M,            // ��(n)��C���ѹ�ϸ���ͳ������
    
    E_D07_RULER_TYPE_POWER_DOWN_TIMES,                        // �����ܴ���
    E_D07_RULER_TYPE_POWER_DOWN_TIME_T,                        // ��(t)�ε��緢��ʱ�̣�����ʱ��
    
    E_D07_RULER_TYPE_OVER_LIMIT_MEMAND_TIMES,                // ���������ܴ�����¼
    E_D07_RULER_TYPE_FORTH_OVER_LIMIT_MEMAND_TIME_T,        // ��(t)�������й��������޼�¼    
    E_D07_RULER_TYPE_BACK_OVER_LIMIT_MEMAND_TIME_T,            // ��(t)�η����й��������޼�¼
    
    E_D07_RULER_TYPE_QUAD_1_OVER_LIMIT_MEMAND_TIME_T,        // ��(t)�ε�1�����޹��������޼�¼    
    E_D07_RULER_TYPE_QUAD_2_OVER_LIMIT_MEMAND_TIME_T,        // ��(t)�ε�2�����޹��������޼�¼
    E_D07_RULER_TYPE_QUAD_3_OVER_LIMIT_MEMAND_TIME_T,        // ��(t)�ε�3�����޹��������޼�¼
    E_D07_RULER_TYPE_QUAD_4_OVER_LIMIT_MEMAND_TIME_T,        // ��(t)�ε�4�����޹��������޼�¼
    
    E_D07_RULER_TYPE_METER_PROG_TIMES_TOTAL,                // ����ܴ���    
    E_D07_RULER_TYPE_METER_PROG_RECORD_T,                    // ��(t)�α�̼�¼
    
    E_D07_RULER_TYPE_METER_CLEAR_TIMES_TOTAL,                // ��������ܴ���    
    E_D07_RULER_TYPE_METER_CLEAR_RECORD_T,                    // ��(t)�ε�������¼
    
    E_D07_RULER_TYPE_DEMAND_CLEAR_TIMES_TOTAL,                // ���������ܴ���    
    E_D07_RULER_TYPE_DEMAND_CLEAR_RECORD_T,                    // ��(t)�����������¼
    
    E_D07_RULER_TYPE_EVENT_CLEAR_TIMES_TOTAL,                // �¼������ܴ���    
    E_D07_RULER_TYPE_EVENT_CLEAR_RECORD_T,                    // ��(t)���¼������¼
    
    E_D07_RULER_TYPE_ADJUST_TIME_TIMES_TOTAL,                // Уʱ�ܴ���    
    E_D07_RULER_TYPE_ADJUST_TIME_RECORD_T,                    // ��(t)��Уʱ��¼
    
    E_D07_RULER_TYPE_TIME_PART_PROG_TIMES_TOTAL,            // ʱ�α�����ܴ���    
    E_D07_RULER_TYPE_TIME_PART_PROG_RECORD_T,                // ��(t)��ʱ�α���̼�¼
    
    E_D07_RULER_TYPE_TIME_ZONE_PROG_TIMES_TOTAL,            // ʱ��������ܴ���    
    E_D07_RULER_TYPE_TIME_ZONE_PROG_RECORD_T,                // ��(t)��ʱ������̼�¼
    
    E_D07_RULER_TYPE_WEEKDAY_PROG_TIMES_TOTAL,                // �����ձ���ܴ���    
    E_D07_RULER_TYPE_WEEKDAY_PROG_RECORD_T,                    // ��(t)�������ձ�̼�¼
    
    E_D07_RULER_TYPE_HOLIDAY_PROG_TIMES_TOTAL,                // �ڼ��ձ���ܴ���    
    E_D07_RULER_TYPE_HOLIDAY_PROG_RECORD_T,                    // ��(t)�νڼ��ձ�̼�¼
    
    E_D07_RULER_TYPE_HAVE_COMB_PROG_TIMES_TOTAL,            // �й���Ϸ�ʽ����ܴ���    
    E_D07_RULER_TYPE_HAVE_COMB_PROG_RECORD_T,                // ��(t)���й���Ϸ�ʽ��̼�¼
    
    E_D07_RULER_TYPE_NONE_COMB_1_PROG_TIMES_TOTAL,            // �޹���Ϸ�ʽ1����ܴ���    
    E_D07_RULER_TYPE_NONE_COMB_1_PROG_RECORD_T,                // ��(t)���޹���Ϸ�ʽ1��̼�¼
    
    E_D07_RULER_TYPE_NONE_COMB_2_PROG_TIMES_TOTAL,            // �޹���Ϸ�ʽ2����ܴ���    
    E_D07_RULER_TYPE_NONE_COMB_2_PROG_RECORD_T,                // ��(t)���޹���Ϸ�ʽ2��̼�¼
    
    E_D07_RULER_TYPE_PAYOFF_DAY_PROG_TIMES_TOTAL,            // �����ձ���ܴ���    
    E_D07_RULER_TYPE_PAYOFF_DAY_PROG_RECORD_T,                // ��(t)�ν����ձ�̼�¼
    
    E_D07_RULER_TYPE_OPEN_METER_CAP_TIMES_TOTAL,            // �������ܴ���    
    E_D07_RULER_TYPE_OPEN_METER_CAP_RECORD_T,                // ��(t)�ο����Ǽ�¼
    
    E_D07_RULER_TYPE_OPEN_BTN_BOX_TIMES_TOTAL,                // ����ť���ܴ���    
    E_D07_RULER_TYPE_OPEN_BTN_BOX_RECORD_T,                    // ��(t)�ο���ť�м�¼
    
    E_D07_RULER_TYPE_A4_MAX = E_D07_RULER_TYPE_OPEN_BTN_BOX_RECORD_T, /* �� A.4 ��Լ���ֵ */
    
    /* ��Ӧ�� A.5 �α������ݱ�ʶ����� */
    E_D07_RULER_TYPE_A5_MIN,                                /* �� A.5 ��Լ��Сֵ */
    E_D07_RULER_TYPE_DATE = E_D07_RULER_TYPE_A5_MIN,        // ���ڼ����ڣ�����0���������죩
    E_D07_RULER_TYPE_TIME,                                    // ʱ��
    E_D07_RULER_TYPE_DEMAND_PERIOD,                            // �����������
    E_D07_RULER_TYPE_SLIT_TIME,                                // ����ʱ��
    E_D07_RULER_TYPE_ADJUST_PULSE_WEDTH,                    // У���������
    E_D07_RULER_TYPE_SWITCH_ZONE_TIME,                        // ����ʱ�����л�ʱ��
    E_D07_RULER_TYPE_SWITCH_PART_TIME,                        // ������ʱ�α��л�ʱ��
    E_D07_RULER_TYPE_YEAR_ZONE_P,                            // ��ʱ���� p <= 14
    E_D07_RULER_TYPE_DAY_PART_Q,                            // ��ʱ�α��� q <= 8
    E_D07_RULER_TYPE_DAY_PART_M,                            // ��ʱ����(ÿ���л���)m <=14
    E_D07_RULER_TYPE_RATE_K,                                // ������ k <= 63
    E_D07_RULER_TYPE_HOLIDAY_N,                                // ����������n <= 254
    E_D07_RULER_TYPE_HARMONIC_ANALY_TIMES,                    // г����������
    E_D07_RULER_TYPE_AUTO_DISPLAY_SCREENS,                    // �Զ�ѭ����ʾ����
    E_D07_RULER_TYPE_DISPLAY_TIME,                            // ÿ����ʾʱ��
    E_D07_RULER_TYPE_DISPLAY_POWER_DECIMAL_DIGITS,            // ��ʾ����С��λ��
    E_D07_RULER_TYPE_DISPLAY_DEMAND_DECIMAL_DIGITS,            // ��ʾ�������С��λ��
    E_D07_RULER_TYPE_PRESS_DISPLAY_SCREENS,                    // ����ѭ����ʾ����
    E_D07_RULER_TYPE_ADDRESS,                                // ͨ�ŵ�ַ
    E_D07_RULER_TYPE_METER_ID,                                // ����
    E_D07_RULER_TYPE_ASSETS_CODE,                            // �ʲ���������
    E_D07_RULER_TYPE_RATED_VOLT,                            // ���ѹ
    E_D07_RULER_TYPE_RATED_ELEC,                            // �����
    E_D07_RULER_TYPE_MAX_ELEC,                                // ������

    E_D07_RULER_TYPE_HAVE_ACCURACY_CLASS,                    // �й�׼ȷ�ȵȼ�
    E_D07_RULER_TYPE_NONE_ACCURACY_CLASS,                    // �޹�׼ȷ�ȵȼ�
        
    E_D07_RULER_TYPE_METER_HAVE_CONSTANT,                    // ����й�����
    E_D07_RULER_TYPE_METER_NONE_CONSTANT,                    // ����޹�����
    
    E_D07_RULER_TYPE_METER_MODEL_NUM,                        // ����ͺ�
    E_D07_RULER_TYPE_METER_PROD_DATE,                        // ��������
    E_D07_RULER_TYPE_METER_RULER_VERSION,                    // Э��汾��
    
    E_D07_RULER_TYPE_METER_RUN_STWD_1,                        // �������״̬�� 1
    E_D07_RULER_TYPE_METER_RUN_STWD_2,                        // �������״̬�� 2
    E_D07_RULER_TYPE_METER_RUN_STWD_3,                        // �������״̬�� 3
    E_D07_RULER_TYPE_METER_RUN_STWD_4,                        // �������״̬�� 4
    E_D07_RULER_TYPE_METER_RUN_STWD_5,                        // �������״̬�� 5
    E_D07_RULER_TYPE_METER_RUN_STWD_6,                        // �������״̬�� 6
    E_D07_RULER_TYPE_METER_RUN_STWD_7,                        // �������״̬�� 7
    E_D07_RULER_TYPE_METER_RUN_STWD_BLOCK,                    // �������״̬�����ݿ�
    E_D07_RULER_TYPE_HAVE_COMB_STWD,                        // �й���Ϸ�ʽ������
    E_D07_RULER_TYPE_NONE_COMB_1_STWD,                        // �޹���Ϸ�ʽ1������
    E_D07_RULER_TYPE_NONE_COMB_2_STWD,                        // �޹���Ϸ�ʽ2������
    
    E_D07_RULER_TYPE_MODEM_IRDA_RATE_STWD,                    // �����ͺ�����ͨ������������
    E_D07_RULER_TYPE_TOUCH_IRDA_RATE_STWD,                    // �Ӵ�ʽ������ͨ������������
    E_D07_RULER_TYPE_PART_1_RATE_STWD,                        // ͨ�ſ� 1 ͨ������������    
    E_D07_RULER_TYPE_PART_2_RATE_STWD,                        // ͨ�ſ� 2 ͨ������������    
    E_D07_RULER_TYPE_PART_3_RATE_STWD,                        // ͨ�ſ� 3 ͨ������������    
    
    E_D07_RULER_TYPE_WEEKDAY_STWD,                            // ������������
    E_D07_RULER_TYPE_WEEKDAY_TBL,                            // �����ղ��õ���ʱ�α���
    E_D07_RULER_TYPE_OVERLOAD_MODEL_STWD,                    // ���ɼ�¼ģʽ��
    E_D07_RULER_TYPE_FREEZE_MODEL_STWD,                        // ��������ģʽ��
    E_D07_RULER_TYPE_OVERLOAD_START_TIME,                    // ���ɼ�¼��ʼʱ��
    E_D07_RULER_TYPE_OVERLOAD_INTRV_TIME_1,                    // �� 1 �ฺ�ɼ�¼���ʱ��
    E_D07_RULER_TYPE_OVERLOAD_INTRV_TIME_2,                    // �� 2 �ฺ�ɼ�¼���ʱ��
    E_D07_RULER_TYPE_OVERLOAD_INTRV_TIME_3,                    // �� 3 �ฺ�ɼ�¼���ʱ��
    E_D07_RULER_TYPE_OVERLOAD_INTRV_TIME_4,                    // �� 4 �ฺ�ɼ�¼���ʱ��
    E_D07_RULER_TYPE_OVERLOAD_INTRV_TIME_5,                    // �� 5 �ฺ�ɼ�¼���ʱ��
    E_D07_RULER_TYPE_OVERLOAD_INTRV_TIME_6,                    // �� 6 �ฺ�ɼ�¼���ʱ��
    E_D07_RULER_TYPE_PAYOFF_DAY_1,                            // ÿ�µ� 1 ������
    E_D07_RULER_TYPE_PAYOFF_DAY_2,                            // ÿ�µ� 2 ������
    E_D07_RULER_TYPE_PAYOFF_DAY_3,                            // ÿ�µ� 3 ������
    
    E_D07_RULER_TYPE_PASSWORD_LV0,                            // 0 ������
    E_D07_RULER_TYPE_PASSWORD_LV1,                            // 1 ������
    E_D07_RULER_TYPE_PASSWORD_LV2,                            // 2 ������
    E_D07_RULER_TYPE_PASSWORD_LV3,                            // 3 ������
    E_D07_RULER_TYPE_PASSWORD_LV4,                            // 4 ������
    E_D07_RULER_TYPE_PASSWORD_LV5,                            // 5 ������
    E_D07_RULER_TYPE_PASSWORD_LV6,                            // 6 ������
    E_D07_RULER_TYPE_PASSWORD_LV7,                            // 7 ������
    E_D07_RULER_TYPE_PASSWORD_LV8,                            // 8 ������
    E_D07_RULER_TYPE_PASSWORD_LV9,                            // 9 ������
    
    E_D07_RULER_TYPE_PHASE_A_CONDUCT_FACTOR,                // A��絼ϵ��
    E_D07_RULER_TYPE_PHASE_A_SUSCEPT_FACTOR,                // A�����ϵ��
    E_D07_RULER_TYPE_PHASE_A_RESIST_FACTOR,                    // A�����ϵ��
    E_D07_RULER_TYPE_PHASE_A_REACTANCE_FACTOR,                // A��翹ϵ��
    
    E_D07_RULER_TYPE_PHASE_B_CONDUCT_FACTOR,                // B��絼ϵ��
    E_D07_RULER_TYPE_PHASE_B_SUSCEPT_FACTOR,                // B�����ϵ��
    E_D07_RULER_TYPE_PHASE_B_RESIST_FACTOR,                    // B�����ϵ��
    E_D07_RULER_TYPE_PHASE_B_REACTANCE_FACTOR,                // B��翹ϵ��
    
    E_D07_RULER_TYPE_PHASE_C_CONDUCT_FACTOR,                // C��絼ϵ��
    E_D07_RULER_TYPE_PHASE_C_SUSCEPT_FACTOR,                // C�����ϵ��
    E_D07_RULER_TYPE_PHASE_C_RESIST_FACTOR,                    // C�����ϵ��
    E_D07_RULER_TYPE_PHASE_C_REACTANCE_FACTOR,                // C��翹ϵ��
    
    E_D07_RULER_TYPE_FORTH_HAVE_POWER_MAX,                    // �����й���������ֵ
    E_D07_RULER_TYPE_BACK_HAVE_POWER_MAX,                    // �����й���������ֵ
    
    E_D07_RULER_TYPE_VOLT_MAX,                                // ��ѹ����ֵ
    E_D07_RULER_TYPE_VOLT_MIN,                                // ��ѹ����ֵ
    
    E_D07_RULER_TYPE_DAY_PART_DATA_1,                        // ��һ��ʱ��������    
    E_D07_RULER_TYPE_DAY_PART_DATA_1_T,                        // ��һ�׵�(t)��ʱ�α����� t(1~8)
    E_D07_RULER_TYPE_DAY_PART_DATA_2,                        // �ڶ���ʱ��������    
    E_D07_RULER_TYPE_DAY_PART_DATA_2_T,                        // �ڶ��׵�(t)��ʱ�α����� t(1~8)
    
    E_D07_RULER_TYPE_HOLIDAY_DATE_T,                        // �� (t)�����������ڼ���ʱ�α��� t(1~254)

    E_D07_RULER_TYPE_AUTO_DISPLAY_SCREEN_T,                    // �Զ�ѭ����ʾ��(t)����ʾ������ t(1~254)
    E_D07_RULER_TYPE_PREES_DISPLAY_SCREEN_T,                // ����ѭ����ʾ��(t)����ʾ������ t(1~254)
    E_D07_RULER_TYPE_FACTORY_SOFTWARE_VERSION,                // ���������汾��
    E_D07_RULER_TYPE_FACTORY_HARDWARE_VERSION,                // ����Ӳ���汾��
    E_D07_RULER_TYPE_FACTORY_SERIAL_NUM,                    // ���ұ��
    E_D07_RULER_TYPE_A5_MAX = E_D07_RULER_TYPE_FACTORY_SERIAL_NUM,/* �� A.5 ��Լ���ֵ */
    
    /* ��Ӧ�� A.6 �������ݱ�ʶ����� */
    /* t(1~12)*/
    E_D07_RULER_TYPE_A6_MIN,                                /* �� A.6 ��Լ��Сֵ */    
    E_D07_RULER_TYPE_FIX_FREZ_TIME_T = E_D07_RULER_TYPE_A6_MIN,    // ��(t)�ζ�ʱ����ʱ��
    E_D07_RULER_TYPE_FIX_FREZ_FORTH_HAVE_POWER_T,            // ��(t)�ζ�ʱ���������й���������
    E_D07_RULER_TYPE_FIX_FREZ_BACK_HAVE_POWER_T,            // ��(t)�ζ�ʱ���ᷴ���й���������
    E_D07_RULER_TYPE_FIX_FREZ_COMB_1_NONE_POWER_T,            // ��(t)�ζ�ʱ��������޹�1��������
    E_D07_RULER_TYPE_FIX_FREZ_COMB_2_NONE_POWER_T,            // ��(t)�ζ�ʱ��������޹�2��������
    E_D07_RULER_TYPE_FIX_FREZ_PHASE_1_NONE_POWER_T,            // ��(t)�ζ�ʱ�����һ�����޹���������
    E_D07_RULER_TYPE_FIX_FREZ_PHASE_2_NONE_POWER_T,            // ��(t)�ζ�ʱ����ڶ������޹���������
    E_D07_RULER_TYPE_FIX_FREZ_PHASE_3_NONE_POWER_T,            // ��(t)�ζ�ʱ������������޹���������
    E_D07_RULER_TYPE_FIX_FREZ_PHASE_4_NONE_POWER_T,            // ��(t)�ζ�ʱ������������޹���������
    E_D07_RULER_TYPE_FIX_FREZ_FORTH_HAVE_DEMAND_T,            // ��(t)�ζ�ʱ���������й�����������ݼ�����ʱ������
    E_D07_RULER_TYPE_FIX_FREZ_BACK_HAVE_DEMAND_T,            // ��(t)�ζ�ʱ���ᷴ���й�����������ݼ�����ʱ������
    E_D07_RULER_TYPE_FIX_FREZ_VAR_T,                        // ��(t)�ζ�ʱ�����������
    E_D07_RULER_TYPE_FIX_FREZ_BLOCK_T,                        // ��(t)�ζ�ʱ�������ݿ�
    
    /* t (1~3)*/
    E_D07_RULER_TYPE_INST_FREZ_TIME_T,                        // ��(t)��˲ʱ����ʱ��
    E_D07_RULER_TYPE_INST_FREZ_FORTH_HAVE_POWER_T,            // ��(t)��˲ʱ���������й���������
    E_D07_RULER_TYPE_INST_FREZ_BACK_HAVE_POWER_T,            // ��(t)��˲ʱ���ᷴ���й���������
    E_D07_RULER_TYPE_INST_FREZ_COMB_1_NONE_POWER_T,            // ��(t)��˲ʱ��������޹���������
    E_D07_RULER_TYPE_INST_FREZ_COMB_2_NONE_POWER_T,            // ��(t)��˲ʱ��������޹���������
    E_D07_RULER_TYPE_INST_FREZ_PHASE_1_NONE_POWER_T,        // ��(t)��˲ʱ�����һ�����޹���������
    E_D07_RULER_TYPE_INST_FREZ_PHASE_2_NONE_POWER_T,        // ��(t)��˲ʱ����ڶ������޹���������
    E_D07_RULER_TYPE_INST_FREZ_PHASE_3_NONE_POWER_T,        // ��(t)��˲ʱ������������޹���������
    E_D07_RULER_TYPE_INST_FREZ_PHASE_4_NONE_POWER_T,        // ��(t)��˲ʱ������������޹���������
    E_D07_RULER_TYPE_INST_FREZ_FORTH_HAVE_DEMAND_T,            // ��(t)��˲ʱ���������й�����������ݼ�����ʱ������
    E_D07_RULER_TYPE_INST_FREZ_BACK_HAVE_DEMAND_T,            // ��(t)��˲ʱ���ᷴ���й�����������ݼ�����ʱ������
    E_D07_RULER_TYPE_INST_FREZ_BLOCK_T,                        // ��(t)��˲ʱ�������ݿ�

    /* t (1~2) */
    E_D07_RULER_TYPE_SWITCH_ZONE_TIME_T,                    // ��(t)�� ����ʱ�����л�ʱ��
    E_D07_RULER_TYPE_SWITCH_ZONE_FORTH_HAVE_POWER_T,        // ��(t)�� ����ʱ�����л������й���������
    E_D07_RULER_TYPE_SWITCH_ZONE_BACK_HAVE_POWER_T,            // ��(t)�� ����ʱ�����л������й���������
    E_D07_RULER_TYPE_SWITCH_ZONE_COMB_1_NONE_POWER_T,        // ��(t)�� ����ʱ�����л�����޹���������
    E_D07_RULER_TYPE_SWITCH_ZONE_COMB_2_NONE_POWER_T,        // ��(t)�� ����ʱ�����л�����޹���������
    E_D07_RULER_TYPE_SWITCH_ZONE_QUAD_1_NONE_POWER_T,        // ��(t)�� ����ʱ�����л���һ�����޹���������
    E_D07_RULER_TYPE_SWITCH_ZONE_QUAD_2_NONE_POWER_T,        // ��(t)�� ����ʱ�����л��ڶ������޹���������
    E_D07_RULER_TYPE_SWITCH_ZONE_QUAD_3_NONE_POWER_T,        // ��(t)�� ����ʱ�����л����������޹���������
    E_D07_RULER_TYPE_SWITCH_ZONE_QUAD_4_NONE_POWER_T,        // ��(t)�� ����ʱ�����л����������޹���������
    E_D07_RULER_TYPE_SWITCH_ZONE_FORTH_HAVE_DEMAND_T,        // ��(t)�� ����ʱ�����л������й��������������ʱ������
    E_D07_RULER_TYPE_SWITCH_ZONE_BACK_HAVE_DEMAND_T,           // ��(t)�� ����ʱ�����л������й��������������ʱ������
    E_D07_RULER_TYPE_SWITCH_ZONE_VAR_DATA_T,                   // ��(t)�� ����ʱ�����л���������
    E_D07_RULER_TYPE_SWITCH_ZONE_BLOCK_T,                       // ��(t)�� ����ʱ�����л����ݿ�
    
    /* t (1~2) */
    E_D07_RULER_TYPE_SWITCH_PART_TIME_T,                    // ��(t)�� ������ʱ�α��л�ʱ��
    E_D07_RULER_TYPE_SWITCH_PART_FORTH_HAVE_POWER_T,        // ��(t)�� ������ʱ�α��л������й���������
    E_D07_RULER_TYPE_SWITCH_PART_BACK_HAVE_POWER_T,            // ��(t)�� ������ʱ�α��л������й���������
    E_D07_RULER_TYPE_SWITCH_PART_COMB_1_NONE_POWER_T,        // ��(t)�� ������ʱ�α��л�����޹���������
    E_D07_RULER_TYPE_SWITCH_PART_COMB_2_NONE_POWER_T,        // ��(t)�� ������ʱ�α��л�����޹���������
    E_D07_RULER_TYPE_SWITCH_PART_QUAD_1_NONE_POWER_T,        // ��(t)�� ������ʱ�α��л���һ�����޹���������
    E_D07_RULER_TYPE_SWITCH_PART_QUAD_2_NONE_POWER_T,        // ��(t)�� ������ʱ�α��л��ڶ������޹���������
    E_D07_RULER_TYPE_SWITCH_PART_QUAD_3_NONE_POWER_T,        // ��(t)�� ������ʱ�α��л����������޹���������
    E_D07_RULER_TYPE_SWITCH_PART_QUAD_4_NONE_POWER_T,        // ��(t)�� ������ʱ�α��л����������޹���������
    E_D07_RULER_TYPE_SWITCH_PART_FORTH_HAVE_DEMAND_T,        // ��(t)�� ������ʱ�α��л������й��������������ʱ������
    E_D07_RULER_TYPE_SWITCH_PART_BACK_HAVE_DEMAND_T,           // ��(t)�� ������ʱ�α��л������й��������������ʱ������
    E_D07_RULER_TYPE_SWITCH_PART_VAR_DATA_T,                   // ��(t)�� ������ʱ�α��л���������
    E_D07_RULER_TYPE_SWITCH_PART_BLOCK_T,                       // ��(t)�� ������ʱ�α��л����ݿ�

    E_D07_RULER_TYPE_A6_MAX = E_D07_RULER_TYPE_SWITCH_PART_BLOCK_T,    /* �� A.6 ��Լ���ֵ */    
    
    /* ��Ӧ�� A.7 ���ɼ�¼���ݱ���� */
    E_D07_RULER_TYPE_A7_MIN,                                /* �� A.7 ��Լ��Сֵ */    
    E_D07_RULER_TYPE_EARLY_OVERLOAD_RECORD = E_D07_RULER_TYPE_A7_MIN,    // �����¼��
    E_D07_RULER_TYPE_GIVEN_OVERLOAD_RECORD,                    // ����ʱ���¼��
    E_D07_RULER_TYPE_RECNT_OVERLOAD_RECORD,                    // ���һ����¼��
    
    E_D07_RULER_TYPE_EARLY_OVERLOAD_RECORD_1,                // ��һ�ฺ�� �����¼��
    E_D07_RULER_TYPE_GIVEN_OVERLOAD_RECORD_1,                // ��һ�ฺ�� ����ʱ���¼��
    E_D07_RULER_TYPE_RECNT_OVERLOAD_RECORD_1,                // ��һ�ฺ�� ���һ����¼��

    E_D07_RULER_TYPE_EARLY_OVERLOAD_RECORD_2,                // �ڶ��ฺ�� �����¼��
    E_D07_RULER_TYPE_GIVEN_OVERLOAD_RECORD_2,                // �ڶ��ฺ�� ����ʱ���¼��
    E_D07_RULER_TYPE_RECNT_OVERLOAD_RECORD_2,                // �ڶ��ฺ�� ���һ����¼��

    E_D07_RULER_TYPE_EARLY_OVERLOAD_RECORD_3,                // �����ฺ�� �����¼��
    E_D07_RULER_TYPE_GIVEN_OVERLOAD_RECORD_3,                // �����ฺ�� ����ʱ���¼��
    E_D07_RULER_TYPE_RECNT_OVERLOAD_RECORD_3,                // �����ฺ�� ���һ����¼��

    E_D07_RULER_TYPE_EARLY_OVERLOAD_RECORD_4,                // �����ฺ�� �����¼��
    E_D07_RULER_TYPE_GIVEN_OVERLOAD_RECORD_4,                // �����ฺ�� ����ʱ���¼��
    E_D07_RULER_TYPE_RECNT_OVERLOAD_RECORD_4,                // �����ฺ�� ���һ����¼��

    E_D07_RULER_TYPE_EARLY_OVERLOAD_RECORD_5,                // �����ฺ�� �����¼��
    E_D07_RULER_TYPE_GIVEN_OVERLOAD_RECORD_5,                // �����ฺ�� ����ʱ���¼��
    E_D07_RULER_TYPE_RECNT_OVERLOAD_RECORD_5,                // �����ฺ�� ���һ����¼��

    E_D07_RULER_TYPE_EARLY_OVERLOAD_RECORD_6,                // �����ฺ�� �����¼��
    E_D07_RULER_TYPE_GIVEN_OVERLOAD_RECORD_6,                // �����ฺ�� ����ʱ���¼��
    E_D07_RULER_TYPE_RECNT_OVERLOAD_RECORD_6,                // �����ฺ�� ���һ����¼��
    E_D07_RULER_TYPE_A7_MAX = E_D07_RULER_TYPE_RECNT_OVERLOAD_RECORD_6,    /* �� A.7 ��Լ���ֵ */
    

    /* �û���չ */
    





}E_D07_RULER_TYPE;
/** dlt645 2007��Լ���� */




/* DLT645 2007�� ��Լ��������� */
typedef enum
{
    E_DLT64507_RULER_TABEL_POWER,          /* ��Ӧ��A.1 ���������ݱ�ʶ����� */
    E_DLT64507_RULER_TABEL_DEMAND,      /* ��Ӧ��A.2 �������������ʱ�����ݱ�ʶ����� */
    E_DLT64507_RULER_TABEL_VAR,            /* ��Ӧ��A.3 �������ݱ�ʶ����� */
    E_DLT64507_RULER_TABEL_EVENT,        /* ��Ӧ��A.4 �¼���¼���ݱ�ʶ����� */
    E_DLT64507_RULER_TABEL_PARA,         /* ��Ӧ��A.5 �α������ݱ�ʶ����� */
    E_DLT64507_RULER_TABEL_FREEZE,      /* ��Ӧ��A.6 �������ݱ�ʶ����� */
    E_DLT64507_RULER_TABEL_LOAD,        /* ��Ӧ��A.7 ���ɼ�¼���ݱ�ʶ����� */
    E_DLT64507_RULER_TABEL_EXT,            /* ��Ӧ��A.8 �û��Զ������ݱ�ʶ����� */

}E_DLT645_07_RULER_TABEL_TYPE;



/* ���������� */
typedef enum
{
    E_D07_PAYOFF_NULL,      // �����ĸò���
    E_D07_PAYOFF_CURRENT, /* ��ǰ */
    E_D07_PAYOFF_PRE_1,      /* �� 1 ������ */
    E_D07_PAYOFF_PRE_2,      /* �� 2 ������ */
    E_D07_PAYOFF_PRE_3,      /* �� 3 ������ */
    E_D07_PAYOFF_PRE_4,      /* �� 4 ������ */
    E_D07_PAYOFF_PRE_5,      /* �� 5 ������ */
    E_D07_PAYOFF_PRE_6,      /* �� 6 ������ */
    E_D07_PAYOFF_PRE_7,      /* �� 7 ������ */
    E_D07_PAYOFF_PRE_8,      /* �� 8 ������ */
    E_D07_PAYOFF_PRE_9,      /* �� 9 ������ */
    E_D07_PAYOFF_PRE_10,  /* �� 10 ������ */
    E_D07_PAYOFF_PRE_11,  /* �� 11 ������ */
    E_D07_PAYOFF_PRE_12,  /* �� 12 ������ */
     
}E_D07_PARA_PAYOFF;


/* ���� г������ */
typedef enum
{

    E_D07_HARM_NULL,        // ������г������
    E_D07_HARM_1,            // 1��г��
    E_D07_HARM_2,            // 2��г��
    E_D07_HARM_3,            // 3��г��
    E_D07_HARM_4,            // 4��г��
    E_D07_HARM_5,            // 5��г��
    E_D07_HARM_6,            // 6��г��
    E_D07_HARM_7,            // 7��г��
    E_D07_HARM_8,            // 8��г��
    E_D07_HARM_9,            // 9��г��
    E_D07_HARM_10,            // 10��г��
    E_D07_HARM_11,            // 11��г��
    E_D07_HARM_12,            // 12��г��
    E_D07_HARM_13,            // 13��г��
    E_D07_HARM_14,            // 14��г��
    E_D07_HARM_15,            // 15��г��
    E_D07_HARM_16,            // 16��г��
    E_D07_HARM_17,            // 17��г��
    E_D07_HARM_18,            // 18��г��
    E_D07_HARM_19,            // 19��г��
    E_D07_HARM_20,            // 20��г��
    E_D07_HARM_21,            // 21��г��

}E_D07_PARA_HARM;

/* ������N���� */
typedef enum
{
    E_D07_LAST_NULL,        // �ϲ��ش���
    E_D07_LAST_1,            // ��1��
    E_D07_LAST_2,            // ��2��
    E_D07_LAST_3,            // ��3��
    E_D07_LAST_4,            // ��4��
    E_D07_LAST_5,            // ��5��
    E_D07_LAST_6,            // ��6��
    E_D07_LAST_7,            // ��7��
    E_D07_LAST_8,            // ��8��
    E_D07_LAST_9,            // ��9��
    E_D07_LAST_10,            // ��10��    
    E_D07_LAST_11,            // ��11��
    E_D07_LAST_12,            // ��12��    
}E_D07_PARA_LAST;

/* ��Լ�������� */
typedef enum
{
    E_D07_RATE_NULL,        // �����ķ��ʲ���
    E_D07_RATE_1,            // ����
    E_D07_RATE_2,            // ����2
    E_D07_RATE_3,            // ����3
    E_D07_RATE_4,            // ����4
    E_D07_RATE_5,            // ����5
    E_D07_RATE_6,            // ����6
    E_D07_RATE_7,            // ����7
    E_D07_RATE_8,            // ����8
    E_D07_RATE_9,            // ����9
    E_D07_RATE_10,            // ����10
    E_D07_RATE_11,            // ����11
    E_D07_RATE_12,            // ����12
    E_D07_RATE_13,            // ����13
    E_D07_RATE_14,            // ����14
    E_D07_RATE_15,            // ����15
    E_D07_RATE_16,            // ����16
    E_D07_RATE_17,            // ����17
    E_D07_RATE_18,            // ����18
    E_D07_RATE_19,            // ����19
    E_D07_RATE_20,            // ����20
    E_D07_RATE_21,            // ����21
    E_D07_RATE_22,            // ����22
    E_D07_RATE_23,            // ����23
    E_D07_RATE_24,            // ����24
    E_D07_RATE_25,            // ����25
    E_D07_RATE_26,            // ����26
    E_D07_RATE_27,            // ����27
    E_D07_RATE_28,            // ����28
    E_D07_RATE_29,            // ����29
    E_D07_RATE_30,            // ����30
    E_D07_RATE_31,            // ����31
    E_D07_RATE_32,            // ����32
    E_D07_RATE_33,            // ����33
    E_D07_RATE_34,            // ����34
    E_D07_RATE_35,            // ����35
    E_D07_RATE_36,            // ����36
    E_D07_RATE_37,            // ����37
    E_D07_RATE_38,            // ����38
    E_D07_RATE_39,            // ����39
    E_D07_RATE_40,            // ����40
    E_D07_RATE_41,            // ����41
    E_D07_RATE_42,            // ����42
    E_D07_RATE_43,            // ����43
    E_D07_RATE_44,            // ����44
    E_D07_RATE_45,            // ����45
    E_D07_RATE_46,            // ����46
    E_D07_RATE_47,            // ����47
    E_D07_RATE_48,            // ����48
    E_D07_RATE_49,            // ����49
    E_D07_RATE_50,            // ����50
    E_D07_RATE_51,            // ����51
    E_D07_RATE_52,            // ����52
    E_D07_RATE_53,            // ����53
    E_D07_RATE_54,            // ����54
    E_D07_RATE_55,            // ����55
    E_D07_RATE_56,            // ����56
    E_D07_RATE_57,            // ����57
    E_D07_RATE_58,            // ����58
    E_D07_RATE_59,            // ����59
    E_D07_RATE_60,            // ����60
    E_D07_RATE_61,            // ����61
    E_D07_RATE_62,            // ����62
    E_D07_RATE_63,            // ����63
    E_D07_RATE_64,            // ����64
}E_D07_PARA_RATE;


/* �ṹ */












/* ����ת������ */
typedef enum
{
    E_D07_TRANS_U2F,    // ���ݸ�ʽ���û���ת����֡��
    E_D07_TRANS_F2U,    // ���ݸ�ʽ��֡��ת�����û���
    
}E_D07_TRANS_FLG;

typedef eD07Err (*F_D07_RULER_TRANS)(E_D07_TRANS_FLG, char*, char*);

/* ��Լ�ĸ�ʽ���� */
typedef enum
{    
    E_D07_FMT_UNKOWN,                // δ֪ 
    E_D07_FMT_XXXX,                    // XXXX
    E_D07_FMT_XX_2 = E_D07_FMT_XXXX,// XXXX
    E_D07_FMT_XXXXXX,                // XXXXXX
    E_D07_FMT_XX_3 = E_D07_FMT_XXXXXX,
    E_D07_FMT_XX_4,                    // XX �ظ�4��
    E_D07_FMT_XX_6,                    // XX �ظ�6��
    E_D07_FMT_XX_8,                    // XX �ظ�8��
    E_D07_FMT_XX_10,                // XX �ظ�10��
    E_D07_FMT_XX_16,                // XX �ظ�16��
    E_D07_FMT_X_XXX,                // X.XXX
    E_D07_FMT_XX_XX,                // XX.XX
    E_D07_FMT_XX_XXXX,                // XX.XXXX
    E_D07_FMT_XX_XXXX_8,            // XX.XXXX
    E_D07_FMT_XXX_X,                // XXX.X
    E_D07_FMT_XXX_XXX,                // XXX.XXX
    E_D07_FMT_XXXXXX_XX,            // XXXXXX.XX
    E_D07_FMT_XXXXXXXX,                // XXXXXXXX
    E_D07_FMT_XXXXXX_2,                // XXXXXX �ظ�2��
    E_D07_FMT_XXXXXX_6,                // XXXXXX �ظ�6��
    E_D07_FMT_NN,                     // NN 
    E_D07_FMT_NNNN,                 // NNNN 
    E_D07_FMT_NN_4,                 // NN 
    E_D07_FMT_NN_6,                 // NN 
    E_D07_FMT_NN_32,                 // NN 
    E_D07_FMT_N_NNN,                 // N.NNN 
    E_D07_FMT_NN_NNNN,                 // NN.NNNN 
    E_D07_FMT_NNN_N,                 // NNN.N 
    E_D07_FMT_hhmmss,                // hhmmss 
    E_D07_FMT_MMDDhhmm,                // MMDDhhmm
    E_D07_FMT_MMDDNN_14,            // MMDDNN �ظ�14��
    E_D07_FMT_hhmmNN_14,            // hhmmNN �ظ�14��
    E_D07_FMT_DDhh,                    // DDhh
    E_D07_FMT_YYMMDDWW,                // YYMMDDWW 
    E_D07_FMT_YYMMDDNN,                // YYMMDDWW 
    E_D07_FMT_YYMMDDhhmm,            // YYMMDDhhmm 
    E_D07_FMT_YYMMDDhhmmNN,            // YYMMDDhhmm
    E_D07_FMT_YYMMDDhhmmss,            // YYMMDDhhmmss 
    E_D07_FMT_YYMMDDhhmmss_2,        // YYMMDDhhmmss YYMMDDhhmmss
    E_D07_FMT_YYMMDDhhmmss_2_XX_XXXX_YYMMDDhhmm,        // YYMMDDhhmmss YYMMDDhhmmss xx.xxxx YYMMDDhhmm
    E_D07_FMT_XX_XXXX_YYMMDDhhmm,    /* XX.XXXX
                                       YYMMDDhhmm */
    E_D07_FMT_YYMMDDhhmmss_XXX_XXX_YYMMDDhhmmss,    /* YYMMDDhhmmss
                                                        XXX.XXXX
                                                        YYMMDDhhmmss */

    // ���ӽ�����ݸ�ʽ����
    E_D07_FMT_RECD_LOSS_LESS_VOLT,        // ʧѹ Ƿѹ���ݸ�ʽ    
    E_D07_FMT_RECD_ANTI_PHASE,    // ���������ݸ�ʽ
    E_D07_FMT_RECD_UN_BALANCE,    // ��ƽ�����ݸ�ʽ    
    E_D07_FMT_RECD_LESS_MORE_LOSS_ELEC,        // LESS MORE LOSS ʧ�����������������ݼ�¼��ʽ
    E_D07_FMT_RECD_VOLT_PASS_PERCENT,        // ��ѹ�ϸ�������ͳ��
    E_D07_FMT_RECD_METER_PROG,        // ��ѹ�ϸ�������ͳ��
    E_D07_FMT_RECD_METER_CLEAR,        // ��ѹ�ϸ�������ͳ��
    E_D07_FMT_RECD_DEAMD_CLEAR,        // ��ѹ�ϸ�������ͳ��
    E_D07_FMT_RECD_EVENT_CLEAR,        // ��ѹ�ϸ�������ͳ��
    E_D07_FMT_RECD_ADJUST_TIME,        // ��ѹ�ϸ�������ͳ��
    E_D07_FMT_RECD_PART_PROG,        // ʱ�α���̼�¼
    E_D07_FMT_RECD_ZONE_PROG,        // ʱ������̼�¼
    E_D07_FMT_RECD_WEEKDAY_PROG,
    E_D07_FMT_RECD_HOLIDAY_PROG,
    E_D07_FMT_RECD_POWER_PROG,
    E_D07_FMT_RECD_PAYOFF_PROG,
    E_D07_FMT_RECD_OPEN_METER_CAP,
    E_D07_FMT_RECD_OPEN_BTN_BOX,
}E_D07_RULER_FORMAT;

/* ��Լ��д���� */
typedef enum
{
    E_D07_RDWR_READ_ONLY,        /* ֻ�� */
    E_D07_RDWR_WRITE_ONLY,        /* ֻд */
    E_D07_RDWR_READ_WRITE,        /* ��д */

}E_D07_RULER_RDWR;


/*���ݽṹ*/


typedef struct
{
    E_D07_PARA_PAYOFF   payoff;        // ������(�����ģ���ǰ����(1-12)������)
    E_D07_PARA_RATE      rate;         // ����(�����ģ�1~63)
    E_D07_PARA_HARM      harm;         // г����(�����ģ�1~21)
    E_D07_PARA_LAST      last;         // ��(n)�μ�¼(�����ģ�1-10)
    
}S_D07_RULER_PARA;
typedef struct
{
    E_D07_RULER_TYPE     type;            // ��Լ����
    E_D07_RULER_RDWR    rdwr;            // ��Լ���ݵĶ�д����
    E_D07_RULER_FORMAT     format;            // ��Լ���ݵĸ�ʽ
    F_D07_RULER_TRANS    func;            // ������ת������ָ��
    S_D07_RULER_PARA     para;            // ��Լ���͵Ķ�������
    int                 len;            // �������ֽڳ��� 
    char         name[NAME_LEN];        // ������Լ����������

}S_D07_RULER_INFO;



typedef struct
{
    UINT32 ruler_id;     /* ��Լ��ǩ�� C0 C1  ���� 0x40E3 */
    UINT8  ctrl_code;    /* ������ */
    UINT8  data_len;     /* �������ֽ��� ������Լ���������� */
    char   address[13];  /* ��ַ */
    char* data;          /* ���� */

}S_D07_PACK_FRAME;

/* �������� C ֡���ͷ��� */
typedef enum
{
    E_D07_CTRL_DIR_M2S, // ��վ����վ
    E_D07_CTRL_DIR_S2M, // ��վ����վ
    
}E_D07_CTRL_DIR;

/* ��վ�쳣��־ */
typedef enum
{
    E_D07_CTRL_SR_OK, // ��վ����Ӧ��
    E_D07_CTRL_SR_NO, // ��վ�쳣Ӧ��
    
}E_D07_CTRL_SR;

/* ���޺���֡��־ */
typedef enum
{
    E_D07_CTRL_FLW_NONE, //�޺���
    E_D07_CTRL_FLW_HAVE, //�к���
    
}E_D07_CTRL_FLW;
/*  ������������Ľ����־ */
typedef enum
{
    E_D07_UNPD_FLG_OK,          /* ������ȷ ���ݿ��� �������������Ĵ� */
    E_D07_UNPD_FLG_ERROR_OK,    /* ������ȷ ���ݿ��� ���������쳣�Ĵ� */
    E_D07_UNPD_FLG_NONE_DATA,   /* û�ж�Ӧ����Լ ���� */
    E_D07_UNPD_FLG_FUNC_NULL,   /* û�н������� */
    E_D07_UNPD_FLG_FUNC_ERROR,  /* �н������������������̳��� */
    E_D07_UNPD_FLG_NONE_STRUCT, /* û�н��������͵��û������ݽṹ */

}E_D07_UNPD_FLG;

/* ������C ������ */
typedef enum
{
    E_D07_CTRL_RESV                  = 0x00,// ����
    E_D07_CTRL_SYNC_TIME          = 0x08,// �㲥Уʱ
    E_D07_CTRL_READ_DATA          = 0x11,// ������
    E_D07_CTRL_READ_AFTERDATA      = 0x12,// ����������
    E_D07_CTRL_READ_ADDR          = 0x13,// ��ͨ�ŵ�ַ
    E_D07_CTRL_WRITE_DATA          = 0x14,// д����
    E_D07_CTRL_WRITE_ADDR          = 0x15,// дͨ�ŵ�ַ
    E_D07_CTRL_FREEZ_COMM          = 0x16,// ��������
    E_D07_CTRL_MODIFY_BAUD          = 0x17,// �޸�ͨ������
    E_D07_CTRL_MODIFY_PASSWORD      = 0x18,// �޸�����
    E_D07_CTRL_CLEAR_MAXDEMAND      = 0x19,// �����������
    E_D07_CTRL_CLEAR_METER          = 0x1A,// �������
    E_D07_CTRL_CLEAR_EVENT          = 0x1B,// �¼�����
    E_D07_CTRL_COMM                  = 0x1C // ��������
    
}E_D07_CTRL_FNC;
/* ������C �ṹ���� */
typedef struct
{
    E_D07_CTRL_DIR direct;    // ֡���ͷ��� 
    E_D07_CTRL_SR  reply;      // ��վӦ���쳣��־
    E_D07_CTRL_FLW follow;      // ���޺���֡
    E_D07_CTRL_FNC funcode;      // ������
    
}S_D07_CTRL_CODE;



typedef struct
{
    float fXX_XXXX;
    UINT8 YY;
    UINT8 MM;
    UINT8 DD;
    UINT8 hh;
    UINT8 mm;
        
}S_D07_XX_XXXX_YYMMDDhhmm;


typedef struct
{
    UINT32 a_times;
    UINT32 a_seconds;
    UINT32 b_times;
    UINT32 b_seconds;
    UINT32 c_times;
    UINT32 c_seconds;
}S_D07_XXXXXX_6;

typedef struct
{
    UINT8 MM;    // month
    UINT8 DD;    // day
    UINT8 hh;    // hour
    UINT8 mm;    // minute
}S_D07_MMDDhhmm;


typedef struct
{

    UINT32 ulTimes;   // XXXXXX
    UINT32 ulMinutes; // XXXXXX
}S_D07_XXXXXX_2;


typedef struct
{

    float fXX_XXXXX[8];
}S_D07_XX_XXXX_8;

typedef struct
{
    UINT8 hh;
    UINT8 mm;
    UINT8 ss;    
}S_D07_hhmmss;

typedef struct
{

    UINT8 hh;
    UINT8 mm;
    UINT8 NN;

}S_D07_hhmmNN;

typedef struct
{
    S_D07_hhmmNN hhmmNN[14];
}S_D07_hhmmNN_14;




typedef struct
{

    UINT8 YY;   // year
    UINT8 MM;    // month
    UINT8 DD;    // day
    UINT8 hh;    // hour
    UINT8 mm;    // minute
    UINT8 ss;    // second

}S_D07_YYMMDDhhmmss;

typedef struct
{

    S_D07_YYMMDDhhmmss sBegin;
    S_D07_YYMMDDhhmmss sEnd;
}S_D07_YYMMDDhhmmss_2;

typedef struct
{

    UINT8 YY;   // year
    UINT8 MM;    // month
    UINT8 DD;    // day
    UINT8 hh;    // hour
    UINT8 mm;    // minute

}S_D07_YYMMDDhhmm;

typedef struct
{
    S_D07_YYMMDDhhmmss            sBgnTime;      // ��ʼʱ��         6 * 1
    S_D07_YYMMDDhhmmss            sEndTime;      // ����ʱ��         6 * 1 
    S_D07_XX_XXXX_YYMMDDhhmm   sDemand;        // �������������ʱ�� 
}S_D07_YYMMDDhhmmss_2_XX_XXXX_YYMMDDhhmm;

typedef struct
{
    S_D07_YYMMDDhhmmss            sBgnTime;      // ��ʼʱ��         6 * 1
    S_D07_YYMMDDhhmmss            sEndTime;      // ����ʱ��         6 * 1 
    float fXXX_XXX;
}S_D07_YYMMDDhhmmss_XX_XXXX_YYMMDDhhmmss;





typedef struct
{
    double dForthHavePowerIcr;     // �¼������ڼ�ĳ�� �����й���������     XXXXXX.XX
    double dBackHavePowerIcr;   // �¼������ڼ�ĳ�� �����й���������      XXXXXX.XX
    double dCombNone1PowerIcr;    // �¼������ڼ�ĳ�� ����޹�1��������     XXXXXX.XX
    double dCombNone2PowerIcr;    // �¼������ڼ�ĳ�� ����޹�2��������     XXXXXX.XX
    
}S_D07_EventRecordVoltPhase;

typedef struct
{
    float fVolt;                // �¼������ڼ�ĳ�� ��ѹ ���� XXX.X
    float fElec;                // �¼������ڼ�ĳ��    ����      XXX.XXX
    float fHavePowerRate;        // �¼������ڼ�ĳ�� �й�����  XX.XXXX
    float fNonePowerRate;        // �¼������ڼ�ĳ�� �޹�����  XX.XXXX    
    float fPowerRateFactor;        // �¼������ڼ�ĳ�� ��������  X.XXX
}S_D07_EventRecordFactor;


typedef struct
{
    double    dAtimeTotal;        // �¼������ڼ� �ܰ�ʱ��    XXXXXX.XX
    double    dAtimePhaseA;        // �¼������ڼ� A�లʱ��   XXXXXX.XX
    double    dAtimePhaseB;        // �¼������ڼ� B�లʱ��   XXXXXX.XX
    double    dAtimePhaseC;        // �¼������ڼ� C�లʱ��   XXXXXX.XX
}S_D07_EventRecordAtime; // ��ʱ��

typedef struct
{
    S_D07_YYMMDDhhmmss            sBgnTime;      // ��ʼʱ��         6 * 1
    S_D07_YYMMDDhhmmss            sEndTime;      // ����ʱ��         6 * 1
    S_D07_EventRecordVoltPhase sPowerTotal; // �ܵ�������       4 * 8
    S_D07_EventRecordVoltPhase sPowerA;         // A���������         4 * 8
    S_D07_EventRecordFactor       sFactorA;    // A������            5 * 4
    S_D07_EventRecordVoltPhase sPowerB;         // B���������        4 * 8 
    S_D07_EventRecordFactor       sFactorB;    // B������             5 * 4
    S_D07_EventRecordVoltPhase sPowerC;     // C���������         4 * 8
    S_D07_EventRecordFactor    sFactorC;    // C������            5 * 4
    S_D07_EventRecordAtime     sAtime;      // ��ʱ��              4 * 8
    
}S_D07_LESS_LOSS_VOLT;// ʧѹǷѹ��ѹ�������¼�������¼����  35 * 4 + 12 = 152�ֽ�



typedef struct
{
    S_D07_YYMMDDhhmmss            sBgnTime;       // ��ʼʱ��    6 * 1    
    S_D07_YYMMDDhhmmss            sEndTime;       // ����ʱ��    6 * 1
    S_D07_EventRecordVoltPhase sPowerTotal;    // �ܵ�������  4 * 8
    S_D07_EventRecordVoltPhase sPowerA;           // A��������� 4 * 8
    S_D07_EventRecordVoltPhase sPowerB;           // B��������� 4 * 8
    S_D07_EventRecordVoltPhase sPowerC;        // C��������� 4 * 8
    
}S_D07_EventRevPhase; // ��ѹ ��������    ��(140)�ֽ�

typedef struct
{
    S_D07_YYMMDDhhmmss            sBgnTime;              // ��ʼʱ��
    S_D07_YYMMDDhhmmss            sEndTime;              // ����ʱ��
    float                        fMaxUnbalanceFator;     // ���ƽ����
    S_D07_EventRecordVoltPhase sPowerTotal;          // �ܵ�������  4 * 8
    S_D07_EventRecordVoltPhase sPowerA;                   // A��������� 4 * 8
    S_D07_EventRecordVoltPhase sPowerB;                   // B��������� 4 * 8
    S_D07_EventRecordVoltPhase sPowerC;               // C��������� 4 * 8
    
}S_D07_EventUnBalance; //��ƽ���¼���¼


typedef struct
{
    S_D07_YYMMDDhhmmss            sBgnTime;      // ��ʼʱ��         6 * 1
    S_D07_YYMMDDhhmmss            sEndTime;      // ����ʱ��         6 * 1
    S_D07_EventRecordVoltPhase sPowerTotal; // �ܵ�������       4 * 8
    S_D07_EventRecordVoltPhase sPowerA;         // A���������         4 * 8
    S_D07_EventRecordFactor       sFactorA;    // A������            5 * 4
    S_D07_EventRecordVoltPhase sPowerB;         // B���������        4 * 8 
    S_D07_EventRecordFactor       sFactorB;    // B������             5 * 4
    S_D07_EventRecordVoltPhase sPowerC;     // C���������         4 * 8
    S_D07_EventRecordFactor    sFactorC;    // C������            5 * 4
    //S_D07_EventRecordAtime     sAtime;      // ��ʱ��              4 * 8
    
}S_D07_LESS_MORE_LOSS_ELET;// ʧ���������������¼�������¼����  35 * 4 + 12 = 152�ֽ�


typedef struct
{
    UINT32 ulMonitorVoltMinutes;  // ���ʱ�� ��λ��
    float fVoltPassPercent;      // ��ѹ�ϸ���
    float fVoltOverLimitPercent; // ��ѹ������
    UINT32 ulVoltOverUpperLimitMinutes;  // ��ѹ������ʱ��
    UINT32 ulVoltOverLowerLimitMinutes;  // ��ѹ������ʱ��
    float fVoltValueMax;                // ��ѹ���ֵ
    float fVoltValueMin;                // ��ѹ��Сֵ
    S_D07_MMDDhhmm sTimeVoltValueMax;       // ��ߵ�ѹ����ʱ��      
    S_D07_MMDDhhmm sTimeVoltValueMin;         // ��͵�ѹ����ʱ��
}S_D07_EventPassPercent; // �ϸ����¼�����



typedef struct
{
    S_D07_YYMMDDhhmmss sProgTime;         // �¼�����ʱ��
    UINT8              programer[4];      // ����߱�ʶ 4�ֽ�
    UINT32               ulRulerID[10];     // ��̵�ǰʮ�����ݱ�ʶ�룬���� 0xFFFFFFFF ������0xFFFFFFFF����
}S_D07_EventMeterProgram; // ����¼���¼ 


typedef struct
{    
    double dForthHavePower; // XXXXXX.XX ���� �й��ܵ���
    double dBackHavePower;  // XXXXXX.XX ���� �й��ܵ���
    double dNonePowerQuad1; // XXXXXX.XX �¼�����ʱ�� 1 �����޹�����
    double dNonePowerQuad2; // XXXXXX.XX �¼�����ʱ�� 2 �����޹�����
    double dNonePowerQuad3; // XXXXXX.XX �¼�����ʱ�� 3 �����޹�����
    double dNonePowerQuad4; // XXXXXX.XX �¼�����ʱ�� 4 �����޹�����
}S_D07_EventPower;

typedef struct
{

    S_D07_XX_XXXX_YYMMDDhhmm sFortHaveDemand;   // �����й��������������ʱ��     XX.XXXX YYMMDDhhmm
    S_D07_XX_XXXX_YYMMDDhhmm sBackHaveDemand;   // �����й��������������ʱ��    XX.XXXX    YYMMDDhhmm
    S_D07_XX_XXXX_YYMMDDhhmm sNoneDemandQuad1;  // �����й��������������ʱ��    XX.XXXX    YYMMDDhhmm
    S_D07_XX_XXXX_YYMMDDhhmm sNoneDemandQuad2;  // �����й��������������ʱ��    XX.XXXX    YYMMDDhhmm
    S_D07_XX_XXXX_YYMMDDhhmm sNoneDemandQuad3;  // �����й��������������ʱ��    XX.XXXX    YYMMDDhhmm
    S_D07_XX_XXXX_YYMMDDhhmm sNoneDemandQuad4;  // �����й��������������ʱ��    XX.XXXX    YYMMDDhhmm

}S_D07_EventDemand; //������������¼�ĳ���������������ʱ��

typedef struct
{

    S_D07_YYMMDDhhmmss sOccurTime;       // �¼�����ʱ��
    UINT8              controller[4];      // �����߱�ʶ 4�ֽ�

    S_D07_EventDemand    sTotal;             // �������ǰ �� ��������
    S_D07_EventDemand    sPhaseA;         // �������ǰ A����������
    S_D07_EventDemand    sPhaseB;         // �������ǰ B����������
    S_D07_EventDemand    sPhaseC;         // �������ǰ C����������
}S_D07_EventDemandClear;

typedef struct
{
    S_D07_YYMMDDhhmmss sOccurTime;       // �¼�����ʱ��
    UINT8              controller[4];      // �����߱�ʶ 4�ֽ�

    S_D07_EventPower    sTotal;             // �������ǰ �� ��������
    S_D07_EventPower    sPhaseA;         // �������ǰ A���������
    S_D07_EventPower    sPhaseB;         // �������ǰ B���������
    S_D07_EventPower    sPhaseC;         // �������ǰ C���������

}S_D07_EventMeterClear; // �����0�¼���¼


typedef struct
{
    S_D07_YYMMDDhhmmss sOccurTime;       // �¼�����ʱ��
    UINT8              controller[4];      // �����߱�ʶ 4�ֽ�
    UINT32               ulEventID;         // �����¼����
}S_D07_EventClear;         // �¼������¼


typedef struct
{
    UINT8              controller[4]; // �����߱�ʶ 4�ֽ�
    S_D07_YYMMDDhhmmss sBefTime;    // Уʱǰʱ��     
    S_D07_YYMMDDhhmmss sAftTime;     // Уʱ��ʱ��
    
}S_D07_EventTiming;        // Уʱ�¼���¼

typedef struct
{
    UINT8 MM;
    UINT8 DD;
    UINT8 NN;    
}S_D07_MMDDNN;

typedef struct
{
    S_D07_YYMMDDhhmmss sOccurTime;       // �¼�����ʱ��
    UINT8              controller[4];      // �����߱�ʶ 4�ֽ�
    S_D07_MMDDNN       sZoneSet1[14];    // ʱ�������ǰ��һ�׵�(1~14)ʱ��������
    S_D07_MMDDNN       sZoneSet2[14];    // ʱ�������ǰ�ڶ��׵�(1~14)ʱ��������
}S_D07_EventZone; // ʱ��������¼���¼

typedef struct
{
    S_D07_YYMMDDhhmmss sOccurTime;       // �¼�����ʱ��
    UINT8              controller[4];      // �����߱�ʶ 4�ֽ�
    UINT8               ucTableNum;         // �����Ǳ��ǰ���õ��նα���
}S_D07_EventWeekDay;   // �����ձ�̼�¼


typedef struct
{
    UINT8 DD;
    UINT8 hh;
}S_D07_DDhh;

typedef struct
{
    UINT8 YY;
    UINT8 MM;
    UINT8 DD;
    UINT8 NN;
    
}S_D07_YYMMDDNN;

typedef struct
{
    UINT8 YY;
    UINT8 MM;
    UINT8 DD;
    UINT8 hh;
    UINT8 mm;
    UINT8 NN;    
}S_D07_YYMMDDhhmmNN;

typedef struct
{

    S_D07_YYMMDDhhmmss sOccurTime;       // �¼�����ʱ��
    UINT8              controller[4];      // �����߱�ʶ 4�ֽ�

    S_D07_YYMMDDNN  sHoliday[12];        
    // �й������ڼ���11�� Ԫ��һ�졣�������졣����һ�졣��һһ�졣����һ�졣����һ�졣�������졣
    // ���ǰ��N�ڼ������� ��׼Э��֧��254���ڼ���
    // 
    
}S_D07_EventHoliday; // �ڼ��ձ���¼���¼


typedef struct
{

    S_D07_YYMMDDhhmmss sOccurTime;       // �¼�����ʱ��
    UINT8              controller[4];      // �����߱�ʶ 4�ֽ�
    UINT8               ucWord;             // ����Ϸ�ʽ���ǰ���й���Ϸ�ʽ������
}S_D07_EventCombPower; // �й�/�޹���Ϸ�ʽ��̼�¼

typedef struct
{
    S_D07_YYMMDDhhmmss sOccurTime;       // �¼�����ʱ��
    UINT8              controller[4];      // �����߱�ʶ 4�ֽ�
    S_D07_DDhh         sDay1;
    S_D07_DDhh         sDay2;
    S_D07_DDhh         sDay3;
}S_D07_EventPayoff;

typedef struct
{

    S_D07_YYMMDDhhmmss sBgnTime;       // ��ʼʱ��
    S_D07_YYMMDDhhmmss sEndTime;       // ����ʱ�� 
    S_D07_EventPower sPowerBeforOpen;  // ����ǰ��������
    S_D07_EventPower sPowerAfterOpen;  // ���Ǻ��������

}S_D07_EventOpenCap;        // �����Ǽ�¼

typedef struct
{
    UINT8 YY;
    UINT8 MM;
    UINT8 DD;
    UINT8 WW;
}S_D07_YYMMDDWW;

typedef struct
{
    S_D07_MMDDNN MMDDNN[14];
    
}S_D07_MMDDNN_14;




typedef struct
{
    BOOL bRateErr;  // ��������
    BOOL bDayErr;   // ��ʱ������
    BOOL bYearErr;  // ��ʱ������
    BOOL bCommErr;  // ͨѶ���ʲ��ܸ���
    BOOL bPwdErr;   // �������δ��Ȩ
    BOOL bNoneReq;  // û����������
    BOOL bOtherErr; // ��������
}S_D07_ERR;


/* �û��ӿڲ����ݽṹ */
typedef union
{

    float   fPower; 
    S_D07_YYMMDDWW sYYMMDDWW;
    S_D07_ERR      sError;
}U_D07_DATA_UNPACK;

/* ����֡��Ϣ���ݽṹ */
typedef struct
{
    
    UINT8                  ctrl_c;           /* ������ �ֽ��� */
    UINT8                  lead_num;         /* ǰ���ַ� 0xFE�ĸ��� */
    UINT32                 ruler_id;         /* ��ԼID */
   
    unsigned short           data_len;         /* ������ */
    unsigned short         frame_len;         /* ����֡��*/
      
    E_D07_RULER_TYPE       type;             /* ��Լ���� */
    E_D07_RULER_FORMAT     format;           /* ֡�����ݸ�ʽ */
    E_D07_UNPD_FLG         flag;             /* �������ݵ��û������ݵı�־��˵������״̬ ����data_unpack �Ƿ���� */
    S_D07_CTRL_CODE        ctrl_s;           /* ������ṹ */
    S_D07_RULER_PARA       para;             /* ��Լ���͵Ķ������� */ 
    UINT8                  data_pack[D07_DATA_MAX_NR];   /* ������ ��������ԼID�Ĳ��� û����ת�� */
    UINT8                  address[D07_ADDR_LEN+1];     //12λ��ַ������
    U_D07_DATA_UNPACK      data_unpack;               /* ת��Ϊ�û�������� */ 
    //UINT8   *pDataUser;
}S_D07_UNPACK;


#ifdef __cplusplus

extern "C"{

#endif

/* ���ܺ��� */

/* ���ݹ�ԼID ��ȡ��Ӧ��Լ������������Ϣ */
int get_d07_ruler_info(UINT32 rulerID, S_D07_RULER_INFO *outRulerInfo);
int get_d07_ruler_id(E_D07_RULER_TYPE type,
                     S_D07_RULER_PARA para,
                     UINT32 *poutRulerID);
/* ͨ����ַ ��ԼID ���������ݼ����� ��֡ */
int pack_d07_frame_by_data(S_D07_PACK_FRAME *inPara, char *outBuffer, int *outLength); 

//���� dlt645 07֡ 
int unpack_d07_frame(void *inpBuffer, int inBufferLength, S_D07_UNPACK *outpFrame);


/* ��һ���������ҳ���һ����Чdlt645 2007֡��λ�ü����� */
int get_d07_first_valid_frame(const UINT8 *pBuf,         // Ҫ������buf
                              UINT16 usLenBuf,           // Ҫ������buf�ֽ���
                              UINT8  **ppFirstPos,       // ���֡buffer
                              UINT16 *pusLenFrame);      // ���Frame�ֽ���
/* �ж�һ��֡�Ƿ�Ϊ��ȷ�� */
int is_right_d07_frame(void *inpBuffer, int inBufferLength);
/* */
void d07_str2bcd(const char *pstr, UINT8 *pbcd, int len);
void d07_bcd2str(const char* inBCD, char *outStr, int len);
double d07_bcd_to_double(UINT8* pBcd, int len,int LeftDigit);
int d07_remove_dot(int len, char*inArray, char *outArray); // ȥ���ַ�����ʽ��ȥ��С����

int d07_add_dot(int len, char*inArray, char *outArray,  int dotpos); // ����С����

/* ���������� */
eD07Err trans_d07ctrl_struct2char(UINT8 *outChar, S_D07_CTRL_CODE *inStruct); //���ṹ��װ���ֽ�
eD07Err trans_d07ctrl_char2struct(UINT8 inChar,  S_D07_CTRL_CODE *outStruct); //���ֽڷ�װ�ɽṹ




/* ���ݽ������� */
/*XX*/
eD07Err trans_d07_data_XX_2(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XX_3(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XX_4(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XX_6(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XX_8(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XX_10(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XX_16(E_D07_TRANS_FLG flag, char *user, char *frame);

eD07Err trans_d07_data_XXXXXX_2(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XXXXXX_6(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XXXX(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XXXXXX(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XXX_X(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XXX_XXX(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XX_XXXX(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XXXXXXXX(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XXXXXX_XX(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XX_XXXX_YYMMDDhhmm(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XX_XXXX_8(E_D07_TRANS_FLG flag, char *user, char *frame);
/*NN*/
eD07Err trans_d07_data_NN(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_NNNN(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_NN_4(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_NN_6(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_NN_32(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_N_NNN(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_NN_NNNN(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_NNN_N(E_D07_TRANS_FLG flag, char *user, char *frame);


/*X.X*/
eD07Err trans_d07_data_X_XXX(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_XX_XX(E_D07_TRANS_FLG flag, char *user, char *frame);

/*YYMMDDWWhhmmss*/
eD07Err trans_d07_data_hhmmss(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_MMDDhhmm(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_DDhh(E_D07_TRANS_FLG flag, char *user, char *frame);

eD07Err trans_d07_data_YYMMDDWW(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_YYMMDDNN(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_YYMMDDhhmm(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_YYMMDDhhmmNN(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_YYMMDDhhmmss(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_YYMMDDhhmmss_2(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_YYMMDDhhmmss_2_XX_XXXX_YYMMDDhhmm(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_YYMMDDhhmmss_XXX_XXX_YYMMDDhhmmss(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_MMDDNN_14(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_hhmmNN_14(E_D07_TRANS_FLG flag, char *user, char *frame);
/* ������� */
eD07Err trans_d07_data_recd_loss_less_volt(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_anti_phase(E_D07_TRANS_FLG flag, char *user, char *frame);    // ���������ݸ�ʽ
eD07Err trans_d07_data_recd_un_balance(E_D07_TRANS_FLG flag, char *user, char *frame);    // ��ƽ�����ݸ�ʽ    
eD07Err trans_d07_data_recd_less_more_loss_elec(E_D07_TRANS_FLG flag, char *user, char *frame);        // less more loss ʧ�����������������ݼ�¼��ʽ
eD07Err trans_d07_data_recd_volt_pass_percent(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_meter_prog(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_meter_clear(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_demand_clear(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_event_clear(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_adjust_time(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_part_prog(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_zone_prog(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_weekday_prog(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_holiday_prog(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_power_prog(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_payoff_prog(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_open_meter_cap(E_D07_TRANS_FLG flag, char *user, char *frame);
eD07Err trans_d07_data_recd_open_btn_box(E_D07_TRANS_FLG flag, char *user, char *frame);

//����״̬��
eD07Err trans_d07_data_err(E_D07_TRANS_FLG flag, char *user, char *frame);

#ifdef __cplusplus

};

#endif


#pragma pack(pop) 
#endif //__DLT645_2007_RULERS_H__

