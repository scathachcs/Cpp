
#include <fstream>
#include <iostream>
using namespace std;
struct ThreadInfo
{
	int tid;            //线程ID
	char direction;     //行人行走方向 N or S
	double delay;      //线程延迟
	double persist;    //行人行走持续时间
};
int s_scount=0;// 南部桥往南行走的人数
int s_ncount=0;// 南部桥往北行走的人数
int n_scount=0;// 北部桥往南行走的人数
int n_ncount=0;// 北部桥往北行走的人数

#ifdef _WIN64
#include <Windows.h>
#define sleep(n) Sleep(n*1000)
HANDLE s_smutex; //局部临界资源
HANDLE s_nmutex; //局部临界资源
HANDLE n_smutex; //局部临界资源
HANDLE n_nmutex; //局部临界资源
CRITICAL_SECTION Smutex; //全局临界资源
CRITICAL_SECTION Nmutex; //全局临界资源
HANDLE h_thread[20]; //全局句柄变量

void Initial(){
	s_smutex = CreateMutexW(NULL, false, LPCWSTR("mutex_for_s_smutex"));
    s_nmutex = CreateMutexW(NULL, false, LPCWSTR("mutex_for_s_nmutex"));
    n_smutex = CreateMutexW(NULL, false, LPCWSTR("mutex_for_n_smutex"));
    n_nmutex = CreateMutexW(NULL, false, LPCWSTR("mutex_for_n_nmutex"));
    //初始化临界区
    InitializeCriticalSection(&Smutex); 
    InitializeCriticalSection(&Nmutex);  
}

void StoNWallkerThread(void * p)
{
	DWORD m_delay;
	DWORD m_persist;
	int m_id;
	//从参数中获取信息
	m_delay = ((ThreadInfo *)(p))->delay;
	m_persist = ((ThreadInfo *)(p))->persist;
	m_id = ((ThreadInfo*)(p))->tid;
	sleep(m_delay); //延迟等待
	printf("StoN_Wallker thread %d walk South Bridge require ! \n", m_id);
	//等待互斥信号量，保证对s_ncount的互斥访问
	DWORD wait_for_mutex = WaitForSingleObject(s_nmutex, -1); 
	if (s_ncount == 0)
	{
		 EnterCriticalSection(&Smutex); //DWORD waits = WaitForSingleObject(RW_mutex, -1);
	}
	s_ncount++;
	ReleaseMutex(s_nmutex);
	// 从南部江安桥往北走
	printf("StoN_Wallker thread %d begins to walk in South Bridge ! \n", m_id);
	sleep(m_persist);
	printf("StoN_Wallker thread %d finished walk in South Bridge ! \n", m_id);
	//释放互斥信号量
	wait_for_mutex = WaitForSingleObject(s_nmutex, -1);
	s_ncount--;
	if (s_ncount == 0)
	{
		LeaveCriticalSection(&Smutex);
	}
	ReleaseMutex(s_nmutex);

        // 从中部江安桥往北走
	printf("StoN_Wallker thread %d begins to walk in Middle Bridge ! \n", m_id);
	sleep(m_persist);
	printf("StoN_Wallker thread %d finished walk in Middle Bridge ! \n", m_id);

        printf("StoN_Wallker thread %d walk North Bridge require ! \n", m_id);
	//等待互斥信号量，保证对s_ncount的互斥访问
	wait_for_mutex = WaitForSingleObject(n_nmutex, -1); 
	if (n_ncount == 0)
	{
		 EnterCriticalSection(&Nmutex); //DWORD waits = WaitForSingleObject(RW_mutex, -1);
	}
	n_ncount++;
	ReleaseMutex(n_nmutex);
	// 从北部江安桥往北走
	printf("StoN_Wallker thread %d begins to walk in North Bridge ! \n", m_id);
	sleep(m_persist);
	printf("StoN_Wallker thread %d finished walk in North Bridge ! \n", m_id);
	//释放互斥信号量
	wait_for_mutex = WaitForSingleObject(n_nmutex, -1);
	n_ncount--;
	if (n_ncount == 0)
	{
		LeaveCriticalSection(&Nmutex);
	}
	ReleaseMutex(n_nmutex);

}

