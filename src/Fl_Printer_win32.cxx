/*
 *  fl_native_printer_win32.cxx
 */

#ifdef WIN32

#include <FL/fl_ask.H>

extern HWND fl_window;

Fl_Printer::Fl_Printer(void)
{
  hPr = NULL;
}

static void WIN_SetupPrinterDeviceContext(HDC prHDC)
{
  if ( !prHDC ) return;
  
  fl_window = 0;
  fl_gc = prHDC;
  SetMapMode(prHDC, MM_ANISOTROPIC);
  SetTextAlign(prHDC, TA_BASELINE|TA_LEFT);
  SetBkMode(prHDC, TRANSPARENT);	
  // this matches 720 logical units to the number of device units in 10 inches of paper
  // thus the logical unit is the point (= 1/72 inch)
  SetWindowExtEx(prHDC, 720, 720, NULL);
  SetViewportExtEx(prHDC, 10*GetDeviceCaps(prHDC, LOGPIXELSX), 10*GetDeviceCaps(prHDC, LOGPIXELSY), NULL);
}


int Fl_Printer::start_job (int pagecount, int *frompage, int *topage)
// returns 0 iff OK
{
  DWORD       commdlgerr;
  DOCINFO     di;
  char        docName [256];
  int err = 0;
  
  abortPrint = FALSE;
  memset (&pd, 0, sizeof (PRINTDLG));
  pd.lStructSize = sizeof (PRINTDLG);
  pd.hwndOwner = GetForegroundWindow();
  pd.Flags = PD_RETURNDC | PD_USEDEVMODECOPIESANDCOLLATE | PD_NOSELECTION;
  pd.nMinPage = 1;
  pd.nMaxPage = pagecount;
  if (PrintDlg (&pd) != 0) {
    hPr = pd.hDC;
    if (hPr != NULL) {
      WIN_SetupPrinterDeviceContext (hPr);
      strcpy (docName, "FLTK");
      memset(&di, 0, sizeof(DOCINFO));
      di.cbSize = sizeof (DOCINFO);
      di.lpszDocName = (LPCSTR) docName;
      prerr = StartDoc (hPr, &di);
      if (prerr < 1) {
	abortPrint = TRUE;
	fl_alert ("StartDoc error %d", prerr);
	err = 1;
      }
    } else {
      commdlgerr = CommDlgExtendedError ();
      fl_alert ("Unable to create print context, error %lu",
		(unsigned long) commdlgerr);
      err = 1;
    }
  } else {
    err = 1;
  }
  if(!err) {
    if((pd.Flags & PD_PAGENUMS) != 0 ) {
      if (frompage) *frompage = pd.nFromPage;
      if (topage) *topage = pd.nToPage;
    }
    else {
      if (frompage) *frompage = 1;
      if (topage) *topage = pagecount;
    }
    x_offset = 0;
    y_offset = 0;
  }
  return err;
}

void Fl_Printer::end_job (void)
{
  if (hPr != NULL) {
    if (! abortPrint) {
      prerr = EndDoc (hPr);
      if (prerr < 0) {
	fl_alert ("EndDoc error %d", prerr);
      }
    }
    DeleteDC (hPr);
    if (pd.hDevMode != NULL) {
      GlobalFree (pd.hDevMode);
    }
    if (pd.hDevNames != NULL) {
      GlobalFree (pd.hDevNames);
    }
  }
}

void Fl_Printer::absolute_printable_rect(int *x, int *y, int *w, int *h)
{
  POINT         physPageSize;
  POINT         pixelsPerInch;
    
  if (hPr == NULL) return;
  SetWindowOrgEx(fl_gc, 0, 0, NULL);
  
  physPageSize.x = GetDeviceCaps(hPr, HORZRES);
  physPageSize.y = GetDeviceCaps(hPr, VERTRES);
  DPtoLP(hPr, &physPageSize, 1);
  *w = physPageSize.x + 1;
  *h = physPageSize.y + 1;
  pixelsPerInch.x = GetDeviceCaps(hPr, LOGPIXELSX);
  pixelsPerInch.y = GetDeviceCaps(hPr, LOGPIXELSY);
  DPtoLP(hPr, &pixelsPerInch, 1);
  left_margin = (pixelsPerInch.x / 4);
  *w -= (pixelsPerInch.x / 2);
  top_margin = (pixelsPerInch.y / 4);
  *h -= (pixelsPerInch.y / 2);
  
  *x = left_margin;
  *y = top_margin;
  origin(x_offset, y_offset);
}

void Fl_Printer::margins(int *left, int *top, int *right, int *bottom)
{
  int x, y, w, h;
  absolute_printable_rect(&x, &y, &w, &h);
  if (left) *left = x;
  if (top) *top = y;
  if (right) *right = x;
  if (bottom) *bottom = y;
}

int Fl_Printer::printable_rect(int *w, int *h)
{
  int x, y;
  absolute_printable_rect(&x, &y, w, h);
  return 0;
}

int Fl_Printer::start_page (void)
{
  int  rsult, w, h;
  
  rsult = 0;
  if (hPr != NULL) {
    WIN_SetupPrinterDeviceContext (hPr);
    prerr = StartPage (hPr);
    if (prerr < 0) {
      fl_alert ("StartPage error %d", prerr);
      rsult = 1;
    }
    printable_rect(&w, &h);
    origin(0, 0);
    image_list_ = NULL;
    fl_clip_region(0);
    fl_isprintcontext = true;
  }
  return rsult;
}

void Fl_Printer::origin (int deltax, int deltay)
{
  SetWindowOrgEx(fl_gc, - left_margin - deltax, - top_margin - deltay, NULL);
  x_offset = deltax;
  y_offset = deltay;
}

void Fl_Printer::scale (float scalex, float scaley)
{
  int w, h;
  SetWindowExtEx(fl_gc, (int)(720 / scalex + 0.5), (int)(720 / scaley + 0.5), NULL);
  printable_rect(&w, &h);
  origin(0, 0);
}

int Fl_Printer::end_page (void)
{
  int  rsult;
  
  delete_image_list();
  fl_isprintcontext = false;
  rsult = 0;
  if (hPr != NULL) {
    prerr = EndPage (hPr);
    if (prerr < 0) {
      abortPrint = TRUE;
      fl_alert ("EndPage error %d", prerr);
      rsult = 1;
    }
  }
  return rsult;
}

#endif // WIN32

