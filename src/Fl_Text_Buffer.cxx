//
// "$Id$"
//
// Copyright 2001-2009 by Bill Spitzak and others.
// Original code Copyright Mark Edel.  Permission to distribute under
// the LGPL for the FLTK library granted by Mark Edel.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#include <stdio.h>
#include <stdlib.h>
#include <FL/fl_utf8.h>
#include "flstring.h"
#include <ctype.h>
#include <FL/Fl.H>
#include <FL/Fl_Text_Buffer.H>

/*
 This file is based on a port of NEdit to FLTK many years ago. NEdit at that
 point was already stretched beyond the task it was designed for which explains
 why the source code is sometimes pretty convoluted. It still is a nice widget
 for FLTK.

 With the introduction of Unicode and UTF-8, Fl_Text_... has to go into a whole
 new generation of code. Originally designed for monspaced fonts only, many
 features make les sense in the multibyte and multiwdth world of UTF-8.
 
 Columns are a good example. There is simply no such thing.
 
 Rectangular selections pose a real problem.
 
 Using multiple spaces to emulate tab stops will no longer work.
 
 And constantly recalculating character widths is just much too expensive.
 
 But nevertheless, we will get ths widget rolling again ;-)
 
 */


#ifndef min

static int max(int i1, int i2)
{
  return i1 >= i2 ? i1 : i2;
}

static int min(int i1, int i2)
{
  return i1 <= i2 ? i1 : i2;
}

#endif

static const char *ControlCodeTable[32] = {
  "nul", "soh", "stx", "etx", "eot", "enq", "ack", "bel",
  "bs", "ht", "nl", "vt", "np", "cr", "so", "si",
  "dle", "dc1", "dc2", "dc3", "dc4", "nak", "syn", "etb",
  "can", "em", "sub", "esc", "fs", "gs", "rs", "us"
};

static char *undobuffer;
static int undobufferlength;
static Fl_Text_Buffer *undowidget;
static int undoat;		// points after insertion
static int undocut;		// number of characters deleted there
static int undoinsert;		// number of characters inserted
static int undoyankcut;		// length of valid contents of buffer, even if undocut=0

static void undobuffersize(int n)
{
  if (n > undobufferlength) {
    if (undobuffer) {
      do {
	undobufferlength *= 2;
      } while (undobufferlength < n);
      undobuffer = (char *) realloc(undobuffer, undobufferlength);
    } else {
      undobufferlength = n + 9;
      undobuffer = (char *) malloc(undobufferlength);
    }
  }
}


// unicode ok
Fl_Text_Buffer::Fl_Text_Buffer(int requestedSize, int preferredGapSize)
{
  mLength = 0;
  mPreferredGapSize = preferredGapSize;
  mBuf = (char *) malloc(requestedSize + mPreferredGapSize);
  mGapStart = 0;
  mGapEnd = mPreferredGapSize;
  mTabDist = 8;
  mUseTabs = 1;
  mPrimary.mSelected = 0;
  mPrimary.mStart = mPrimary.mEnd = 0;
  mSecondary.mSelected = 0;
  mSecondary.mStart = mSecondary.mEnd = 0;
  mHighlight.mSelected = 0;
  mHighlight.mStart = mHighlight.mEnd = 0;
  mModifyProcs = NULL;
  mCbArgs = NULL;
  mNModifyProcs = 0;
  mNPredeleteProcs = 0;
  mPredeleteProcs = NULL;
  mPredeleteCbArgs = NULL;
  mCursorPosHint = 0;
  mCanUndo = 1;
#ifdef PURIFY
  {
    int i;
    for (i = mGapStart; i < mGapEnd; i++)
      mBuf[i] = '.';
  }
#endif
}


// unicode ok
Fl_Text_Buffer::~Fl_Text_Buffer()
{
  free(mBuf);
  if (mNModifyProcs != 0) {
    delete[]mModifyProcs;
    delete[]mCbArgs;
  }
  if (mNPredeleteProcs != 0) {
    delete[]mPredeleteProcs;
    delete[]mPredeleteCbArgs;
  }
}


// This function copies verbose whatever is in front and after the gap into a
// single buffer.
// - unicode ok
char *Fl_Text_Buffer::text() const {
  char *t = (char *) malloc(mLength + 1);
  memcpy(t, mBuf, mGapStart);
  memcpy(&t[mGapStart], &mBuf[mGapEnd], mLength - mGapStart);
  t[mLength] = '\0';
  return t;
} 


// unicode ok, functions called have not been verified yet
void Fl_Text_Buffer::text(const char *t)
{
  call_predelete_callbacks(0, length());
  
  /* Save information for redisplay, and get rid of the old buffer */
  const char *deletedText = text();
  int deletedLength = mLength;
  free((void *) mBuf);
  
  /* Start a new buffer with a gap of mPreferredGapSize at the end */
  int insertedLength = strlen(t);
  mBuf = (char *) malloc(insertedLength + mPreferredGapSize);
  mLength = insertedLength;
  mGapStart = insertedLength;
  mGapEnd = mGapStart + mPreferredGapSize;
  memcpy(mBuf, t, insertedLength);
#ifdef PURIFY
  {
    int i;
    for (i = mGapStart; i < mGapEnd; i++)
      mBuf[i] = '.';
  }
#endif
  
  /* Zero all of the existing selections */
  update_selections(0, deletedLength, 0);
  
  /* Call the saved display routine(s) to update the screen */
  call_modify_callbacks(0, deletedLength, insertedLength, 0, deletedText);
  free((void *) deletedText);
}