void NtoSWallkerThread(void * p)
{
	DWORD m_delay;
	DWORD m_persist;
	int m_id;
	//从参数中获取信息
	m_delay = ((ThreadInfo *)(p))->delay;
	m_persist = ((ThreadInfo *)(p))->persist;
	m_id = ((ThreadInfo*)(p))->tid;
	sleep(m_delay); //延迟等待
	printf("NtoS_Wallker thread %d walk North Bridge require ! \n", m_id);
	//等待互斥信号量，保证对n_scount的互斥访问
	DWORD wait_for_mutex = WaitForSingleObject(n_smutex, -1); 
	if (n_scount == 0)
	{
		 EnterCriticalSection(&Nmutex); //DWORD waits = WaitForSingleObject(RW_mutex, -1);
	}
	n_scount++;
	ReleaseMutex(n_smutex);
	// 从北部江安桥往南走
	printf("NtoS_Wallker thread %d begins to walk in North Bridge ! \n", m_id);
	sleep(m_persist);
	printf("NtoS_Wallker thread %d finished walk in North Bridge ! \n", m_id);
	//释放互斥信号量
	wait_for_mutex = WaitForSingleObject(n_smutex, -1);
	n_scount--;
	if (n_scount == 0)
	{
		LeaveCriticalSection(&Nmutex);
	}
	ReleaseMutex(n_smutex);

        // 从中部江安桥往南走
	printf("NtoS_Wallker thread %d begins to walk in Middle Bridge ! \n", m_id);
	sleep(m_persist);
	printf("NtoS_Wallker thread %d finished walk in Middle Bridge ! \n", m_id);

        printf("NtoS_Wallker thread %d walk south Bridge require ! \n", m_id);
	//等待互斥信号量，保证对s_ncount的互斥访问
	wait_for_mutex = WaitForSingleObject(s_smutex, -1); 
	if (s_scount == 0)
	{
		 EnterCriticalSection(&Smutex); //DWORD waits = WaitForSingleObject(RW_mutex, -1);
	}
	s_scount++;
	ReleaseMutex(s_smutex);
	// 从南部江安桥往南走
	printf("NtoS_Wallker thread %d begins to walk in South Bridge ! \n", m_id);
	sleep(m_persist);
	printf("NtoS_Wallker thread %d finished walk in South Bridge ! \n", m_id);
	//释放互斥信号量
	wait_for_mutex = WaitForSingleObject(s_smutex, -1);
	s_scount--;
	if (s_scount == 0)
	{
		LeaveCriticalSection(&Smutex);
	}
	ReleaseMutex(s_smutex);
}


void Create(DWORD& n_thread,ThreadInfo *thread_info,DWORD& thread_ID){
	for (int i = 0; i < n_thread; i++)
	{
		if (thread_info[i].direction == 'N' || thread_info[i].direction == 'n') 
		{
			h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(StoNWallkerThread), &thread_info[i], 0, &thread_ID);
		}
		else
		{
			h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(NtoSWallkerThread), &thread_info[i], 0, &thread_ID);
		}
	}
	//等待所有线程结束
	DWORD wait_for_all = WaitForMultipleObjects(n_thread, h_thread, true, -1);
}

#endif 

#ifdef __linux
#include<pthread.h>
#include <unistd.h>
typedef unsigned int DWORD;
pthread_mutex_t s_smutex; //局部临界资源
pthread_mutex_t s_nmutex; //局部临界资源
pthread_mutex_t n_smutex; //局部临界资源
pthread_mutex_t n_nmutex; //局部临界资源
pthread_mutex_t Smutex; //全局临界资源
pthread_mutex_t Nmutex; //全局临界资源
pthread_t h_thread[20]; 

void Initial(){
	pthread_mutex_init(&s_smutex,NULL);
    pthread_mutex_init(&s_nmutex,NULL);
	pthread_mutex_init(&n_smutex,NULL);
	pthread_mutex_init(&n_nmutex,NULL);
    //初始化临界区
    pthread_mutex_init(&Smutex,NULL); 
    pthread_mutex_init(&Nmutex,NULL);  
}

void *StoNWallkerThread(void * p)
{
	DWORD m_delay;
	DWORD m_persist;
	int m_id;
	//从参数中获取信息
	m_delay = ((ThreadInfo *)(p))->delay;
	m_persist = ((ThreadInfo *)(p))->persist;
	m_id = ((ThreadInfo*)(p))->tid;
	sleep(m_delay); //延迟等待
	printf("StoN_Wallker thread %d walk South Bridge require ! \n", m_id);
	//等待互斥信号量，保证对s_ncount的互斥访问
	pthread_mutex_lock(&s_nmutex); 
	if (s_ncount == 0)
	{
		pthread_mutex_lock(&Smutex); //DWORD waits = WaitForSingleObject(RW_mutex, -1);
	}
	s_ncount++;
	pthread_mutex_unlock(&s_nmutex);
	// 从南部江安桥往北走
	printf("StoN_Wallker thread %d begins to walk in South Bridge ! \n", m_id);
	sleep(m_persist);
	printf("StoN_Wallker thread %d finished walk in South Bridge ! \n", m_id);
	//释放互斥信号量
	pthread_mutex_lock(&s_nmutex);
	s_ncount--;
	if (s_ncount == 0)
	{
		pthread_mutex_unlock(&Smutex);
	}
	pthread_mutex_unlock(&s_nmutex);

        // 从中部江安桥往北走
	printf("StoN_Wallker thread %d begins to walk in Middle Bridge ! \n", m_id);
	sleep(m_persist);
	printf("StoN_Wallker thread %d finished walk in Middle Bridge ! \n", m_id);

    printf("StoN_Wallker thread %d walk North Bridge require ! \n", m_id);
	//等待互斥信号量，保证对s_ncount的互斥访问
	pthread_mutex_lock(&n_nmutex); 
	if (n_ncount == 0)
	{
		 pthread_mutex_lock(&Nmutex); //DWORD waits = WaitForSingleObject(RW_mutex, -1);
	}
	n_ncount++;
	pthread_mutex_unlock(&n_nmutex);
	// 从北部江安桥往北走
	printf("StoN_Wallker thread %d begins to walk in North Bridge ! \n", m_id);
	sleep(m_persist);
	printf("StoN_Wallker thread %d finished walk in North Bridge ! \n", m_id);
	//释放互斥信号量
	pthread_mutex_lock(&n_nmutex);
	n_ncount--;
	if (n_ncount == 0)
	{
		pthread_mutex_unlock(&Nmutex);
	}
	pthread_mutex_unlock(&n_nmutex);

}

