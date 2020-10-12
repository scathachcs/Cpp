#include<iostream>
using namespace std;

int n1 = 5, n2 = 10;
int in_buf1 = 0, out_buf1 = 0, in_buf2 = 0, out_buf2 = 0;
int count1 = 0, count2 = 0;
int buf1[10];
int buf2[10];

int Calculate(int x) {
	return x * 10;
}
# if _win64
#include <Windows.h>
#define sleep(n) Sleep(n*1000)
SRWLOCK lock1;
SRWLOCK lock2;
CONDITION_VARIABLE buf_1_empty;
CONDITION_VARIABLE buf_1_full;
CONDITION_VARIABLE buf_2_empty;
CONDITION_VARIABLE buf_2_full;
HANDLE in_thread; //全局句柄变量
HANDLE c_thread; //全局句柄变量
HANDLE out_thread; //全局句柄变量

void Input() {
	
	int x;
	while (cin>>x) {
		AcquireSRWLockExclusive(&lock1);
		while (count1 == n1) {
			SleepConditionVariableSRW(&buf_1_empty, &lock1, INFINITE, 0);
		}
		buf1[in_buf1] = x;
		in_buf1 = (in_buf1 + 1) % n1;
		count1++;
		ReleaseSRWLockExclusive(&lock1);
		WakeConditionVariable(&buf_1_full);
	}
	
}

void Calculator() {
	while (1) {
		int x;
		AcquireSRWLockExclusive(&lock1);
		while (count1 == 0) {
			SleepConditionVariableSRW(&buf_1_full, &lock1, INFINITE,0);
		}
		x = buf1[out_buf1];//从buf1取得数据
		out_buf1 = (out_buf1 + 1) % n1;
		count1--;
		ReleaseSRWLockExclusive(&lock1);
		WakeConditionVariable(&buf_1_empty);


		x = Calculate(x);//计算数据

		AcquireSRWLockExclusive(&lock2);
		while (count2 == n2) {
			SleepConditionVariableSRW(&buf_2_empty, &lock2, INFINITE, 0);
		}
		buf2[in_buf2] = x;//放入数据入buf2
		in_buf2 = (in_buf2 + 1) % n2;
		count2++;
		ReleaseSRWLockExclusive(&lock2);
		WakeConditionVariable(&buf_2_full);
	}
	
	
}

void Print() {
	while (1) {
		AcquireSRWLockExclusive(&lock2);
		while (count2 == 0) {
			SleepConditionVariableSRW(&buf_2_full, &lock2, INFINITE, 0);
		}
		cout << buf2[out_buf2] << endl;
		out_buf2 = (out_buf2 + 1) % n2;
		count2--;
		ReleaseSRWLockExclusive(&lock2);
		WakeConditionVariable(&buf_2_empty);
	}
}


void initial() {
	InitializeSRWLock(&lock1);
	InitializeSRWLock(&lock2);
}
void Create(DWORD& thread_ID) {
		in_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(Input), NULL, 0, &thread_ID);
		
		c_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(Calculator), NULL, 0, &thread_ID);
		
		out_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(Print), NULL, 0, &thread_ID);

		sleep(10);//等待所有线程完成

}

#endif

#ifdef __linux
#include<pthread.h>
#include <unistd.h>
typedef unsigned int DWORD;

pthread_mutex_t lock1;
pthread_mutex_t lock2;
pthread_cond_t  buf_1_empty;
pthread_cond_t  buf_1_full;
pthread_cond_t  buf_2_empty;
pthread_cond_t  buf_2_full;
pthread_t in_thread; //全局句柄变量
pthread_t c_thread; //全局句柄变量
pthread_t out_thread; //全局句柄变量

void* Input(void* p) {
	
	int x;
	while (cin>>x) {
		pthread_mutex_lock(&lock1);
		while (count1 == n1) {
			pthread_cond_wait(&buf_1_empty, &lock1);
		}
		buf1[in_buf1] = x;
		in_buf1 = (in_buf1 + 1) % n1;
		count1++;
		pthread_mutex_unlock(&lock1);
		pthread_cond_signal(&buf_1_full);
	}
	
}

void* Calculator(void* p) {
	while (1) {
		int x;
		pthread_mutex_lock(&lock1);
		while (count1 == 0) {
			pthread_cond_wait(&buf_1_full, &lock1);
		}
		x = buf1[out_buf1];//从buf1取得数据
		out_buf1 = (out_buf1 + 1) % n1;
		count1--;
		pthread_mutex_unlock(&lock1);
		pthread_cond_signal(&buf_1_empty);


		x = Calculate(x);//计算数据

		pthread_mutex_lock(&lock2);
		while (count2 == n2) {
			pthread_cond_wait(&buf_2_empty, &lock2);
		}
		buf2[in_buf2] = x;//放入数据入buf2
		in_buf2 = (in_buf2 + 1) % n2;
		count2++;
		pthread_mutex_unlock(&lock2);
		pthread_cond_signal(&buf_2_full);
	}
	
	
}

void* Print(void* p) {
	while (1) {
		pthread_mutex_lock(&lock2);
		while (count2 == 0) {
			pthread_cond_wait(&buf_2_full, &lock2);
		}
		cout << buf2[out_buf2] << endl;
		out_buf2 = (out_buf2 + 1) % n2;
		count2--;
		pthread_mutex_unlock(&lock2);
		pthread_cond_signal(&buf_2_empty);
	}
}


void initial() {
	lock1=PTHREAD_MUTEX_INITIALIZER;
    lock2=PTHREAD_MUTEX_INITIALIZER;
    buf_1_empty= PTHREAD_COND_INITIALIZER;
    buf_1_full= PTHREAD_COND_INITIALIZER;
    buf_2_empty= PTHREAD_COND_INITIALIZER;
    buf_2_full= PTHREAD_COND_INITIALIZER;
}
void Create(DWORD& thread_ID) {
    int res;
	void* thread_result;
    res=pthread_create(&in_thread, NULL, Input, NULL);
    res=pthread_create(&c_thread, NULL, Calculator, NULL);
	res=pthread_create(&out_thread, NULL, Print , NULL);
    res=pthread_join(in_thread,&thread_result);
    res=pthread_join(c_thread,&thread_result);
    res=pthread_join(out_thread,&thread_result);
	//等待所有线程完成

}
#endif


int main() {
	DWORD thread_ID=0;     //线程ID
	initial();//初始化读写锁
	Create(thread_ID);//创建进程
	printf("all thread are over!");
	return 0;
}