



struct id_block {
  word len;
  word p2;
  char data[152];
  };

extern struct id_block id1_block;
extern struct id_block id2_block;


struct ticblock {
  word a;
  word b;
  };

struct tscblock {
  word a;
  word b;
  char buffer[512];
  };

extern struct ticblock tic_block;
extern struct tscblock tsc_block;


struct file_buffer_1024 {
 word type_word;
 word block_length;
 word buffer_size;
 word remaining_chars_to_read;
 word offset_to_next_character_to_read;
 word file_position_of_buffer;
 word physical_position_in_file;
 char buffer[1024];
 };
 
extern struct file_buffer_1024 input_buffer; 

struct file_buffer_260 {
 word type_word;
 word block_length;
 word buffer_size;
 word remaining_chars_to_read;
 word offset_to_next_character_to_read;
 word file_position_of_buffer;
 word physical_position_in_file;
 char buffer[260];
 };
 
extern struct file_buffer_260 tty_buffer;






#define id1blk id1_block.len
#define id2blk id2_block.len
#define ticblk tic_block.a
#define tscblk tsc_block.a
#define inpbuf input_buffer.type_word
#define ttybuf tty_buffer.type_word

extern const struct spitbol_constants c;

extern struct spitbol_variables v;

#define polct v.polct
#define headv c.headv
#define r_fcb v.r_fcb
#define stbas v.stbas
#define flptr v.flptr
#define flprt v.flprt
#define gtcef v.gtcef
#define c_aaa c.c_aaa
#define c_yyy c.c_yyy
#define mxlen v.mxlen
#define dnamp v.dnamp
#define dnamb v.dnamb
#define pmhbs v.pmhbs

#define g_aaa v.g_aaa
#define hshtb v.hshtb
#define w_yyy v.w_yyy
#define state v.state
#define stbas v.stbas
#define statb v.statb
#define timsx v.timsx
#define stage v.stage
#define lowspmin v.lowspmin