void *NtoSWallkerThread(void * p)
{
	DWORD m_delay;
	DWORD m_persist;
	int m_id;
	//从参数中获取信息
	m_delay = ((ThreadInfo *)(p))->delay;
	m_persist = ((ThreadInfo *)(p))->persist;
	m_id = ((ThreadInfo*)(p))->tid;
	sleep(m_delay); //延迟等待
	printf("NtoS_Wallker thread %d walk North Bridge require ! \n", m_id);
	//等待互斥信号量，保证对n_scount的互斥访问
	pthread_mutex_lock(&n_smutex); 
	if (n_scount == 0)
	{
		pthread_mutex_lock(&Nmutex); //DWORD waits = WaitForSingleObject(RW_mutex, -1);
	}
	n_scount++;
	pthread_mutex_unlock(&n_smutex);
	// 从北部江安桥往南走
	printf("NtoS_Wallker thread %d begins to walk in North Bridge ! \n", m_id);
	sleep(m_persist);
	printf("NtoS_Wallker thread %d finished walk in North Bridge ! \n", m_id);
	//释放互斥信号量
	pthread_mutex_lock(&n_smutex);
	n_scount--;
	if (n_scount == 0)
	{
		pthread_mutex_unlock(&Nmutex);
	}
	pthread_mutex_unlock(&n_smutex);

    // 从中部江安桥往南走
	printf("NtoS_Wallker thread %d begins to walk in Middle Bridge ! \n", m_id);
	sleep(m_persist);
	printf("NtoS_Wallker thread %d finished walk in Middle Bridge ! \n", m_id);

    printf("NtoS_Wallker thread %d walk south Bridge require ! \n", m_id);
	//等待互斥信号量，保证对s_ncount的互斥访问
	pthread_mutex_lock(&s_smutex); 
	if (s_scount == 0)
	{
		pthread_mutex_lock(&Smutex); //DWORD waits = WaitForSingleObject(RW_mutex, -1);
	}
	s_scount++;
	pthread_mutex_unlock(&s_smutex);
	// 从南部江安桥往南走
	printf("NtoS_Wallker thread %d begins to walk in South Bridge ! \n", m_id);
	sleep(m_persist);
	printf("NtoS_Wallker thread %d finished walk in South Bridge ! \n", m_id);
	//释放互斥信号量
	pthread_mutex_lock(&s_smutex);
	s_scount--;
	if (s_scount == 0)
	{
		pthread_mutex_unlock(&Smutex);
	}
	pthread_mutex_unlock(&s_smutex);
}


void Create(DWORD& n_thread,ThreadInfo *thread_info,DWORD& thread_ID){
	int res;
	void* thread_result;
	for (int i = 0; i < n_thread; i++)
	{
		if (thread_info[i].direction == 'N' || thread_info[i].direction == 'n') 
		{
			res=pthread_create(&h_thread[i], NULL, StoNWallkerThread,(void*) &thread_info[i]);
		}
		else
		{
			res=pthread_create(&h_thread[i] , NULL, NtoSWallkerThread,(void*) &thread_info[i]);
		}
	}
	//等待所有线程结束
	for(int i=0;i < n_thread; i++){
		res=pthread_join(h_thread[i],&thread_result);
	}
}
#endif 

int main(int argc, char ** argv)
{
	DWORD n_thread = 0;  //线程数目
	DWORD thread_ID;     //线程ID
	//线程对象数组
	
	ThreadInfo thread_info[20];
	//初始化同步对象
        Initial();
	//读取输入文件
	ifstream inFile;
	inFile.open("passer.txt");
	if (!inFile)
	{
		printf("error in open file !\n");
		return -1;
	}
	while (inFile)
	{
		inFile >> thread_info[n_thread].tid;
		inFile >> thread_info[n_thread].direction;
		inFile >> thread_info[n_thread].delay;
		inFile >> thread_info[n_thread].persist;
		inFile.get();
		n_thread++;
	}
	//创建线程
	Create(n_thread,thread_info,thread_ID);
	printf("All Walker have finished walking !\n");
	return 0;
}