// Creates a new buffer and copies verbose from around the gap.
// - unicode ok
char *Fl_Text_Buffer::text_range(int start, int end) const {
  char *s = NULL;
  
  /* Make sure start and end are ok, and allocate memory for returned string.
   If start is bad, return "", if end is bad, adjust it. */
  if (start < 0 || start > mLength)
  {
    s = (char *) malloc(1);
    s[0] = '\0';
    return s;
  }
  if (end < start) {
    int temp = start;
    start = end;
    end = temp;
  }
  if (end > mLength)
    end = mLength;
  int copiedLength = end - start;
  s = (char *) malloc(copiedLength + 1);
  
  /* Copy the text from the buffer to the returned string */
  if (end <= mGapStart) {
    memcpy(s, &mBuf[start], copiedLength);
  } else if (start >= mGapStart) {
    memcpy(s, &mBuf[start + (mGapEnd - mGapStart)], copiedLength);
  } else {
    int part1Length = mGapStart - start;
    memcpy(s, &mBuf[start], part1Length);
    memcpy(&s[part1Length], &mBuf[mGapEnd], copiedLength - part1Length);
  }
  s[copiedLength] = '\0';
  return s;
}


// TODO: we will need the same signature function to get bytes (style buffer)
// unicode ok
unsigned int Fl_Text_Buffer::at(int pos) const {
  if (pos < 0 || pos >= mLength)
    return '\0';
  const char *src = address(pos);
  return fl_utf8decode(src, 0, 0);
} 


// unicode ok, dependents not tested
void Fl_Text_Buffer::insert(int pos, const char *text)
{
  /* if pos is not contiguous to existing text, make it */
  if (pos > mLength)
    pos = mLength;
  if (pos < 0)
    pos = 0;
  
  /* Even if nothing is deleted, we must call these callbacks */
  call_predelete_callbacks(pos, 0);
  
  /* insert and redisplay */
  int nInserted = insert_(pos, text);
  mCursorPosHint = pos + nInserted;
  call_modify_callbacks(pos, 0, nInserted, 0, NULL);
}


// unicode ok, dependents not tested
void Fl_Text_Buffer::replace(int start, int end, const char *text)
{
  // Range check...
  if (!text)
    return;
  if (start < 0)
    start = 0;
  if (end > mLength)
    end = mLength;
  
  call_predelete_callbacks(start, end - start);
  const char *deletedText = text_range(start, end);
  remove_(start, end);
  int nInserted = insert_(start, text);
  mCursorPosHint = start + nInserted;
  call_modify_callbacks(start, end - start, nInserted, 0, deletedText);
  free((void *) deletedText);
}


// unicode ok, dependents not tested
void Fl_Text_Buffer::remove(int start, int end)
{
  /* Make sure the arguments make sense */
  if (start > end) {
    int temp = start;
    start = end;
    end = temp;
  }
  if (start > mLength)
    start = mLength;
  if (start < 0)
    start = 0;
  if (end > mLength)
    end = mLength;
  if (end < 0)
    end = 0;
  
  if (start == end)
    return;
  
  call_predelete_callbacks(start, end - start);
  /* Remove and redisplay */
  const char *deletedText = text_range(start, end);
  remove_(start, end);
  mCursorPosHint = start;
  call_modify_callbacks(start, end - start, 0, 0, deletedText);
  free((void *) deletedText);
}

void Fl_Text_Buffer::copy(Fl_Text_Buffer * fromBuf, int fromStart,
			  int fromEnd, int toPos)
{
  int copiedLength = fromEnd - fromStart;
  
  /* Prepare the buffer to receive the new text.  If the new text fits in
   the current buffer, just move the gap (if necessary) to where
   the text should be inserted.  If the new text is too large, reallocate
   the buffer with a gap large enough to accomodate the new text and a
   gap of mPreferredGapSize */
  if (copiedLength > mGapEnd - mGapStart)
    reallocate_with_gap(toPos, copiedLength + mPreferredGapSize);
  else if (toPos != mGapStart)
    move_gap(toPos);
  
  /* Insert the new text (toPos now corresponds to the start of the gap) */
  if (fromEnd <= fromBuf->mGapStart) {
    memcpy(&mBuf[toPos], &fromBuf->mBuf[fromStart], copiedLength);
  } else if (fromStart >= fromBuf->mGapStart) {
    memcpy(&mBuf[toPos],
	   &fromBuf->mBuf[fromStart +
			  (fromBuf->mGapEnd - fromBuf->mGapStart)],
	   copiedLength);
  } else {
    int part1Length = fromBuf->mGapStart - fromStart;
    memcpy(&mBuf[toPos], &fromBuf->mBuf[fromStart], part1Length);
    memcpy(&mBuf[toPos + part1Length],
	   &fromBuf->mBuf[fromBuf->mGapEnd], copiedLength - part1Length);
  }
  mGapStart += copiedLength;
  mLength += copiedLength;
  update_selections(toPos, 0, copiedLength);
}

