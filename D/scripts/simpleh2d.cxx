
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *in_path;
char *out_path;

unsigned int ifdefs = 0;

const int TE_NO_WORD = 1;

typedef struct {
  char *srch, *repl;
  int flags, len;
} TEntry;

TEntry tlut[] = {
  { "AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER", "" },
  { "AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER", "" },
  { "AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER", "" },
  { "AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER", "" },
  { "CG_EXTERN", "extern (C)" },
  { "CG_EXTERN_C_BEGIN", "" },
  { "CG_EXTERN_C_END", "" },
  { "const", "" },
  { "long long", "long" },
  { "long", "int" },
  { "typedef enum", "alias" },
  { "typedef struct", "alias" },
  { "unsigned char", "ubyte" },
  { "unsigned int", "uint" },
  { "unsigned long long", "ulong" },
  { "unsigned long", "uint" },
  { "unsigned short", "ushort" },
};
int ntlut = sizeof(tlut)/sizeof(TEntry);

void initTLut() {
  int i;
  for (i=0; i<ntlut; i++) {
    tlut[i].len = strlen(tlut[i].srch);
  }
}

const char sTAlpha[] = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char sTAlnum[] = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456790";
const char sDigit[] = "123456790";
const char sNum[] = "123456790.eExXlL";

int findInList(char *s) {
  int i;
  // ++ please put a binary search function in here!
  for (i=0; i<ntlut; i++) {
    TEntry &te = tlut[i];
    if (strncmp(s, te.srch, te.len)==0) {
      if (te.flags & TE_NO_WORD) return i;
      // only retrun if this is a token (not just part of a token)
      if (s[te.len]==0 || strchr(sTAlnum, s[te.len])==0L) return i;
    }
  }
  return -1;
}

void simpleWordReplace(char *d) {
  char buf[2048];
  strcpy(buf, d);
  char *s = buf;
  for(;;) {
    while (isspace(*s)) *d++ = *s++;
    if (!*s) break;
    int n = findInList(s);
    if (n>=0) {
      char *st = tlut[n].repl;
      while (*st) *d++ = *st++;
      s += tlut[n].len;
    } else {
      char c = *s;
      if (strchr(sTAlpha, c)) {
        *d++ = *s++;
        for (;;) {
          c = *s;
          if (strchr(sTAlnum, c)==0) break;
          *d++ = c; s++;
        }
      } else if (strchr(sDigit, c)) {
        *d++ = *s++;
        for (;;) {
          c = *s;
          if (strchr(sNum, c)==0) break;
          *d++ = c; s++;
        }
      } else { 
        *d++ = *s++;
      }
    }
  } 
  *d = 0;
}

void strtolower(char *s) {
  int i, n = strlen(s);
  for (i=0; i<n; i++) {
    s[i] = tolower(s[i]);
  }
}

void stripctrl(char *s) {
  char *d = s;
  for (;;) {
    char c = *s++;
    if (!c) break;
    if (c<32) continue;
    *d++ = c;
  }
  *d = 0;
}

// remove all '/*' style comments
bool stripComments(char *s, bool c) {
  char *d = s;
  while (*s) {
    if (c) { // we are inside a comment block. Wait for star/slash
      if (s[0]=='*' && s[1]=='/') {
        c = false;
        s += 2;
        continue;
      }
    } else { // we are outside of a comment block. Wait for slash/star
      if (s[0]=='/' && s[1]=='*') {
        c = true;
        s += 2;
        continue;
      }
      *d++ = *s;
    }
    s++;
  }
  *d = 0;
  return c;
}

void translateEndif() {
  ifdefs = ifdefs>>1;
}

void translateElse() {
  ifdefs = ifdefs^1;
}

void translateIf(char *s, bool neg) {
  // ++ add a LUT of defines that are assumed TRUE
  ifdefs = (ifdefs<<1) | (neg?1:0);
}

void translateInclude(char *d) {
  char buf[2048];
  strcpy(buf, d);
  char *s = buf+9;
  strcpy(d, "public import std.c.osx.");
  d += 24;
  for (;;) {
    char c = *s++;
    if (!c) break;
    if (c=='<' || c=='>' || c=='\"') continue;
    if (c=='.') { s++; continue; }
    if (c=='/') c = '.';
    *d++ = tolower(c);
  }
  *d++ =';';
  *d = 0;
}

void translateDefine(char *d) {
  // no translation for #define's yet:
  *d = 0;;
}

