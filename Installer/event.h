/**
* Copyright (C) 2014-2050 SongJia
* All rights reserved.
*
* @file       event.h
* @brief	  �Զ�����Ϣ
* @version    v1.0
* @author     SongJia
* @date       2015-04-23
*
* Describe     ������NSIS�ű������ò�����Ϣ���ƣ�����ֱ�ӵ��ó��򷽷����������������ִ�С�
*/


#ifndef ___EVENT__H___
#define ___EVENT__H___
//////��һ��ͼ Welcome ��Ϣ/////
//��ѡ��״̬���֪ͨ
//����������Э����ͼ��Ϣ
#define WM_SJONELINKAGREEMENT (WM_USER+302)

//////�ڶ���ͼ agreement ��Ϣ/////
#define WM_SJTWOSURE (WM_USER+310)

//////������ͼ choose ��Ϣ/////
//���밲װ������Ϣ
#define WM_SJTHREEINSTALL WM_SJONEINSTALL
//���¿��ô��̿ռ�
#define WM_SJTHREEUPDATEFREESPACE (WM_USER+321)
//����������̿ռ�
#define WM_SJTHREEUPDATEREQUIREDSPACE (WM_USER+322)

//ֹͣ��Ϣѭ����ʹ��װ�������ִ�С�
#define WM_SJMSGLOOPSTOP (WM_USER+323)

//////������ͼ installing ��Ϣ/////

//////������ͼ finish ��Ϣ/////


/////ж��///////


#endif