int Fl_Text_Buffer::undo(int *cursorPos)
{
  if (undowidget != this || !undocut && !undoinsert && !mCanUndo)
    return 0;
  
  int ilen = undocut;
  int xlen = undoinsert;
  int b = undoat - xlen;
  
  if (xlen && undoyankcut && !ilen) {
    ilen = undoyankcut;
  }
  
  if (xlen && ilen) {
    undobuffersize(ilen + 1);
    undobuffer[ilen] = 0;
    char *tmp = strdup(undobuffer);
    replace(b, undoat, tmp);
    if (cursorPos)
      *cursorPos = mCursorPosHint;
    free(tmp);
  } else if (xlen) {
    remove(b, undoat);
    if (cursorPos)
      *cursorPos = mCursorPosHint;
  } else if (ilen) {
    undobuffersize(ilen + 1);
    undobuffer[ilen] = 0;
    insert(undoat, undobuffer);
    if (cursorPos)
      *cursorPos = mCursorPosHint;
    undoyankcut = 0;
  }
  
  return 1;
}


// unicode ok
void Fl_Text_Buffer::canUndo(char flag)
{
  mCanUndo = flag;
}

void Fl_Text_Buffer::tab_distance(int tabDist)
{
  /* First call the pre-delete callbacks with the previous tab setting 
   still active. */
  call_predelete_callbacks(0, mLength);
  
  /* Change the tab setting */
  mTabDist = tabDist;
  
  /* Force any display routines to redisplay everything (unfortunately,
   this means copying the whole buffer contents to provide "deletedText" */
  const char *deletedText = text();
  call_modify_callbacks(0, mLength, mLength, 0, deletedText);
  free((void *) deletedText);
}

void Fl_Text_Buffer::select(int start, int end)
{
  Fl_Text_Selection oldSelection = mPrimary;
  
  mPrimary.set(start, end);
  redisplay_selection(&oldSelection, &mPrimary);
}

void Fl_Text_Buffer::unselect()
{
  Fl_Text_Selection oldSelection = mPrimary;
  
  mPrimary.mSelected = 0;
  redisplay_selection(&oldSelection, &mPrimary);
}

int Fl_Text_Buffer::selection_position(int *start, int *end)
{
  return mPrimary.position(start, end);
}

char *Fl_Text_Buffer::selection_text()
{
  return selection_text_(&mPrimary);
}

void Fl_Text_Buffer::remove_selection()
{
  remove_selection_(&mPrimary);
}

void Fl_Text_Buffer::replace_selection(const char *text)
{
  replace_selection_(&mPrimary, text);
}

void Fl_Text_Buffer::secondary_select(int start, int end)
{
  Fl_Text_Selection oldSelection = mSecondary;
  
  mSecondary.set(start, end);
  redisplay_selection(&oldSelection, &mSecondary);
}

void Fl_Text_Buffer::secondary_unselect()
{
  Fl_Text_Selection oldSelection = mSecondary;
  
  mSecondary.mSelected = 0;
  redisplay_selection(&oldSelection, &mSecondary);
}

int Fl_Text_Buffer::secondary_selection_position(int *start, int *end)
{
  return mSecondary.position(start, end);
}

char *Fl_Text_Buffer::secondary_selection_text()
{
  return selection_text_(&mSecondary);
}

void Fl_Text_Buffer::remove_secondary_selection()
{
  remove_selection_(&mSecondary);
}

void Fl_Text_Buffer::replace_secondary_selection(const char *text)
{
  replace_selection_(&mSecondary, text);
}

void Fl_Text_Buffer::highlight(int start, int end)
{
  Fl_Text_Selection oldSelection = mHighlight;
  
  mHighlight.set(start, end);
  redisplay_selection(&oldSelection, &mHighlight);
}

void Fl_Text_Buffer::unhighlight()
{
  Fl_Text_Selection oldSelection = mHighlight;
  
  mHighlight.mSelected = 0;
  redisplay_selection(&oldSelection, &mHighlight);
}

int Fl_Text_Buffer::highlight_position(int *start, int *end)
{
  return mHighlight.position(start, end);
}

char *Fl_Text_Buffer::highlight_text()
{
  return selection_text_(&mHighlight);
}

void Fl_Text_Buffer::add_modify_callback(Fl_Text_Modify_Cb bufModifiedCB,
					 void *cbArg)
{
  Fl_Text_Modify_Cb *newModifyProcs =
  new Fl_Text_Modify_Cb[mNModifyProcs + 1];
  void **newCBArgs = new void *[mNModifyProcs + 1];
  for (int i = 0; i < mNModifyProcs; i++) {
    newModifyProcs[i + 1] = mModifyProcs[i];
    newCBArgs[i + 1] = mCbArgs[i];
  }
  if (mNModifyProcs != 0) {
    delete[]mModifyProcs;
    delete[]mCbArgs;
  }
  newModifyProcs[0] = bufModifiedCB;
  newCBArgs[0] = cbArg;
  mNModifyProcs++;
  mModifyProcs = newModifyProcs;
  mCbArgs = newCBArgs;
}

