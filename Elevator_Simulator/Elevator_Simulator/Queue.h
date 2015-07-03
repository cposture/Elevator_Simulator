/***************************************************************************************
*	File Name				: Queue.h
*	CopyRight				:
*	ModuleName			    :
*
*	CPU						:
*	RTOS					:
*
*	Create Data				:	2015/06/17
*	Author/Corportation		:	�¼���
*
*	Abstract Description	:	����
*
*--------------------------------Revision History--------------------------------------
*	No	version		Data			Revised By			Item			Description
*	1   v1.0        2015/06/17      �¼���              All             Create the file
*
***************************************************************************************/


/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef _QUEUE_H
#define _QUEUE_H

/**************************************************************
*	Debug switch Section
**************************************************************/

/**************************************************************
*	Include File Section
**************************************************************/


/**************************************************************
*	Macro Define Section
**************************************************************/

/**************************************************************
*	Struct Define Section
**************************************************************/
typedef enum Status{
    TRUE,FALSE
}Status;

typedef struct Passenger{
    int key;
}Passenger,ElemType;

typedef struct QueueNode{
    ElemType    data;
    struct QueueNode *next;
}QueueNode,*QueueNodePtr;

typedef struct Queue{
    QueueNodePtr    front;
    QueueNodePtr    rear;
}Queue,QueuePtr;

/**************************************************************
*	Prototype Declare Section
**************************************************************/
/**
*	Name...........:    Status initQueue(QueuePtr Q);
*	Description....:	����һ���ն���
*	Param..........:	Q:ָ����е�ָ��
*	Return.........:    TRUE:�����ɹ�
                        FALSE:����ʧ�ܣ���ΪQ��Ϊ��
*	Precondition...:    ʹ��ǰҪ�ȶ���һ��QueuePtr���ͱ����������ַ��Ϊʵ�Σ����б�����丳ֵΪNULL
*	Postcondition..:    ��������ɹ���Qָ��һ���ն��У��������ʧ�ܣ�Qָ���ֵ���ı�
**/
Status initQueue(QueuePtr Q);

/**
*	Name...........:    Status destroyQueue(QueuePtr Q);
*	Description....:	����һ���ն���
*	Param..........:	Q:ָ����е�ָ��
*	Return.........:    TRUE:�����ɹ�
FALSE:����ʧ�ܣ���ΪQ��Ϊ��
*	Precondition...:    ʹ��ǰҪ�ȶ���һ��QueuePtr���ͱ����������ַ��Ϊʵ�Σ����б�����丳ֵΪNULL
*	Postcondition..:    ��������ɹ���Qָ��һ���ն��У��������ʧ�ܣ�Qָ���ֵ���ı�
**/
Status destroyQueue(QueuePtr Q);

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif