#include "lab3.h"

//
// lab3 code should be located here!
//
#include <windows.h> 
#include <stdio.h> 
#include <map> 
#include <string> 

#define MAX_SEM_COUNT 10 
#define THREADCOUNT 12 

HANDLE stdout_mutex;
HANDLE app_mutex;

HANDLE semA, semB, semC, semD, semE, semF, semG, semH, semK, semM, semN, semI;
HANDLE semB1, semE1, semI1;
HANDLE semIch, semKch, semMch;

std::vector<HANDLE> threads;

unsigned int lab3_thread_graph_id()
{
	return 2;
}

const char* lab3_unsynchronized_threads()
{
	return "bcde";
}

const char* lab3_sequential_threads()
{
	return "ikm";
}


DWORD WINAPI thread_a(LPVOID);
DWORD WINAPI thread_b(LPVOID);

DWORD WINAPI thread_c(LPVOID);
DWORD WINAPI thread_d(LPVOID);
DWORD WINAPI thread_e(LPVOID);

DWORD WINAPI thread_g(LPVOID);
DWORD WINAPI thread_h(LPVOID);
DWORD WINAPI thread_f(LPVOID);
DWORD WINAPI thread_i(LPVOID);

DWORD WINAPI thread_k(LPVOID);
DWORD WINAPI thread_m(LPVOID);

DWORD WINAPI thread_n(LPVOID);


HANDLE create_thread(DWORD(WINAPI* temp)(LPVOID))
{
	HANDLE new_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)temp, NULL, 0, NULL);
	if (new_thread)
		return new_thread;
	std::cerr << "Cannot create thread, error: " << GetLastError() << std::endl;
	exit(-1);
}

HANDLE sem_init(int n)
{
	HANDLE new_sem = CreateSemaphore(nullptr, n, MAX_SEM_COUNT, nullptr);
	if (new_sem)
		return new_sem;
	std::cerr << "Cannot create semaphore:" << GetLastError() << std::endl;
	exit(-1);
}


void wait_threads()
{
	for (int i = 0; i < THREADCOUNT; i++)
	{
		
		while (WaitForSingleObject(threads[i], 0) == WAIT_TIMEOUT)
		{
			Sleep(0);
		}
	}
}

void print_char(char c)
{
	while (WaitForSingleObject(stdout_mutex, 0) == WAIT_TIMEOUT)
		Sleep(0);
	std::cout << c << std::flush;
	ReleaseMutex(stdout_mutex);
}


void sem_wait(HANDLE s)
{
	auto status = WaitForSingleObject(s, 0);
	while (status == WAIT_TIMEOUT)
	{
		status = WaitForSingleObject(s, 0);
	}
}

void sem_post(HANDLE s)
{
	ReleaseSemaphore(s, 1, NULL);
}

void interval_0_wait() //ab
{
	sem_wait(semB);
	sem_wait(semA);
}

void interval_1_wait() //bcde
{
	sem_wait(semB1);
	sem_wait(semC);
	
	sem_wait(semD);
	sem_wait(semE);
}

void interval_2_wait() //ighfe
{
	sem_wait(semI);
	sem_wait(semH);
	sem_wait(semG);
	sem_wait(semF);
	sem_wait(semE1);
}

void interval_3_wait() //ikm
{
	sem_wait(semI1);
	sem_wait(semK);
	sem_wait(semM);


}


DWORD WINAPI thread_a(LPVOID)
{

	for (int i = 0; i < 3; i++)
	{
		print_char('a'); computation();
	}

	//0й интервал
	for (int i = 0; i < 4; i++) { sem_post(semA); }
	return 0;
}

DWORD WINAPI thread_b(LPVOID)
{
	//на 0м интервале 
	for (int i = 0; i < 3; i++) { print_char('b'); computation(); }

	for (int i = 0; i < 4; i++) { sem_post(semB); }

	//1й интервал
	for (int i = 0; i < 3; i++) { print_char('b'); computation(); }

	for (int i = 0; i < 5; i++) { sem_post(semB1); }
		
	return 0;
}

DWORD WINAPI thread_c(LPVOID)
{
	interval_0_wait(); //ждем 0й интервал 

	for (int i = 0; i < 3; i++) { print_char('c'); computation(); }

	for (int i = 0; i < 5; i++) { sem_post(semC); }

	return 0;
}

DWORD WINAPI thread_d(LPVOID)
{
	interval_0_wait(); //ждем 0й интервал 

	for (int i = 0; i < 3; i++) { print_char('d'); computation(); }

	for (int i = 0; i < 5; i++) { sem_post(semD); }

	
	return 0;
}