// a nonsense alias is the remainder of a line that aliases
// the same keyword, for example "alias myType myType".
void removeNonsenseAlias(char *d, int o) {
  char *b = d+o;
  char *s = strchr(b, ' ');
  if (!s) return;
  char *e = strchr(s, ';');
  if (!e) return;
  if (strncmp(b, s+1, e-s-1)==0) {
    *d = 0;
  }
}

void alignHash(char *buf) {
  char *s = buf;
  while (isspace(*s)) s++;
  if (s!=buf)
    memmove(buf, s, strlen(s)+1);
}

void translate(FILE *src, FILE *dst) {
  char buf[2048];
  bool inComment = false;
  bool firstComment = true;
  while (!feof(src)) {
    if (fgets(buf, 2048, src)==0L) break;
    stripctrl(buf);
    if (firstComment) {
      if (!inComment) {
        if (strncmp(buf, "/*", 2)==0) {
          inComment = true;
        }
      }
      if (inComment) {
        fputs(buf, dst);
        fputc('\n', dst);
        if (strstr(buf, "*/")) {
          inComment = false;
          firstComment = false;
          continue;
        }
      }
    }
    inComment = stripComments(buf, inComment);
    if (*buf==0) continue;
    //printf("// \"C\": %s\n", buf);
    if (buf[0]=='#') alignHash(buf+1);
    if (strncmp(buf, "#include ", 9)==0) {
      translateInclude(buf);
      fputs(buf, dst);
      fputc('\n', dst);
    } else if (strncmp(buf, "#ifndef ", 8)==0) translateIf(buf+8, false);
    else if (strncmp(buf, "#ifdef ", 7)==0) translateIf(buf+7, true);
    else if (strncmp(buf, "#if ", 4)==0) translateIf(buf+4, true);
    else if (strncmp(buf, "#else", 5)==0) translateElse();
    else if (strncmp(buf, "#elif ", 6)==0) { translateElse(); translateIf(buf+6, ifdefs&1); }
    else if (strncmp(buf, "#endif", 6)==0) translateEndif();
    else {
      if (ifdefs&1) continue;
      simpleWordReplace(buf);
      if (strncmp(buf, "#define ", 8)==0) translateDefine(buf);
      if (*buf==0) continue;
      if (strncmp(buf, "alias ", 6)==0) removeNonsenseAlias(buf, 6); 
      else if (strncmp(buf, "typedef ", 8)==0) removeNonsenseAlias(buf, 8); 
      if (*buf==0) continue;
      fputs(buf, dst);
      fputc('\n', dst);
    }
  }
}

void translate(char *srcname) {
  char buf[1024];
  char *dstname = strdup(srcname);
  dstname[strlen(dstname)-1] = 'd';
  sprintf(buf, "%s/%s", out_path, dstname); 
  strtolower(buf);
  printf("Translating \"%s\" to \"%s\"\n", srcname, dstname);
  FILE *dst = fopen(buf, "wb");
  if (!dst) {
    printf("Can't open destination file \"%s\"\n", buf);
    return;
  }
  sprintf(buf, "%s/%s", in_path, srcname);
  FILE *src = fopen(buf, "rb");
  if (!src) {
    printf("Can't open source file \"%s\"\n", buf);
    return;
  }
  // ++ create destination path! 
  fprintf(dst, "/+ Automatic translation of the \"C\" header file\n"
               " + %s\n"
               " + to \"D\" by \"simpleh2d\". Original copyright notice follows.\n +/\n\n", buf);
  sprintf(buf, "%s/%s", out_path+3, dstname);
  strtolower(buf);
  char *d = buf; 
  for (;;) {
    char c = *d;
    if (c=='/') c = '.';
    else if (c=='.') c = 0;
    *d++ = c;
    if (c==0) break;
  }
  fprintf(dst, "module %s;\n\n", buf);
  translate(src, dst);
  fclose(src);
  fclose(dst);
}

int main(int, char**) {
  initTLut();
  char buf[1024];
  FILE *cmd = fopen("sh2d.txt", "rb");
  if (!cmd) {
    printf("Can't open command file \"sh2d.txt\"\n");
    return 0;
  }
  while (!feof(cmd)) {
    if (fgets(buf, 1024, cmd)==0L) break;
    stripctrl(buf);
    switch (buf[0]) {
      case 'i': in_path = strdup(buf+1); break;
      case 'o': out_path = strdup(buf+1); break;
      case 't': translate(buf+1); break;
      default: break;
    }
  }
  fclose(cmd);
  return 0;
}

