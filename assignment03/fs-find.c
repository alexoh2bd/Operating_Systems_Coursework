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
void printdir(char * start, struct fs * sb, struct ufs2_dinode *inode, int depth);

int
main(int argc, char*argv[])
{
	int superblock_offset=65536;
	int frag_size = 4096;
	int disk_image_size = 512* 1024 *1024;
	int fd;
	struct fs * superblock;
	struct ufs2_dinode * root_inode;

	// open partition image
	fd = open(argv[1], O_RDONLY);

	// map memory
    	char *start = mmap(NULL,  disk_image_size, PROT_READ, MAP_PRIVATE, fd, 0);

	if (start  == MAP_FAILED) {
        	perror("mmap");
       	 	close(fd);
        	return -1;
    	}

	// find superblock struct
	superblock = (struct fs * ) (start+SBLOCK_UFS2);
	
	// find root inode
	root_inode = find_inode_addr(start, superblock,UFS_ROOTINO);

	// print directory of root inode
	printdir(start, superblock, root_inode,0);


	munmap(start, disk_image_size);
	close(fd);
}

struct ufs2_dinode* find_inode_addr(char *start, struct fs *sb, uint32_t inode_no){
	// find address & offset for calculating inode address
	uint32_t i_fsba= ino_to_fsba(sb, inode_no);
	uint32_t i_fsbo = ino_to_fsbo(sb, inode_no);


	struct ufs2_dinode *inode = (struct ufs2_dinode *)(start + (i_fsba*FRAG_SIZE))+i_fsbo;// * sizeof(struct ufs2_dinode);
	return inode;
}

void printdir(char * start, struct fs * sb, struct ufs2_dinode *inode, int depth){
	int i = 0;
	//printf("Depth: %d\n", depth);
	// While there are  inode blocks
	while(inode->di_db[i] >0){
		// char * pointer and keep track of offset within the block
		char * dir_start =  start + inode->di_db[i] * BLK_SIZE;
		uint32_t blk_offset = 0;
		
		struct direct * dir_entry = (struct direct *) dir_start;
		// Loop through the Direct structs within each Block 
   		while (blk_offset<BLK_SIZE && dir_entry-> d_ino !=0 && dir_entry->d_reclen !=0) {
			dir_entry = (struct direct *) dir_start;
		//	printf("THIS IS DIR %s, depth: %d\n", dir_entry->d_name, depth);
			// Conditions to print directory, don't want data blocks from non-directory direct
			if(strcmp(dir_entry->d_name,"." ) !=0  && strcmp(dir_entry->d_name, "..")!=0 && dir_entry->d_type<9 && dir_entry->d_name[0] != '\0'){
				for(int j =0; j< depth; j++){ printf("   "); }
				// print and recursively call the inside directories
				printf("%s\n", dir_entry->d_name);
				struct ufs2_dinode * rec_ino = find_inode_addr(start,sb, dir_entry->d_ino);
				if(dir_entry->d_type == 4){
					printdir(start, sb, rec_ino, depth+1);
				}
			}

			blk_offset += dir_entry->d_reclen;
			dir_start += dir_entry->d_reclen;

		}
		i++;
	}
}
