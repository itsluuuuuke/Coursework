/*
    sim_pag_lru.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<limits.h>

#include "sim_paging.h"

// Function that initialises the tables

void init_tables (ssystem * S)
{
    int i;

    // Reset pages
    memset (S->pgt, 0, sizeof(spage)*S->numpags);

    // Empty LRU stack
    S->lru = -1;

    // Reset LRU(t) time
    S->clock = 0;

    // Circular list of free frames
    for (i=0; i<S->numframes-1; i++)
    {
        S->frt[i].page = -1;
        S->frt[i].next = i+1;
    }

    S->frt[i].page = -1;    // Now i == numframes-1
    S->frt[i].next = 0;     // Close circular list
    S->listfree = i;        // Point to the last one

    // Empty circular list of occupied frames
    S->listoccupied = -1;
}

// Functions that simulate the hardware of the MMU

unsigned sim_mmu (ssystem * S, unsigned virtual_addr, char op)
{
    unsigned physical_addr;
    int page, frame, offset;
	
	page = virtual_addr / S->pagsz; //Quotient
	offset = virtual_addr % S->pagsz;
	if (page < 0 || page>=S->numpags)
	{
		S->numillegalrefs ++;
		return ~0U;
	}

	if(!S->pgt[page].present)
		handle_page_fault(S,virtual_addr);
	
	//Now is present 

	frame = S->pgt[page].frame;
	physical_addr = frame * S->pagsz+offset;

	reference_page(S,page,op);

	if(S->detailed)
		printf("\t%c %u==P%d(M%d)+%d\n",op,virtual_addr,page,frame,offset);

	 //Remainder
    // TODO: Type in the code that simulates the MMU's (hardware)
    //       behaviour in response to a memory access operation

    return physical_addr;
}

void reference_page (ssystem * S, int page, char op)
{
    if (op=='R')                         // If it's a read,
        S->numrefsread ++;               // count it
    else if (op=='W')
    {                                    // If it's a write,
        S->pgt[page].modified = 1;       // count it and mark the
        S->numrefswrite ++;              // page 'modified'
    }
	
	S->clock++;
	S->pgt[page].timestamp = S->clock;   //Store the clock in the timestamp
	if(S->pgt[page].timestamp == 0)
		printf("The timestamp overflow back to 0!");
}

// Functions that simulate the operating system

void handle_page_fault (ssystem * S, unsigned virtual_addr)
{
    int page, victim, frame, last;

	S->numpagefaults++;
	page = virtual_addr / S->pagsz;

	if(S->detailed)
		printf("@ PAGE FAULT in P%d!\n",page);

	if(S->listfree!=-1) //If there are free frames
	{
		last = S->listfree;
		frame = S->frt[last].next; //

		if(frame == last)
			S->listfree = -1;
		else
			S->frt[last].next = S->frt[frame].next;

		occupy_free_frame(S,frame,page);
	}

	else
	{
		victim = choose_page_to_be_replaced(S);

		replace_page(S,victim,page);
	}

    // TODO: Type in the code that simulates the Operating
    //       System's response to a page fault trap
}

int choose_page_to_be_replaced (ssystem * S)
{
    int frame,victim; //victim is the #page that will be replaced
	unsigned local_min = UINT_MAX; //To store the minimum timestamp
   
	for(int i = 0; i < S->numframes; i++){
		if(S->pgt[S->frt[i].page].timestamp < local_min){
			local_min = S->pgt[S->frt[i].page].timestamp;
			victim = S->frt[i].page;
		}
	}
	frame = S->pgt[victim].frame;

    if (S->detailed)
        printf ("@ Choosing (LRU) P%d of F%d to be "
                "replaced\n", victim, frame);
	
    return victim;
}

void replace_page (ssystem * S, int victim, int newpage)
{
    int frame;

    frame = S->pgt[victim].frame;

    if (S->pgt[victim].modified)
    {
        if (S->detailed)
            printf ("@ Writing modified P%d back (to disc) to "
                    "replace it\n", victim);

        S->numpgwriteback ++;
    }

    if (S->detailed)
        printf ("@ Replacing victim P%d with P%d in F%d\n",
                victim, newpage, frame);

    S->pgt[victim].present = 0;

    S->pgt[newpage].present = 1;
    S->pgt[newpage].frame = frame;
    S->pgt[newpage].modified = 0;

    S->frt[frame].page = newpage;
}

void occupy_free_frame (ssystem * S, int frame, int page)
{
    if (S->detailed)
        printf ("@ Storing P%d in F%d\n", page, frame);
    
    S->pgt[page].frame = frame;
    S->pgt[page].present = 1;
    S->frt[frame].page = page;
    

    // TODO: Write the code that links the page with the frame and
    //       vice-versa, and wites the corresponding values in the
    //       state bits of the page (presence...)
}

// Functions that show results

void print_page_table (ssystem * S)
{
    int p;

    printf ("%10s %10s %10s   %s  %10s\n",
            "PAGE", "Present", "Frame", "Modified", "Timestamp");

    for (p=0; p<S->numpags; p++)
        if (S->pgt[p].present)
            printf ("%8d   %6d     %8d   %6d  %8d\n", p,
                    S->pgt[p].present, S->pgt[p].frame,
                    S->pgt[p].modified, S->pgt[p].timestamp);
        else
            printf ("%8d   %6d     %8s   %6s\n", p,
                    S->pgt[p].present, "-", "-");
}

void print_frames_table (ssystem * S)
{
    int p, f;

    printf ("%10s %10s %10s   %s\n",
            "FRAME", "Page", "Present", "Modified");

    for (f=0; f<S->numframes; f++)
    {
        p = S->frt[f].page;

        if (p==-1)
            printf ("%8d   %8s   %6s     %6s\n", f, "-", "-", "-");
        else if (S->pgt[p].present)
            printf ("%8d   %8d   %6d     %6d\n", f, p,
                    S->pgt[p].present, S->pgt[p].modified);
        else
            printf ("%8d   %8d   %6d     %6s   ERROR!\n", f, p,
                    S->pgt[p].present, "-");
    }
}

void print_replacement_report (ssystem * S)
{
	unsigned local_max = 0, local_min = UINT_MAX;
    printf ("LRU replacement \n");
	for(int i = 0; i < S->numpags; i++){
		if(S->pgt[i].timestamp < local_min){
			local_min = S->pgt[i].timestamp;
			S->pag_with_MIN_timestamp = i;
		}
	}
	S->timestamp_MIN = local_min;
	//Search for the maximum
	for(int i = 0; i < S->numpags; i++){
		if(S->pgt[i].timestamp > local_max){
			local_max = S->pgt[i].timestamp;
			S->pag_with_MAX_timestamp = i;
		}
	}

	S->timestamp_MAX = local_max;
	printf ("Page with Maximum timestamp:\n %10s   %10s\n","#Page","Timestamp");
	printf ("       %d        %u\n",S->pag_with_MAX_timestamp, S->timestamp_MAX);
	printf ("Page with Minimum timestamp:\n %10s   %10s\n","#Page","Timestamp");
	printf ("       %d        %u\n",S->pag_with_MIN_timestamp, S->timestamp_MIN);
}
