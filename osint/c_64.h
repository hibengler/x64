// copyright 1987-2012 robert b. k. dewar and mark emmer.

// copyright 2012-2015 david shields
// copyright 2018-2020 hib Engler
// this file is part of macro spitbol.
//
//     macro spitbol is free software: you can redistribute it and/or modify
//     it under the terms of the gnu general public license as published by
//     the free software foundation, either version 2 of the license, or
//     (at your option) any later version.
//
//     macro spitbol is distributed in the hope that it will be useful,
//     but without any warranty// without even the implied warranty of
//     merchantability or fitness for a particular purpose.  see the
//     gnu general public license for more details.
//
//     you should have received a copy of the gnu general public license
//     along with macro spitbol.  if not, see <http://www.gnu.org/licenses/>.
#include <math.h>

// this is included first for the C64 interface.

typedef unsigned char m_char;  // reference to byte in memory
typedef unsigned char d_char; // define value of byte
typedef double m_real;	// reference to floating point value in memory
typedef double d_real;  // define value for floating point

typedef unsigned long d_word;
typedef unsigned long m_word;
//typedef unsigned long word;
// port.h does this one


typedef union itis { 
  word w;
  word *wp;
  m_char *chp;  /* chp for multibyte characters experiimental */
  m_char *byp;
  void *vp;
  void (*callp)();
  double *dp;
  double d;
  char c[4]; 
  char b[4];} 
  itis;

// exp10 is a math function. So is log. Neex to differentiate
#define exp10 ezp10


#define	FLAG_OF	0x80
#define	FLAG_CF	0x01
#define	FLAG_CA	0x40

#define xl (xl_it.w)
#define xr (xr_it.w)
#define w0 (w0_it.w)
#define w1 (w1_it.w)
#define wa (wa_it.w)
#define wb (wb_it.w)
#define wc (wc_it.w)
#define xs (xs_it.w)
#define ia (ia_it.w)
#define cp (cp_it.w)
#define ra (ra_it.d)
#define rp (w0_it.dp)
#define fl (fl_it.c[0])

itis xl_it;
itis xr_it;
itis w0_it;
itis w1_it;
itis wa_it;
itis wb_it;
itis wc_it;
itis xs_it;
itis ia_it;
itis cp_it;
itis ra_it;
itis fl_it;
word _rt_;

void (*goto_nextfunction)();
extern word goto_counter;


#define isgoodnum(valueya) (_rt_=fpclassify(valueya),((_rt_!= FP_NAN)&&(_rt_ != FP_INFINITE)))
//#define isgoodnum(valueya) 1

#define xt xl
#define xt_it xl_it
#define wa_l *((byte *)(&wa))
#define wb_l *((byte *)(&wb))
#define w0_l *(byte *)(&w0))

#define CFP_B	(8)
#define CFP_C	(8)
#define LOG_CFP_B 3
#define LOG_CFP_C 3
#define CFP_C_VAL	8
#define LOG_CFP_C 3
#define CFP_M_	9223372036854775807
//	%define	cfp_n_	64


//	flags
#define	FLAG_OF	0x80
#define	flag_cf	0x01
#define	flag_ca	0x40








#define C_CALL(new_func) {new_func(); }

#define C_POP() \
  *(xs_it.wp++)
#define C_TOP() \
  *(xs_it.wp)
#define C_PUSH(val)  *(--xs_it.wp) = val

typedef void (*voidcall());

#ifdef z_trace
void zzzz(word a,word b,char *s);
#endif


// C_GOTO returns with goto_nextfunction being the next function to call.  Generally, this is inside snobol-ish code where
// it is Assumed that there is a catch procedure such as a C_JSR behind the call that will keep looping things.
// So, generally, any C_JSR call from regular C can startup C
// However, C_JMS doesn't do that. Because of this, regular C can call via C_JSR, and not C_JMS
// C_JMS is a throwback reference to the PDP/8 architecture, that didn't have a stack, but instead would write the 
// return pointer to the JMS address and set the PC to the address + 1.  A return was a JMP I (calling_address)
// This is very similar to the "n" type calls for spitbol, where the stack is not used.
// Anyways, C_GOTO makes it easy to jump from C mini-function to C minifunction, which works for decoding the minimal assembly.