void Fl_Text_Buffer::
remove_modify_callback(Fl_Text_Modify_Cb bufModifiedCB, void *cbArg)
{
  int i, toRemove = -1;
  
  /* find the matching callback to remove */
  for (i = 0; i < mNModifyProcs; i++) {
    if (mModifyProcs[i] == bufModifiedCB && mCbArgs[i] == cbArg) {
      toRemove = i;
      break;
    }
  }
  if (toRemove == -1) {
    Fl::error
    ("Fl_Text_Buffer::remove_modify_callback(): Can't find modify CB to remove");
    return;
  }
  
  /* Allocate new lists for remaining callback procs and args (if
   any are left) */
  mNModifyProcs--;
  if (mNModifyProcs == 0) {
    mNModifyProcs = 0;
    delete[]mModifyProcs;
    mModifyProcs = NULL;
    delete[]mCbArgs;
    mCbArgs = NULL;
    return;
  }
  Fl_Text_Modify_Cb *newModifyProcs = new Fl_Text_Modify_Cb[mNModifyProcs];
  void **newCBArgs = new void *[mNModifyProcs];
  
  /* copy out the remaining members and free the old lists */
  for (i = 0; i < toRemove; i++) {
    newModifyProcs[i] = mModifyProcs[i];
    newCBArgs[i] = mCbArgs[i];
  }
  for (; i < mNModifyProcs; i++) {
    newModifyProcs[i] = mModifyProcs[i + 1];
    newCBArgs[i] = mCbArgs[i + 1];
  }
  delete[]mModifyProcs;
  delete[]mCbArgs;
  mModifyProcs = newModifyProcs;
  mCbArgs = newCBArgs;
}

void Fl_Text_Buffer::
add_predelete_callback(Fl_Text_Predelete_Cb bufPreDeleteCB, void *cbArg)
{
  Fl_Text_Predelete_Cb *newPreDeleteProcs =
  new Fl_Text_Predelete_Cb[mNPredeleteProcs + 1];
  void **newCBArgs = new void *[mNPredeleteProcs + 1];
  for (int i = 0; i < mNPredeleteProcs; i++) {
    newPreDeleteProcs[i + 1] = mPredeleteProcs[i];
    newCBArgs[i + 1] = mPredeleteCbArgs[i];
  }
  if (!mNPredeleteProcs != 0) {
    delete[]mPredeleteProcs;
    delete[]mPredeleteCbArgs;
  }
  newPreDeleteProcs[0] = bufPreDeleteCB;
  newCBArgs[0] = cbArg;
  mNPredeleteProcs++;
  mPredeleteProcs = newPreDeleteProcs;
  mPredeleteCbArgs = newCBArgs;
}

void Fl_Text_Buffer::
remove_predelete_callback(Fl_Text_Predelete_Cb bufPreDeleteCB, void *cbArg)
{
  int i, toRemove = -1;
  /* find the matching callback to remove */
  for (i = 0; i < mNPredeleteProcs; i++) {
    if (mPredeleteProcs[i] == bufPreDeleteCB &&
	mPredeleteCbArgs[i] == cbArg) {
      toRemove = i;
      break;
    }
  }
  if (toRemove == -1) {
    Fl::error
    ("Fl_Text_Buffer::remove_predelete_callback(): Can't find pre-delete CB to remove");
    return;
  }
  
  /* Allocate new lists for remaining callback procs and args (if
   any are left) */
  mNPredeleteProcs--;
  if (mNPredeleteProcs == 0) {
    mNPredeleteProcs = 0;
    delete[]mPredeleteProcs;
    mPredeleteProcs = NULL;
    delete[]mPredeleteCbArgs;
    mPredeleteCbArgs = NULL;
    return;
  }
  Fl_Text_Predelete_Cb *newPreDeleteProcs =
  new Fl_Text_Predelete_Cb[mNPredeleteProcs];
  void **newCBArgs = new void *[mNPredeleteProcs];
  
  /* copy out the remaining members and free the old lists */
  for (i = 0; i < toRemove; i++) {
    newPreDeleteProcs[i] = mPredeleteProcs[i];
    newCBArgs[i] = mPredeleteCbArgs[i];
  }
  for (; i < mNPredeleteProcs; i++) {
    newPreDeleteProcs[i] = mPredeleteProcs[i + 1];
    newCBArgs[i] = mPredeleteCbArgs[i + 1];
  }
  delete[]mPredeleteProcs;
  delete[]mPredeleteCbArgs;
  mPredeleteProcs = newPreDeleteProcs;
  mPredeleteCbArgs = newCBArgs;
}

char *Fl_Text_Buffer::line_text(int pos) const {
  return text_range(line_start(pos), line_end(pos));
} 

int Fl_Text_Buffer::line_start(int pos) const {
  if (!findchar_backward(pos, '\n', &pos))
    return 0;
  return pos + 1;
} 

int Fl_Text_Buffer::line_end(int pos) const {
  if (!findchar_forward(pos, '\n', &pos))
    pos = mLength;
  return pos;
} 

int Fl_Text_Buffer::word_start(int pos) const {
  // FIXME: character is ucs-4
  while (pos && (isalnum(at(pos)) || at(pos) == '_')) {
    pos--;
  } 
  // FIXME: character is ucs-4
  if (!(isalnum(at(pos)) || at(pos) == '_'))
    pos++;
  return pos;
}

int Fl_Text_Buffer::word_end(int pos) const {
  // FIXME: character is ucs-4
  while (pos < length() && (isalnum(at(pos)) || at(pos) == '_'))
  {
    pos++;
  } return pos;
}


