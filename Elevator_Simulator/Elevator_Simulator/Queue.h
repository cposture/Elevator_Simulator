/***************************************************************************************
*	File Name				: Queue.h
*	CopyRight				:
*	ModuleName			    :
*
*	CPU						:
*	RTOS					:
*
*	Create Data				:	2015/06/17
*	Author/Corportation		:	陈家启
*
*	Abstract Description	:	队列
*
*--------------------------------Revision History--------------------------------------
*	No	version		Data			Revised By			Item			Description
*	1   v1.0        2015/06/17      陈家启              All             Create the file
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
*	Description....:	建立一个空队列
*	Param..........:	Q:指向队列的指针
*	Return.........:    TRUE:建立成功
                        FALSE:建立失败，因为Q不为空
*	Precondition...:    使用前要先定义一个QueuePtr类型变量，将其地址作为实参，其中必须对其赋值为NULL
*	Postcondition..:    如果建立成功，Q指向一个空队列；如果建立失败，Q指向的值不改变
**/
Status initQueue(QueuePtr Q);

/**
*	Name...........:    Status destroyQueue(QueuePtr Q);
*	Description....:	建立一个空队列
*	Param..........:	Q:指向队列的指针
*	Return.........:    TRUE:建立成功
FALSE:建立失败，因为Q不为空
*	Precondition...:    使用前要先定义一个QueuePtr类型变量，将其地址作为实参，其中必须对其赋值为NULL
*	Postcondition..:    如果建立成功，Q指向一个空队列；如果建立失败，Q指向的值不改变
**/
Status destroyQueue(QueuePtr Q);

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif