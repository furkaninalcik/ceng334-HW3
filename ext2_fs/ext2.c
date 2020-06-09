#include "ext2.h"

#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BASE_OFFSET 1024 /* location of the superblock in the first group */

struct super_operations s_op;
struct inode_operations i_op;
struct file_operations f_op;

char fs_name[] = "ext2";

/* Implement functions in s_op, i_op, f_op here */

ssize_t my_read(struct file *f, char *buf, size_t len, loffset_t *o){

  //return pread(f->file_descriptor, void *buf, size_t count, off_t offset);


}


struct ext2_super_block read_ext2_superblock(struct file_system_type *fs){


  struct ext2_super_block ext2_sb ; //this is for reading the image file into the ext2_super_block fields 

  unsigned int u_int_buffer;

  //read(fs->file_descriptor, &u_int_buffer , sizeof(unsigned int) );

  //read(fs->file_descriptor, &ext2_sb.s_inodes_count , sizeof(unsigned int) );

  int offset = 1024; //superblock starts at offset 1024;

  //https://www.nongnu.org/ext2-doc/ext2.html#superblock -> the offset values taken from Table 3.3. Superblock Structure 


  size_t size_u_int = sizeof(unsigned int);
  size_t size_u_short = size_u_short;
  size_t size_u_char = sizeof(unsigned char);
  size_t size_char = sizeof(char);


  int fd = fs->file_descriptor;

  //OFFSET will be the offset + # of the previously read bytes

  pread(fd, &ext2_sb.s_inodes_count, size_u_int, offset );     /* Inodes count */
  pread(fd, &ext2_sb.s_blocks_count, size_u_int, offset += size_u_int );      /* Blocks count */
  pread(fd, &ext2_sb.s_r_blocks_count, size_u_int, offset += size_u_int);    /* Reserved blocks count */
  pread(fd, &ext2_sb.s_free_blocks_count, size_u_int, offset += size_u_int); /* Free blocks count */
  pread(fd, &ext2_sb.s_free_inodes_count, size_u_int, offset += size_u_int); /* Free inodes count */
  pread(fd, &ext2_sb.s_first_data_block, size_u_int, offset += size_u_int);  /* First Data Block */
  pread(fd, &ext2_sb.s_log_block_size, size_u_int, offset += size_u_int);    /* Block size */
  pread(fd, &ext2_sb.s_log_frag_size, size_u_int, offset += size_u_int);     /* Fragment size */
  pread(fd, &ext2_sb.s_blocks_per_group, size_u_int, offset += size_u_int);  /* # Blocks per group */
  pread(fd, &ext2_sb.s_frags_per_group, size_u_int, offset += size_u_int);   /* # Fragments per group */
  pread(fd, &ext2_sb.s_inodes_per_group, size_u_int, offset += size_u_int);  /* # Inodes per group */
  pread(fd, &ext2_sb.s_mtime, size_u_int, offset += size_u_int );            /* Mount time */
  pread(fd, &ext2_sb.s_wtime, size_u_int, offset += size_u_int );            /* Write time */


  pread(fd, &ext2_sb.s_mnt_count, size_u_short, offset += size_u_int);        /* Mount count */
  pread(fd, &ext2_sb.s_max_mnt_count, size_u_short, offset += size_u_short);    /* Maximal mount count */
  pread(fd, &ext2_sb.s_magic, size_u_short, offset += size_u_short);            /* Magic signature */
  pread(fd, &ext2_sb.s_state, size_u_short, offset += size_u_short);            /* File system state */
  pread(fd, &ext2_sb.s_errors, size_u_short, offset += size_u_short);           /* Behaviour when detecting errors */
  pread(fd, &ext2_sb.s_minor_rev_level, size_u_short, offset += size_u_short);  /* minor revision level */
  
  pread(fd, &ext2_sb.s_lastcheck, size_u_int, offset += size_u_short );          /* time of last check */
  pread(fd, &ext2_sb.s_checkinterval, size_u_int, offset += size_u_int );      /* max. time between checks */
  pread(fd, &ext2_sb.s_creator_os, size_u_int, offset += size_u_int );         /* OS */
  pread(fd, &ext2_sb.s_rev_level, size_u_int, offset += size_u_int );          /* Revision level */
  
  pread(fd, &ext2_sb.s_def_resuid, size_u_short, offset += size_u_int);       /* Default uid for reserved blocks */
  pread(fd, &ext2_sb.s_def_resgid, size_u_short, offset += size_u_short);       /* Default gid for reserved blocks */
  /*
   * These fields are for EXT2_DYNAMIC_REV superblocks only.
   *
   * Note: the difference between the compatible feature set and
   * the incompatible feature set is that if there is a bit set
   * in the incompatible feature set that the kernel doesn't
   * know about, it should refuse to mount the filesystem.
   *
   * e2fsck's requirements are more strict; if it doesn't know
   * about a feature in either the compatible or incompatible
   * feature set, it must abort and not try to meddle with
   * things it doesn't understand...
   */
  pread(fd, &ext2_sb.s_first_ino, size_u_int, offset += size_u_short );              /* First non-reserved inode */
  
  pread(fd, &ext2_sb.s_inode_size, size_u_short, offset += size_u_int);            /* size of inode structure */
  pread(fd, &ext2_sb.s_block_group_nr, size_u_short, offset += size_u_short);        /* block group # of this superblock */
  
  pread(fd, &ext2_sb.s_feature_compat, size_u_int, offset += size_u_short );         /* compatible feature set */
  pread(fd, &ext2_sb.s_feature_incompat, size_u_int, offset += size_u_int );       /* incompatible feature set */
  pread(fd, &ext2_sb.s_feature_ro_compat, size_u_int, offset += size_u_int );      /* readonly-compatible feature set */
  