// Expand from the byte representation into some readable text.
// Under unicode, this is not really needed because all characters should
// be prinatble one way or the other. But since we use this to (badly) simulate
// tabs, we can leave this here anyway.
// - unicode ok
int Fl_Text_Buffer::expand_character(int pos, int indent, char *outStr) const {
  const char *src = address(pos);
  return expand_character(src, indent, outStr, mTabDist);
}


// static function and counterpart to "character_width"
// - unicode ok
// FIXME: harmonise with new character_width(char*...) version
//
int Fl_Text_Buffer::expand_character(const char *src, int indent, char *outStr, int tabDist)
{
  char c = *src;
  /* Convert tabs to spaces */
  if (c == '\t') {
    int nSpaces = tabDist - (indent % tabDist);
    for (int i = 0; i < nSpaces; i++)
      outStr[i] = ' ';
    return nSpaces;
  }
  
  /* Convert control codes to readable character sequences */
  if (((unsigned char) c) <= 31) {
    sprintf(outStr, "<%s>", ControlCodeTable[(unsigned char) c]);
    return strlen(outStr);
  } else if (c == 127) {
    sprintf(outStr, "<del>");
    return 5;
  } else if ((c & 0x80) && !(c & 0x40)) {
#ifdef DEBUG
    fprintf(stderr, "%s:%d - Error in UTF-8 encoding!\n", __FILE__, __LINE__);
#endif
    *outStr = c;
    return 1;
  } else if (c & 0x80) {
    int i, n = fl_utf8len(c);
    for (i=0; i<n; i++) *outStr++ = *src++;
    return n;
  }
  
  /* Otherwise, just return the character */
  *outStr = c;
  return 1;
}


// This function takes a character and optionally converts it into a little
// string which will replace the character on screen. This function returns
// the number of bytes in the replacement string, but *not* the number of 
// bytes in the original character!
// - unicode ok
int Fl_Text_Buffer::character_width(const char *src, int indent, int tabDist)
{
  char c = *src;
  if ((c & 0x80) && (c & 0x40)) {       // first byte of UTF-8 sequence
    int len = fl_utf8len(c);
    int ret = 0;
    unsigned int ucs = fl_utf8decode(src, src+len, &ret);
    int width = fl_wcwidth_(ucs);       // FIXME
    // fprintf(stderr, "mk_wcwidth(%x) -> %d (%d, %d, %s)\n", ucs, width, len, ret, src);
    return width;
  }
  if ((c & 0x80) && !(c & 0x40)) {      // other byte of UTF-8 sequence
    return 0;
  }
  return 1; // FIXME: ouch!
  //return character_width(c, indent, tabDist);
}

#if 0
// FIXME: merge the following with the char* version above.
// but the question then is: how to reorganise expand_character()?
//
int Fl_Text_Buffer::character_width(const char    c, int indent, int tabDist)
{
  /* Note, this code must parallel that in Fl_Text_Buffer::ExpandCharacter */
  if (c == '\t') {
    return tabDist - (indent % tabDist);
  } else if (((unsigned char) c) <= 31) {
    return strlen(ControlCodeTable[(unsigned char) c]) + 2;
  } else if (c == 127) {
    return 5;
  } else if ((c & 0x80) && !(c & 0x40)) {
#ifdef DEBUG
    fprintf(stderr, "%s:%d - Error in UTF-8 encoding!\n", __FILE__, __LINE__);
#endif
    return 1;
  } else if (c & 0x80) {
    // return fl_utf8len(c);
    return 1;
  }
  return 1;
}
#endif

int Fl_Text_Buffer::count_displayed_characters(int lineStartPos,
					       int targetPos) const
{
  int charCount = 0;
  char expandedChar[FL_TEXT_MAX_EXP_CHAR_LEN];
  
  int pos = lineStartPos;
  while (pos < targetPos)
    charCount += expand_character(pos++, charCount, expandedChar);
  return charCount;
} 


// All values are number of bytes. 
// - unicode ok
int Fl_Text_Buffer::skip_displayed_characters(int lineStartPos, int nChars)
{
  int pos = lineStartPos;
  
  for (int charCount = 0; charCount < nChars && pos < mLength;) {
    const char *src = address(pos);
    char c = *src;
    if (c == '\n')
      return pos;
    charCount += character_width(src, charCount, mTabDist);
    pos += fl_utf8len(c);
  }
  return pos;
}

int Fl_Text_Buffer::count_lines(int startPos, int endPos) const {
  int gapLen = mGapEnd - mGapStart;
  int lineCount = 0;
  
  int pos = startPos;
  while (pos < mGapStart)
  {
    if (pos == endPos)
      return lineCount;
    if (mBuf[pos++] == '\n')
      lineCount++;
  } while (pos < mLength) {
    if (pos == endPos)
      return lineCount;
    if (mBuf[pos++ + gapLen] == '\n')
      lineCount++;
  }
  return lineCount;
}

int Fl_Text_Buffer::skip_lines(int startPos, int nLines)
{
  if (nLines == 0)
    return startPos;
  
  int gapLen = mGapEnd - mGapStart;
  int pos = startPos;
  int lineCount = 0;
  while (pos < mGapStart) {
    if (mBuf[pos++] == '\n') {
      lineCount++;
      if (lineCount == nLines)
	return pos;
    }
  }
  while (pos < mLength) {
    if (mBuf[pos++ + gapLen] == '\n') {
      lineCount++;
      if (lineCount >= nLines)
	return pos;
    }
  }
  return pos;
}

