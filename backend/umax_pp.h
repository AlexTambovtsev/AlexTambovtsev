/* sane - Scanner Access Now Easy.
   Copyright (C) 2001 St�phane Voltz <svoltz@wanadoo.fr>
   This file is part of the SANE package.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA.

   As a special exception, the authors of SANE give permission for
   additional uses of the libraries contained in this release of SANE.

   The exception is that, if you link a SANE library with other files
   to produce an executable, this does not by itself cause the
   resulting executable to be covered by the GNU General Public
   License.  Your use of that executable is in no way restricted on
   account of linking the SANE library code into it.

   This exception does not, however, invalidate any other reasons why
   the executable file might be covered by the GNU General Public
   License.

   If you submit changes to SANE to the maintainers to be included in
   a subsequent release, you agree by submitting the changes that
   those changes may be distributed with this exception intact.

   If you write modifications of your own for SANE, it is your choice
   whether to permit this exception to apply to your modifications.
   If you do not wish that, delete this exception notice.

   This file implements a SANE backend for Umax PP flatbed scanners.  */

#ifndef umax_pp_h
#define umax_pp_h

#include <sys/types.h>
#include <sys/time.h>
#include <../include/sane/sanei_debug.h>


enum Umax_PP_Option
{
  OPT_NUM_OPTS = 0,

  OPT_MODE_GROUP,
  OPT_MODE,
  OPT_RESOLUTION,
  OPT_PREVIEW,
  OPT_GRAY_PREVIEW,

  OPT_GEOMETRY_GROUP,
  OPT_TL_X,			/* top-left x */
  OPT_TL_Y,			/* top-left y */
  OPT_BR_X,			/* bottom-right x */
  OPT_BR_Y,			/* bottom-right y */

  OPT_ENHANCEMENT_GROUP,

  OPT_LAMP_CONTROL,
  OPT_UTA_CONTROL,

  OPT_CUSTOM_GAMMA,		/* use custom gamma tables? */
  /* The gamma vectors MUST appear in the order gray, red, green,
     blue.  */
  OPT_GAMMA_VECTOR,
  OPT_GAMMA_VECTOR_R,
  OPT_GAMMA_VECTOR_G,
  OPT_GAMMA_VECTOR_B,

  OPT_MANUAL_GAIN,
  OPT_GRAY_GAIN,
  OPT_RED_GAIN,
  OPT_GREEN_GAIN,
  OPT_BLUE_GAIN,

  OPT_MANUAL_HIGHLIGHT,
  OPT_GRAY_HIGHLIGHT,
  OPT_RED_HIGHLIGHT,
  OPT_GREEN_HIGHLIGHT,
  OPT_BLUE_HIGHLIGHT,

  /* must come last: */
  NUM_OPTIONS
};

typedef union
{
  SANE_Word w;
  SANE_Word *wa;		/* word array */
  SANE_String s;
}
Option_Value;


typedef struct Umax_PP_Descriptor
{
  SANE_Device sane;

  SANE_String port;
  SANE_String ppdevice;

  SANE_Int max_res;
  SANE_Int max_h_size;
  SANE_Int max_v_size;
  long int buf_size;
  u_char revision;

  /* default values */
  SANE_Int gray_gain;
  SANE_Int red_gain;
  SANE_Int blue_gain;
  SANE_Int green_gain;
  SANE_Int gray_highlight;
  SANE_Int red_highlight;
  SANE_Int blue_highlight;
  SANE_Int green_highlight;
}
Umax_PP_Descriptor;

typedef struct Umax_PP_Device
{
  struct Umax_PP_Device *next;
  Umax_PP_Descriptor *desc;


  SANE_Option_Descriptor opt[NUM_OPTIONS];
  Option_Value val[NUM_OPTIONS];

  SANE_Int gamma_table[4][256];

  int state;
  int mode;

  int TopX;
  int TopY;
  int BottomX;
  int BottomY;

  int dpi;
  int gain;
  int color;
  int bpp;			/* bytes per pixel */
  int tw;			/* target width in pixels */
  int th;			/* target height in pixels */



  SANE_Byte *calibration;

  SANE_Byte *buf;
  long int bufsize;		/* size of read buffer                 */
  long int buflen;		/* size of data length in buffer       */
  long int bufread;		/* number of bytes read in the buffer  */
  long int read;		/* bytes read from previous start scan */

  SANE_Parameters params;
  SANE_Range dpi_range;
  SANE_Range x_range;
  SANE_Range y_range;

  SANE_Int gray_gain;
  SANE_Int red_gain;
  SANE_Int blue_gain;
  SANE_Int green_gain;

  SANE_Int gray_highlight;
  SANE_Int red_highlight;
  SANE_Int blue_highlight;
  SANE_Int green_highlight;
}
Umax_PP_Device;


#if (!defined __GNUC__ || __GNUC__ < 2 || \
     __GNUC_MINOR__ < (defined __cplusplus ? 6 : 4))

#define __PRETTY_FUNCTION__	"umax_pp"

#endif

#define DEBUG()		DBG(4, "%s(v%d.%d.%d-%s): line %d: debug exception\n", \
			  __PRETTY_FUNCTION__, V_MAJOR, V_MINOR,	\
			  UMAX_PP_BUILD, UMAX_PP_STATE, __LINE__)

#define ASSERT(cond)	if (!(cond))					\
			  {						\
                            DEBUG();					\
			    DBG(1, "ASSERT(%s) failed\n", STRINGIFY(cond)); \
			    DBG(1, "expect disaster...\n");\
			  }

/* Please note: ASSERT won't go away if you define NDEBUG, it just won't
 * output a message when ASSERT failes. So if "cond" does anything, it will
 * be executed, even if NDEBUG is defined... 
 */


#endif /* umax_pp_h */
