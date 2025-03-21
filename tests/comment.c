/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggTheora SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE Theora SOURCE CODE IS COPYRIGHT (C) 2002-2009                *
 * by the Xiph.Org Foundation https://www.xiph.org/                 *
 *                                                                  *
 ********************************************************************

  function: routines for validating comment header code

 ********************************************************************/

#include <theora/theoradec.h>

#include <string.h>
#include "tests.h"

#define ARTIST1 "Bug-eyed Fish"
#define ARTIST2 "VJ Fugu"
#define COPYRIGHT "Copyright (C) 2005. Some Rights Reserved."
#define LICENSE "Creative Commons Attribution-ShareAlike 2.5"

static int
test_comments ()
{
  th_comment tc;
  int n;
  char * value;

  INFO ("+ Initializing th_comment");
  th_comment_init (&tc);

  INFO ("+ Adding ARTIST1");
  th_comment_add (&tc, "ARTIST=" ARTIST1);

  INFO ("+ Adding LICENSE by tag");
  th_comment_add_tag (&tc, "LICENSE", LICENSE);

  INFO ("+ Adding ARTIST2 by tag");
  th_comment_add_tag (&tc, "ARTIST", ARTIST2);

  INFO ("+ Querying value of LICENSE");
  value = th_comment_query (&tc, "LICENSE", 0);
  printf("foo %s\n", value);

  if (strcmp (value, LICENSE))
    FAIL ("Incorrect value for LICENSE");

  INFO ("+ Querying count of ARTIST comments");
  n = th_comment_query_count (&tc, "ARTIST");

  if (n != 2)
    FAIL ("Incorrect count of ARTIST comments");

  INFO ("+ Querying value of ARTIST index 0");
  value = th_comment_query (&tc, "ARTIST", 0);
  if (strcmp (value, ARTIST1))
    FAIL ("Incorrect value for ARTIST index 0");

  INFO ("+ Querying value of ARTIST index 1");
  value = th_comment_query (&tc, "ARTIST", 1);
  if (strcmp (value, ARTIST2))
    FAIL ("Incorrect value for ARTIST index 1");

  INFO ("+ Querying value of ARTIST index 2 (out of bounds)");
  value = th_comment_query (&tc, "ARTIST", 2);
  if (value != NULL)
    FAIL ("Non-NULL value for ARTIST index 2 (out of bounds)");

  INFO ("+ Querying value of UNDEF index 7 (tag not defined)");
  value = th_comment_query (&tc, "UNDEF", 7);
  if (value != NULL)
    FAIL ("Non-NULL value for UNDEF index 7 (tag not defined)");

  INFO ("+ Clearing th_comment");
  th_comment_clear (&tc);

  return 0;
}

int main(int argc, char *argv[])
{
  test_comments ();

  exit (0);
}