int Fl_Text_Buffer::rewind_lines(int startPos, int nLines)
{
  int pos = startPos - 1;
  if (pos <= 0)
    return 0;
  
  int gapLen = mGapEnd - mGapStart;
  int lineCount = -1;
  while (pos >= mGapStart) {
    if (mBuf[pos + gapLen] == '\n') {
      if (++lineCount >= nLines)
	return pos + 1;
    }
    pos--;
  }
  while (pos >= 0) {
    if (mBuf[pos] == '\n') {
      if (++lineCount >= nLines)
	return pos + 1;
    }
    pos--;
  }
  return 0;
}

int Fl_Text_Buffer::search_forward(int startPos, const char *searchString,
				   int *foundPos,
				   int matchCase) const 
{
  if (!searchString)
    return 0;
  int bp;
  const char *sp;
  while (startPos < length()) {
    bp = startPos;
    sp = searchString;
    do {
      if (!*sp) {
        *foundPos = startPos;
        return 1;
      }
      // FIXME: character is ucs-4
    } while ((matchCase ? at(bp++) == *sp++ :
              toupper(at(bp++)) == toupper(*sp++))
             && bp < length());
    startPos++;
  }
  return 0;
}

int Fl_Text_Buffer::search_backward(int startPos, const char *searchString,
				    int *foundPos,
				    int matchCase) const {
  if (!searchString)
    return 0;
  int bp;
  const char *sp;
  while (startPos > 0)
  {
    bp = startPos - 1;
    sp = searchString + strlen(searchString) - 1;
    do {
      if (sp < searchString) {
        *foundPos = bp + 1;
        return 1;
      }
      // FIXME: character is ucs-4
    } while ((matchCase ? at(bp--) == *sp-- :
              toupper(at(bp--)) == toupper(*sp--))
             && bp >= 0);
    startPos--;
  }
  return 0;
}

int Fl_Text_Buffer::findchars_forward(int startPos,
				      const char *searchChars,
				      int *foundPos) const {
  int gapLen = mGapEnd - mGapStart;
  const char *c;
  
  int pos = startPos;
  while (pos < mGapStart)
  {
    for (c = searchChars; *c != '\0'; c++) {
      if (mBuf[pos] == *c) {
        *foundPos = pos;
        return 1;
      }
    } pos++;
  }
  while (pos < mLength) {
    for (c = searchChars; *c != '\0'; c++) {
      if (mBuf[pos + gapLen] == *c) {
	*foundPos = pos;
	return 1;
      }
    }
    pos++;
  }
  *foundPos = mLength;
  return 0;
}

int Fl_Text_Buffer::findchars_backward(int startPos,
				       const char *searchChars,
				       int *foundPos) const {
  int gapLen = mGapEnd - mGapStart;
  const char *c;
  
  if (startPos == 0)
  {
    *foundPos = 0;
    return 0;
  }
  int pos = startPos == 0 ? 0 : startPos - 1;
  while (pos >= mGapStart) {
    for (c = searchChars; *c != '\0'; c++) {
      if (mBuf[pos + gapLen] == *c) {
	*foundPos = pos;
	return 1;
      }
    }
    pos--;
  }
  while (pos >= 0) {
    for (c = searchChars; *c != '\0'; c++) {
      if (mBuf[pos] == *c) {
	*foundPos = pos;
	return 1;
      }
    }
    pos--;
  }
  *foundPos = 0;
  return 0;
}

int Fl_Text_Buffer::insert_(int pos, const char *text)
{
  int insertedLength = strlen(text);
  
  /* Prepare the buffer to receive the new text.  If the new text fits in
   the current buffer, just move the gap (if necessary) to where
   the text should be inserted.  If the new text is too large, reallocate
   the buffer with a gap large enough to accomodate the new text and a
   gap of mPreferredGapSize */
  if (insertedLength > mGapEnd - mGapStart)
    reallocate_with_gap(pos, insertedLength + mPreferredGapSize);
  else if (pos != mGapStart)
    move_gap(pos);
  
  /* Insert the new text (pos now corresponds to the start of the gap) */
  memcpy(&mBuf[pos], text, insertedLength);
  mGapStart += insertedLength;
  mLength += insertedLength;
  update_selections(pos, 0, insertedLength);
  
  if (mCanUndo) {
    if (undowidget == this && undoat == pos && undoinsert) {
      undoinsert += insertedLength;
    } else {
      undoinsert = insertedLength;
      undoyankcut = (undoat == pos) ? undocut : 0;
    }
    undoat = pos + insertedLength;
    undocut = 0;
    undowidget = this;
  }
  
  return insertedLength;
}

