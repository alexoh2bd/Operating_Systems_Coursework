#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <ufs/ffs/fs.h>
#include <ufs/ufs/dinode.h>
#include <ufs/ufs/dir.h>
#define FRAG_SIZE 4096
#define BLK_SIZE 4096

struct ufs2_dinode* find_inode_addr(char * start, struct fs * sb, uint32_t inode_no);
void find_data(char * start, struct fs * sb, struct ufs2_dinode *inode, char ** directories, int dir_layer, int dir_length);

int
main(int argc, char*argv[])
{
	int fd;
 	char * start;
	struct fs * superblock;
	struct ufs2_dinode * root_inode;

	int superblock_offset=65536;
	int frag_size = 4096;
	int disk_image_size = 512* 1024 *1024;

	fd = open(argv[1], O_RDONLY);
	char* directories[20]; // Arbitrarily setting a max of 20 directories in the path
   	int count = 0;

	// parse argv[2] into string array
   	char* token = strtok(argv[2], "/\\"); // Tokenize the path based on '/' and '\'
	int dir_length=0;
    	while (token != NULL) {
      		directories[count] = token;
//		printf("Directory: %s\n", directories[count]);
       	 	count++;
        	token = strtok(NULL, "/\\");
		dir_length++;
    	}

	// map disk
    	start = mmap(NULL,  disk_image_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (start  == MAP_FAILED) {
        	perror("mmap");
       	 	close(fd);
        	return -1;
    	}
	
	//superblock
	superblock = (struct fs * ) (start+SBLOCK_UFS2);
	
	root_inode = find_inode_addr(start, superblock, UFS_ROOTINO);
//	printf("inode 1: %ld", root_inode->di_db[0]);
//	printf("inode 2: %u", root_inode->di_db[1]);
	find_data(start, superblock, root_inode, directories, 0, dir_length);

	munmap(start, disk_image_size);
	close(fd);
}

struct ufs2_dinode* find_inode_addr(char * start, struct fs * superblock, uint32_t inode_no){
	uint32_t i_fsba= ino_to_fsba(superblock, inode_no);
	uint32_t i_fsbo = ino_to_fsbo(superblock, inode_no);
	
	struct ufs2_dinode *inode = (struct ufs2_dinode *)(start + (i_fsba*FRAG_SIZE))+i_fsbo;
	return inode;
}

void find_data(char * start, struct fs * sb, struct ufs2_dinode *  inode, char ** directories, int dir_layer, int dir_length){
	int i = 0;
	
	// Handles last direct layer
	if(dir_layer== dir_length){
		struct direct * dir =  (struct direct *)(start + inode->di_db[i] * BLK_SIZE);
		// if last dir is a directory
		if(dir->d_type == 4){
			printf("Path to Directory %s\n", directories[dir_layer-1]);
		}
		else{
			// print contents of file
			while(inode->di_db[i] > 0){
				
				char * text=  (char *)(start + inode->di_db[i] * BLK_SIZE);
				printf("%s", text);
				i++;
			}
		}
	       	return;
	}
	int foundDir = 0;
	// While there are  inode blocks
	while(inode->di_db[i] >0){
		// char * pointer and keep track of offset within the block
		char * dir_start =  start + inode->di_db[i] * BLK_SIZE;
		uint32_t blk_offset = 0;
		
		struct direct * dir_entry = (struct direct *) dir_start;
		// Loop through the Direct structs within each Block 
   		while (blk_offset<BLK_SIZE && dir_entry-> d_ino !=0 && dir_entry->d_reclen !=0) {
			dir_entry = (struct direct *) dir_start;
		//	printf("name: %s, layer: %d\n", dir_entry->d_name, dir_layer);
			// Conditions to print directory, don't want data blocks from non-directory direct
			if(strcmp(dir_entry->d_name, directories[dir_layer]) == 0){
				struct ufs2_dinode * rec_ino = find_inode_addr(start, sb,  dir_entry->d_ino);
				// print and recursively call the inside directories
				find_data(start, sb, rec_ino, directories,  dir_layer+1, dir_length);
				foundDir=1;
				return;
			}

			blk_offset += dir_entry->d_reclen;
			dir_start += dir_entry->d_reclen;

		}
		i+=1;
	}
	if(foundDir == 0){ printf("Directory %s not found.\n", directories[dir_layer]);}

}