DWORD WINAPI thread_e(LPVOID)
{
	interval_0_wait(); //ждем 0й интервал 
	//на 1м интервале 
	for (int i = 0; i < 3; i++) { print_char('e'); computation(); }

	for (int i = 0; i < 5; i++) { sem_post(semE); }
		
	interval_1_wait();
	//2й интервал
	for (int i = 0; i < 3; i++) { print_char('e'); computation(); }

	for (int i = 0; i < 3; i++) { sem_post(semE1); }

	return 0;
}

DWORD WINAPI thread_f(LPVOID)
{
	
	interval_1_wait(); //ждем 1й интервал 
	for (int i = 0; i < 3; i++) { print_char('f'); computation(); }

	for (int i = 0; i < 3; i++) { sem_post(semF); }


	return 0;
}

DWORD WINAPI thread_g(LPVOID)
{
	
	interval_1_wait(); //ждем 1й интервал 
	for (int i = 0; i < 3; i++) { print_char('g'); computation(); }

	for (int i = 0; i < 3; i++) { sem_post(semG); }


	return 0;
}

DWORD WINAPI thread_h(LPVOID)
{

	interval_1_wait(); //ждем 1й интервал 
	for (int i = 0; i < 3; i++) { print_char('h'); computation(); }

	for (int i = 0; i < 3; i++) { sem_post(semH); }


	return 0;
}

DWORD WINAPI thread_i(LPVOID)
{
	interval_1_wait(); //ждем 1й интервал 
	//2й интервал
	for (int i = 0; i < 3; i++) { print_char('i'); computation(); }

	for (int i = 0; i < 3; i++) { sem_post(semI); }
	
	interval_2_wait();

	//на 3м интервале
	for (int i = 0; i < 3; i++)
	{
		sem_wait(semIch);
		print_char('i');
		computation();
		sem_post(semKch);
	}

	for (int i = 0; i < 1; i++) { sem_post(semI1); }
	
	return 0;
}

DWORD WINAPI thread_k(LPVOID)
{

	interval_2_wait();


	for (int i = 0; i < 3; i++)
	{
		sem_wait(semKch);
		print_char('k');
		computation();
		sem_post(semMch);
	}

	for (int i = 0; i < 1; i++) { sem_post(semK); }

	return 0;
}

DWORD WINAPI thread_m(LPVOID)
{

	interval_2_wait();

	
	for (int i = 0; i < 3; i++)
	{
		sem_wait(semMch);
		print_char('m');
		computation();
		sem_post(semIch);
	}

	for (int i = 0; i < 1; i++) { sem_post(semM); }

	return 0;
}

DWORD WINAPI thread_n(LPVOID)
{
	interval_3_wait();
	for (int i = 0; i < 3; i++) { print_char('n'); computation(); }


	return 0;
}

int lab3_init()
{
	
	stdout_mutex = CreateMutex(NULL, false, NULL);
	app_mutex = CreateMutex(NULL, false, NULL);
	semA = sem_init(0);
	semB = sem_init(0);
	semC = sem_init(0);
	semD = sem_init(0);
	semF = sem_init(0);
	semE = sem_init(0);
	semI = sem_init(0);
	semG = sem_init(0);
	semH = sem_init(0);
	semK = sem_init(0);
	semM = sem_init(0);
	semN = sem_init(0);


	semB1 = sem_init(0);


	semE1 = sem_init(0);

	semI1 = sem_init(0);


	semIch = sem_init(0);
	semKch = sem_init(1);
	semMch = sem_init(0);

	int count = 0;

	threads.resize(12);


	threads[count] = create_thread(thread_a);
	count++;
	threads[count] = create_thread(thread_b);
	count++;
	threads[count] = create_thread(thread_c);
	count++;
	threads[count] = create_thread(thread_d);
	count++;
	threads[count] = create_thread(thread_e);
	count++;
	threads[count] = create_thread(thread_f);
	count++;
	threads[count] = create_thread(thread_g);
	count++;
	threads[count] = create_thread(thread_h);
	count++;
	threads[count] = create_thread(thread_i);
	count++;
	threads[count] = create_thread(thread_k);
	count++;
	threads[count] = create_thread(thread_m);
	count++;
	threads[count] = create_thread(thread_n);
	count++;

	wait_threads();
	CloseHandle(stdout_mutex);
	CloseHandle(app_mutex);

	CloseHandle(semA);
	CloseHandle(semB);
	CloseHandle(semC);
	
	return 0;
}