  pread(fd, &ext2_sb.s_uuid , 16 * size_u_char, offset += size_u_int); ;              /* 128-bit uuid for volume */
  
  pread(fd, &ext2_sb.s_volume_name, 16 * size_char, offset += 16 * size_u_char); ;                /* volume name */
  pread(fd, &ext2_sb.s_last_mounted, 64 * size_char, offset += 16 * size_char); ;               /* directory where last mounted */
  pread(fd, &ext2_sb.s_algorithm_usage_bitmap, size_u_int, offset += 64 * size_char ); /* For compression */
  /*
   * Performance hints.  Directory preallocation should only
   * happen if the EXT2_COMPAT_PREALLOC flag is on.
   */
  pread(fd, &ext2_sb.s_prealloc_blocks, size_u_char , offset += size_u_int);      /* Nr of blocks to try to preallocate*/
  pread(fd, &ext2_sb.s_prealloc_dir_blocks, size_u_char , offset += size_u_char);  /* Nr to preallocate for dirs */
  
  pread(fd, &ext2_sb.s_padding1, size_u_short, offset += size_u_char);
  /*
   * Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.
   */
  pread(fd, &ext2_sb.s_journal_uuid , 16 * size_u_char , offset += size_u_short);  /* uuid of journal superblock */
  
  pread(fd, &ext2_sb.s_journal_inum, size_u_int, offset += 16 * size_u_char );      /* inode number of journal file */
  pread(fd, &ext2_sb.s_journal_dev, size_u_int, offset += size_u_int );       /* device number of journal file */
  pread(fd, &ext2_sb.s_last_orphan, size_u_int, offset += size_u_int );       /* start of list of inodes to delete */
  
  pread(fd, &ext2_sb.s_hash_seed, 4 * size_u_int, offset += size_u_int);       /* HTREE hash seed */
  
  pread(fd, &ext2_sb.s_def_hash_version, size_u_char , offset += 4 * size_u_int); /* Default hash version to use */
  pread(fd, &ext2_sb.s_reserved_char_pad, size_u_char , offset += size_u_char);
  
  pread(fd, &ext2_sb.s_reserved_word_pad, size_u_short, offset += size_u_char);
  
  pread(fd, &ext2_sb.s_default_mount_opts, size_u_int, offset += size_u_short );
  pread(fd, &ext2_sb.s_first_meta_bg, size_u_int, offset += size_u_int ); /* First metablock block group */
  
  pread(fd, &ext2_sb.s_reserved, size_u_int * 190, offset += size_u_int); /* Padding to the end of the block */


  return ext2_sb;



}




struct super_block *my_get_superblock(struct file_system_type *fs){

  //TODO This function
  //allocates and fills the fields of the superblock of the file system fs returning a pointer to the
  //allocated struct super_block .



  struct super_block sb ; 



  struct super_block* my_superblock_pointer = malloc(sizeof *my_superblock);



  struct ext2_super_block ext2_sb = read_ext2_superblock(fs);






  struct super_operations* my_super_operations = malloc(sizeof *my_super_operations);




  my_superblock->s_inodes_count = 17;

  my_superblock->s_inodes_count = 0;      /* Inodes count */
  my_superblock->s_blocks_count = 0;      /* Blocks count */
  my_superblock->s_free_blocks_count = 0; /* Free blocks count */
  my_superblock->s_free_inodes_count = 0; /* Free inodes count */
  my_superblock->s_first_data_block = 0;  /* First Data Block */
  my_superblock->s_blocksize = 0;        /* blocksize in bytes */
  my_superblock->s_blocksize_bits = 0;   /* log2(s_blocksize) */
  my_superblock->s_blocks_per_group = 0;  /* # Blocks per group */
  my_superblock->s_inodes_per_group = 0;  /* # Inodes per group */
  my_superblock->s_minor_rev_level = 0; /* minor revision level */
  my_superblock->s_rev_level = 0;         /* Revision level */
  my_superblock->s_first_ino = 0;         /* First non-reserved inode */
  my_superblock->s_inode_size = 0;      /* size of inode structure */
  my_superblock->s_block_group_nr = 0;  /* block group # of this superblock */
  my_superblock->s_maxbytes = 0;    /* Max file size */
  my_superblock->s_type = fs ;        /* Pointer to file system type */
  my_superblock->s_op = my_super_operations;    /* Pointer to super operations */
  my_superblock->s_flags = 0;            /* */
  my_superblock->s_magic = 0;            /* Magic number */
  my_superblock->s_root = NULL;            /* Directory entry for root */
  my_superblock->s_fs_info = NULL;                  /* Filesystem private info */
  

  return my_superblock; 

}




struct file_system_type *initialize_ext2(const char *image_path) {
  /* fill super_operations s_op */
  /* fill inode_operations i_op */
  /* fill file_operations f_op */
  /* for example:
      s_op = (struct super_operations){
        .read_inode = your_read_inode_function,
        .statfs = your_statfs_function,
      };
  */


  //filling super_operations s_op 





  myfs.name = fs_name;
  myfs.file_descriptor = open(image_path, O_RDONLY);

  printf("file_descriptor of the image  %d\n" , myfs.file_descriptor);


  /* assign get_superblock function
     for example:
        myfs.get_superblock = your_get_superblock;
  */




  //assigning the get_superblock function with my implementation

  myfs.get_superblock = my_get_superblock;


  return &myfs;
}

