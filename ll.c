#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 200

struct clip *build_a_lst();
struct clip *append();
int find_length();
void print_lst();
void split_line();

struct clip {
  int views;
  char *user;
  char *id;
  char *title;
  struct clip *next;
} *head;

int main(int argc, char **argv) {
  int n;
  head = build_a_lst(*(argv+1));
  n = find_length(head);
  printf("%d clips\n",n);
  print_lst(head);		/* prints the table */
  return 0;
}

struct clip *build_a_lst(char *fn) {
  FILE *fp;
  struct clip *hp;
  char *fields[4];
  char line[LINE_LENGTH];
  int cnt=0;
  hp=NULL;
  fp=fopen(fn, "r");
  while(fgets(line, LINE_LENGTH, fp)){
    split_line(&fields, line);
    hp=append(hp, fields);
  }
  //printf("%d", hp -> views);

  return hp;
}


void split_line(char **fields,char *line) {
  int i=0;
  char *token, *delim;
  delim = ",\n";
  token = strtok(line, delim);
  while(token) {
      fields[i] = malloc(sizeof(char) * strlen(token));
      strcpy(fields[i], token);
      token = strtok(NULL, delim);
      i++;
  }
}

struct clip *append(struct clip *hp,char **five) {
  struct clip *cp,*tp;
  tp = (struct clip*) malloc(sizeof(struct clip));
  tp -> next = NULL;
  tp -> views = atoi(five[0]);
  tp -> user = five[1];
  tp -> id = five[2];
  tp -> title = five[3];
//  printf("%d ", tp -> views);
//  printf("%s ", tp -> user);
//  printf("%s ", tp -> id);
//  printf("%s\n", tp -> title);
  if(hp){
      cp = hp;
      while(cp -> next)
          cp = cp -> next;
      cp -> next = tp;
  }
  else
      hp = tp;

  return hp;
}

void print_lst(struct clip *cp) {
    while(cp) {
        printf("%d,%s,%s,%s\n",cp->views,cp->user,cp->id,cp->title);
        cp = cp -> next;
    }
}

int find_length(struct clip *cp){
    int cnt = 0;
    while(cp) {
        cnt++;
        cp = cp -> next;
    }
    return cnt;
}