void Fl_Text_Buffer::remove_(int start, int end)
{
  /* if the gap is not contiguous to the area to remove, move it there */
  
  if (mCanUndo) {
    if (undowidget == this && undoat == end && undocut) {
      undobuffersize(undocut + end - start + 1);
      memmove(undobuffer + end - start, undobuffer, undocut);
      undocut += end - start;
    } else {
      undocut = end - start;
      undobuffersize(undocut);
    }
    undoat = start;
    undoinsert = 0;
    undoyankcut = 0;
    undowidget = this;
  }
  
  if (start > mGapStart) {
    if (mCanUndo)
      memcpy(undobuffer, mBuf + (mGapEnd - mGapStart) + start,
	     end - start);
    move_gap(start);
  } else if (end < mGapStart) {
    if (mCanUndo)
      memcpy(undobuffer, mBuf + start, end - start);
    move_gap(end);
  } else {
    int prelen = mGapStart - start;
    if (mCanUndo) {
      memcpy(undobuffer, mBuf + start, prelen);
      memcpy(undobuffer + prelen, mBuf + mGapEnd, end - start - prelen);
    }
  }
  
  /* expand the gap to encompass the deleted characters */
  mGapEnd += end - mGapStart;
  mGapStart -= mGapStart - start;
  
  /* update the length */
  mLength -= end - start;
  
  /* fix up any selections which might be affected by the change */
  update_selections(start, end - start, 0);
}


// simple setter
// Unicode safe
void Fl_Text_Selection::set(int startpos, int endpos)
{
  mSelected = startpos != endpos;
  mStart = min(startpos, endpos);
  mEnd = max(startpos, endpos);
}


// simple getter
// Unicode safe
int Fl_Text_Selection::position(int *startpos, int *endpos) const {
  if (!mSelected)
    return 0;
  *startpos = mStart;
  *endpos = mEnd;
  
  return 1;
} 


// unicode safe
int Fl_Text_Selection::includes(int pos) const {
  return (selected() && pos >= start() && pos < end() );
} 

char *Fl_Text_Buffer::selection_text_(Fl_Text_Selection * sel) const {
  int start, end;
  
  /* If there's no selection, return an allocated empty string */
  if (!sel->position(&start, &end))
  {
    char *s = (char *) malloc(1);
    *s = '\0';
    return s;
  }
  
  /* If the selection is not rectangular, return the selected range */
  return text_range(start, end);
}

void Fl_Text_Buffer::remove_selection_(Fl_Text_Selection * sel)
{
  int start, end;
  
  if (!sel->position(&start, &end))
    return;
  remove(start, end);
  //undoyankcut = undocut;
}


void Fl_Text_Buffer::replace_selection_(Fl_Text_Selection * sel,
					const char *text)
{
  Fl_Text_Selection oldSelection = *sel;
  
  /* If there's no selection, return */
  int start, end;
  if (!sel->position(&start, &end))
    return;
  
  /* Do the appropriate type of replace */
  replace(start, end, text);
  
  /* Unselect (happens automatically in BufReplace, but BufReplaceRect
   can't detect when the contents of a selection goes away) */
  sel->mSelected = 0;
  redisplay_selection(&oldSelection, sel);
}


void Fl_Text_Buffer::call_modify_callbacks(int pos, int nDeleted,
					   int nInserted, int nRestyled,
					   const char *deletedText) const {
  for (int i = 0; i < mNModifyProcs; i++)
    (*mModifyProcs[i]) (pos, nInserted, nDeleted, nRestyled,
			deletedText, mCbArgs[i]);
} 


void Fl_Text_Buffer::call_predelete_callbacks(int pos, int nDeleted) const {
  for (int i = 0; i < mNPredeleteProcs; i++)
    (*mPredeleteProcs[i]) (pos, nDeleted, mPredeleteCbArgs[i]);
} 


void Fl_Text_Buffer::redisplay_selection(Fl_Text_Selection *
					   oldSelection,
					   Fl_Text_Selection *
					   newSelection) const
{
  int oldStart, oldEnd, newStart, newEnd, ch1Start, ch1End, ch2Start,
  ch2End;
  
  /* If either selection is rectangular, add an additional character to
   the end of the selection to request the redraw routines to wipe out
   the parts of the selection beyond the end of the line */
  oldStart = oldSelection->mStart;
  newStart = newSelection->mStart;
  oldEnd = oldSelection->mEnd;
  newEnd = newSelection->mEnd;
  
  /* If the old or new selection is unselected, just redisplay the
   single area that is (was) selected and return */
  if (!oldSelection->mSelected && !newSelection->mSelected)
    return;
  if (!oldSelection->mSelected)
  {
    call_modify_callbacks(newStart, 0, 0, newEnd - newStart, NULL);
    return;
  }
  if (!newSelection->mSelected) {
    call_modify_callbacks(oldStart, 0, 0, oldEnd - oldStart, NULL);
    return;
  }
  
  /* If the selections are non-contiguous, do two separate updates
   and return */
  if (oldEnd < newStart || newEnd < oldStart) {
    call_modify_callbacks(oldStart, 0, 0, oldEnd - oldStart, NULL);
    call_modify_callbacks(newStart, 0, 0, newEnd - newStart, NULL);
    return;
  }
  
  /* Otherwise, separate into 3 separate regions: ch1, and ch2 (the two
   changed areas), and the unchanged area of their intersection,
   and update only the changed area(s) */
  ch1Start = min(oldStart, newStart);
  ch2End = max(oldEnd, newEnd);
  ch1End = max(oldStart, newStart);
  ch2Start = min(oldEnd, newEnd);
  if (ch1Start != ch1End)
    call_modify_callbacks(ch1Start, 0, 0, ch1End - ch1Start, NULL);
  if (ch2Start != ch2End)
    call_modify_callbacks(ch2Start, 0, 0, ch2End - ch2Start, NULL);
}