//#define C_GOTO(new_func) { goto_nextfunction = new_func; return;}
// ^^^ the above function is good for production
#define C_GOTO(new_func) { if ((goto_counter++) &31) { new_func();} else goto_nextfunction = new_func; return;}
// ^^ this function is good for troubleshooting, as the stack will hold a list trailing the gotos in most cases.

// C_JSR - this sets up a loop that will handle the goto functions until goto_nextfunction is null
#define C_JSR(procedureya) \
  {C_CALL(procedureya); while (goto_nextfunction) { goto_nextfunction(); }} 


// These variants of C_JSR allow for alternate exits from a JSR call.  This is built in minimal by using the prc r,<n> command where <n> is the number of alternate calls.
#define C_JSR_1(procedureya,nogo) \
  {C_CALL(procedureya); while (goto_nextfunction) { goto_nextfunction(); } if (_rt_) nogo; }

#define C_JSR_2(procedureya,other1,other2) \
  {C_CALL(procedureya); while (goto_nextfunction) { goto_nextfunction(); } if(_rt_==1) other1; if (_rt_==2) other2; }
  
#define C_JSR_3(procedureya,other1,other2,other3) \
  {C_CALL(procedureya); while (goto_nextfunction) { goto_nextfunction(); } if(_rt_==1) other1; if (_rt_==2) other2; \
    if (_rt_==3) other3;}
    
#define C_JSR_4(procedureya,other1,other2,other3,other4) \
  {C_CALL(procedureya); while (goto_nextfunction) { goto_nextfunction(); } if(_rt_==1) other1; if (_rt_==2) other2; \
    if (_rt_==3) other3;    if (_rt_==4) other4;}
/* C_ERR and C_GOTO are the parameters other... for the C_JSR variants */

#define C_JSR_5(procedureya,other1,other2,other3,other4,other5) \
  {C_CALL(procedureya); while (goto_nextfunction) { goto_nextfunction(); } if(_rt_==1) other1; if (_rt_==2) other2; \
    if (_rt_==3) other3;    if (_rt_==4) other4; if (_rt_==5) other5;}
/* C_ERR and C_GOTO are the parameters other... for the C_JSR variants */

#define C_JSR_6(procedureya,other1,other2,other3,other4,other5,other6) \
  {C_CALL(procedureya); while (goto_nextfunction) { goto_nextfunction(); } if(_rt_==1) other1; if (_rt_==2) other2; \
    if (_rt_==3) other3;    if (_rt_==4) other4; if (_rt_==5) other5; if (_rt_==6) other6;}

#define C_JSR_7(procedureya,other1,other2,other3,other4,other5,other6,other7) \
  {C_CALL(procedureya); while (goto_nextfunction) { goto_nextfunction(); } if(_rt_==1) other1; if (_rt_==2) other2; \
    if (_rt_==3) other3;    if (_rt_==4) other4; if (_rt_==5) other5; if (_rt_==6) other6;if (_rt_==7) other7;}

    
#define C_JSR_8(procedureya,other1,other2,other3,other4,other5,other6,other7,other8) \
  {C_CALL(procedureya); while (goto_nextfunction) { goto_nextfunction(); } if(_rt_==1) other1; if (_rt_==2) other2; \
    if (_rt_==3) other3;    if (_rt_==4) other4; if (_rt_==5) other5; if (_rt_==6) other6;if (_rt_==7) other7; \
    if (_rt_==8) other8;}
	    
    
/* C_ERR and C_GOTO are the parameters other... for the C_JSR variants */


void err_();
#define C_ERR(errnumber) {_rt_ = errnumber;C_GOTO(err_);} 


/* error base - probably wrong */
#define C_ERB(errnumber) {_rt_ = errnumber;C_GOTO(err_);}

#define C_EXIT(par) { goto_nextfunction = NULL;  _rt_ = par; return;}




