#ifndef FAT_H
#define FAT_H

/*INCLUDE*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*DEFINE*/
#define SECTOR_SIZE	512
#define CLUSTER_SIZE 2*SECTOR_SIZE
#define ENTRY_BY_CLUSTER CLUSTER_SIZE/sizeof(dir_entry_t)
#define FAT_SIZE 4096
#define fat_name	     "fat.part"

struct _dir_entry_t {
	char filename[18];
	uint8_t attributes;
	uint8_t reserved[7];
	uint16_t first_block;
	uint32_t size;
};

typedef struct _dir_entry_t  dir_entry_t;

union data_cluster{
	dir_entry_t dir[ENTRY_BY_CLUSTER];
	uint8_t data[CLUSTER_SIZE];
};

// utils
union data_cluster __readCluster__(int index);
void __writeCluster__(int index, union data_cluster *cluster);
int __findFreeSpaceFat__();
void __writeFat__();
void __slice_str__(char * str, char * buffer, int start, int end);
void __resize__(char* directories, size_t extend_size);

//shell
void init();
void load ();
void create(char* directories);
void unlink(char* directories);
void write(char * words, char* directories);
void append(char * words, char* directories);
void read(char* directories);
void mkdir(char* directories);
void ls (char* directories);
#endif