void Fl_Text_Buffer::move_gap(int pos)
{
  int gapLen = mGapEnd - mGapStart;
  
  if (pos > mGapStart)
    memmove(&mBuf[mGapStart], &mBuf[mGapEnd], pos - mGapStart);
  else
    memmove(&mBuf[pos + gapLen], &mBuf[pos], mGapStart - pos);
  mGapEnd += pos - mGapStart;
  mGapStart += pos - mGapStart;
}

void Fl_Text_Buffer::reallocate_with_gap(int newGapStart, int newGapLen)
{
  char *newBuf = (char *) malloc(mLength + newGapLen);
  int newGapEnd = newGapStart + newGapLen;
  
  if (newGapStart <= mGapStart) {
    memcpy(newBuf, mBuf, newGapStart);
    memcpy(&newBuf[newGapEnd], &mBuf[newGapStart],
	   mGapStart - newGapStart);
    memcpy(&newBuf[newGapEnd + mGapStart - newGapStart],
	   &mBuf[mGapEnd], mLength - mGapStart);
  } else {			/* newGapStart > mGapStart */
    memcpy(newBuf, mBuf, mGapStart);
    memcpy(&newBuf[mGapStart], &mBuf[mGapEnd], newGapStart - mGapStart);
    memcpy(&newBuf[newGapEnd],
	   &mBuf[mGapEnd + newGapStart - mGapStart],
	   mLength - newGapStart);
  }
  free((void *) mBuf);
  mBuf = newBuf;
  mGapStart = newGapStart;
  mGapEnd = newGapEnd;
#ifdef PURIFY
  {
    int i;
    for (i = mGapStart; i < mGapEnd; i++)
      mBuf[i] = '.';
  }
#endif
}

void Fl_Text_Buffer::update_selections(int pos, int nDeleted,
				       int nInserted)
{
  mPrimary.update(pos, nDeleted, nInserted);
  mSecondary.update(pos, nDeleted, nInserted);
  mHighlight.update(pos, nDeleted, nInserted);
}


// unicode safe, assuming the arguments are on character boundaries
void Fl_Text_Selection::update(int pos, int nDeleted, int nInserted)
{
  if (!mSelected || pos > mEnd)
    return;
  if (pos + nDeleted <= mStart) {
    mStart += nInserted - nDeleted;
    mEnd += nInserted - nDeleted;
  } else if (pos <= mStart && pos + nDeleted >= mEnd) {
    mStart = pos;
    mEnd = pos;
    mSelected = 0;
  } else if (pos <= mStart && pos + nDeleted < mEnd) {
    mStart = pos;
    mEnd = nInserted + mEnd - nDeleted;
  } else if (pos < mEnd) {
    mEnd += nInserted - nDeleted;
    if (mEnd <= mStart)
      mSelected = 0;
  }
}

int Fl_Text_Buffer::findchar_forward(int startPos, unsigned searchChar,
				     int *foundPos) const {
  if (startPos < 0 || startPos >= mLength)
  {
    *foundPos = mLength;
    return 0;
  }
  
  int pos = startPos;
  while (pos < mGapStart) {
    if (mBuf[pos] == searchChar) {
      *foundPos = pos;
      return 1;
    }
    pos++;
  }
  
  for (int gapLen = mGapEnd - mGapStart; pos < mLength; pos++) {
    if (mBuf[pos + gapLen] == searchChar) {
      *foundPos = pos;
      return 1;
    }
  }
  *foundPos = mLength;
  return 0;
}

int Fl_Text_Buffer::findchar_backward(int startPos, unsigned searchChar,
				      int *foundPos) const {
  
  if (startPos <= 0 || startPos > mLength)
  {
    *foundPos = 0;
    return 0;
  }
  
  int pos = startPos - 1;
  for (int gapLen = mGapEnd - mGapStart; pos >= mGapStart; pos--) {
    if (mBuf[pos + gapLen] == searchChar) {
      *foundPos = pos;
      return 1;
    }
  }
  
  for (; pos >= 0; pos--) {
    if (mBuf[pos] == searchChar) {
      *foundPos = pos;
      return 1;
    }
  }
  *foundPos = 0;
  return 0;
}


int Fl_Text_Buffer::insertfile(const char *file, int pos, int buflen)
{
  FILE *fp;
  if (!(fp = fl_fopen(file, "r")))
    return 1;
  char *buffer = new char[buflen];
  for (int r; (r = fread(buffer, 1, buflen - 1, fp)) > 0; pos += r) {
    buffer[r] = (char) 0;
    insert(pos, buffer);
  }
  
  int e = ferror(fp) ? 2 : 0;
  fclose(fp);
  delete[]buffer;
  return e;
}

int Fl_Text_Buffer::outputfile(const char *file, int start, int end,
			       int buflen)
{
  FILE *fp;
  if (!(fp = fl_fopen(file, "wb")))
    return 1;
  for (int n; (n = min(end - start, buflen)); start += n) {
    const char *p = text_range(start, start + n);
    int r = fwrite(p, 1, n, fp);
    free((void *) p);
    if (r != n)
      break;
  }
  
  int e = ferror(fp) ? 2 : 0;
  fclose(fp);
  return e;
}


//
// End of "$Id$".
//