// JMS (non stack calls)
// JMS calls store a return point in the v.prc_[<procedure number>] location
// where [procedure number] is the type n (non recursive) call number.
// JMS calls might not return to the caller, if there are error functions that are global
// as I understand it.
// Exits are performed with C_NEXIT(<proceure number>,return value)

#define C_JMS(procedureya,procedure_number,continuation_function) { \
 v.prc_[procedure_number] = continuation_function; \
 goto_nextfunction = procedureya; _rt_=0; return;}



// C_JMS_HANDLE_<n> handles the alternate gotos for a N - nonrecursive call.
// Generally the code (slightly ineffecient) goes like this:
//
//    jsr	non_recursive_example
//    ppm	other1_goto
//    ppm	other2_goto
//    err	other3_error_number
//
// converts to
//
//   extern void l_63787();
//   C_JMS(non_recursive_example,P_PRC_NON_RECURSIVE_EXAMPLE,l_63787);
//   } /* previous function whatever */
//
//  void l_63787() {
//  C_JMS_HANDLE_3(non_recursive_example,C_GOTO(other1_goto),C_GOTO(other2_goto),CERR(other3_error_number);
//
//

#define C_JMS_HANDLE_1(procedureya,nogo) {if (_rt_) nogo;}

#define C_JMS_HANDLE_2(procedureya,other1,other2) {if(_rt_==1) other1; if (_rt_==2) other2; }

#define C_JMS_HANDLE_3(procedureya,other1,other2,other3) {if(_rt_==1) other1; if (_rt_==2) other2; \
    if (_rt_==3) other3;}   
    
#define C_JMS_HANDLE_4(procedureya,other1,other2,other3,other4) {if(_rt_==1) other1; if (_rt_==2) other2; \
   if (_rt_==3) other3;    if (_rt_==4) other4;}

        
#define C_JMS_HANDLE_5(procedureya,other1,other2,other3,other4,other5) {if(_rt_==1) other1; if (_rt_==2) other2; \
   if (_rt_==3) other3;    if (_rt_==4) other4; if (_rt_==5) other5;}

#define C_JMS_HANDLE_6(procedureya,other1,other2,other3,other4,other5,other6) {if(_rt_==1) other1; if (_rt_==2) other2; \
   if (_rt_==3) other3;    if (_rt_==4) other4; if (_rt_==5) other5; if (_rt_==6) other6;}

#define C_JMS_HANDLE_7(procedureya,other1,other2,other3,other4,other5,other6,other7) {if(_rt_==1) other1; if (_rt_==2) other2; \
   if (_rt_==3) other3;    if (_rt_==4) other4; if (_rt_==5) other5; if (_rt_==6) other6;if (_rt_==7) other7;}

#define C_JMS_HANDLE_8(procedureya,other1,other2,other3,other4,other5,other6,other7,other8) {if(_rt_==1) other1; if (_rt_==2) other2; \
   if (_rt_==3) other3;    if (_rt_==4) other4; if (_rt_==5) other5; if (_rt_==6) other6;if (_rt_==7) other7; \
   if (_rt_==8) other8;}
	 

#define C_NEXIT(procedure_number,par) { goto_nextfunction = v.prc_[procedure_number];  _rt_ = par; return;}






extern void error_found(word errornum);
extern void ezzor();


/* main string compare */
#define C_CMC(one_it,two_it,len_it,ltl,gtl) \
{long test; long i=0; while (i<len_it.w) {  \
  if (test=   (one_it.chp[i] - two_it.chp[i])) {  \
    one_it.w=0;two_it.w=0; if (test>0) C_GOTO(gtl) else C_GOTO(ltl); \
    } \
  i++; \
  } \
one_it.w=0;two_it.w=0; \
}





/* main string compare differ */
#define C_CMC_DIFFER(one_it,two_it,len_it,different) \
{long test; long i=0; while (i<len_it.w) {  \
  if (test=   (one_it.chp[i] - two_it.chp[i])) {  \
    one_it.w=0;two_it.w=0; C_GOTO(different) \
    } \
  i++; \
  } \
one_it.w=0;two_it.w=0; }



extern word find_elab(word check);


/* end of c_64.h */
